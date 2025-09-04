// current_time.c

#include <string.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/rtc.h"

#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

#include "wifi_conn.h" 

#define WIFI_SSID "UFC-MMA"
#define WIFI_PASS "05142029"
#define NTP_SERVER "pool.ntp.org"
#define NTP_MSG_LEN 48
#define NTP_PORT 123
#define NTP_DELTA 2208988800 // Segundos entre 1 Jan 1900 e 1 Jan 1970
#define NTP_TIMEOUT_MS (10 * 1000) // Timeout de 10 segundos

// Estrutura para manter o estado do cliente NTP
typedef struct NTP_STATE_T {
    ip_addr_t ntp_server_address;
    struct udp_pcb *ntp_pcb;
    bool dns_request_sent;
} NTP_STATE_T;

// Flag global para indicar que o RTC foi sincronizado
static volatile bool g_rtc_set_ok = false;

// Função final chamada quando uma resposta NTP válida é recebida
static void ntp_result(time_t *result) {
    if (result) {
        struct tm *utc = gmtime(result);
        printf("NTP Response: %02d/%02d/%04d %02d:%02d:%02d\n", utc->tm_mday, utc->tm_mon + 1, utc->tm_year + 1900,
               utc->tm_hour, utc->tm_min, utc->tm_sec);

        datetime_t t = {
                .year  = (int16_t)(utc->tm_year + 1900),
                .month = (int8_t)(utc->tm_mon + 1),
                .day   = (int8_t)utc->tm_mday,
                .dotw  = (int8_t)utc->tm_wday,
                .hour  = (int8_t)utc->tm_hour,
                .min   = (int8_t)utc->tm_min,
                .sec   = (int8_t)utc->tm_sec
        };
        rtc_set_datetime(&t);
        g_rtc_set_ok = true; 
    } else {
        printf("NTP Error: Falha na solicitação.\n");
    }
}

// Envia a requisição NTP para o servidor
static void ntp_request(NTP_STATE_T *state) {
    cyw43_arch_lwip_begin();
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, NTP_MSG_LEN, PBUF_RAM);
    uint8_t *req = (uint8_t *) p->payload;
    memset(req, 0, NTP_MSG_LEN);
    req[0] = 0x1b; 
    udp_sendto(state->ntp_pcb, p, &state->ntp_server_address, NTP_PORT);
    pbuf_free(p);
    cyw43_arch_lwip_end();
}

 // Callback chamado quando a resolução DNS é concluída
static void ntp_dns_found(const char *hostname, const ip_addr_t *ipaddr, void *arg) {
    NTP_STATE_T *state = (NTP_STATE_T*)arg;
    if (ipaddr) {
        state->ntp_server_address = *ipaddr;
        printf("NTP Server IP: %s\n", ip4addr_ntoa(ipaddr));
        ntp_request(state);
    } else {
        printf("NTP Error: Falha na resolução DNS\n");
        ntp_result(NULL);
    }
}

// Callback chamado quando uma resposta NTP é recebida
static void ntp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) {
    NTP_STATE_T *state = (NTP_STATE_T*)arg;
    if (p->tot_len == NTP_MSG_LEN) {
        uint8_t seconds_buf[4] = {0};
        pbuf_copy_partial(p, seconds_buf, sizeof(seconds_buf), 40);
        uint32_t seconds_since_1900 = seconds_buf[0] << 24 | seconds_buf[1] << 16 | seconds_buf[2] << 8 | seconds_buf[3];
        time_t epoch = seconds_since_1900 - NTP_DELTA;
        ntp_result(&epoch);
    } else {
        printf("NTP Error: Resposta inválida\n");
        ntp_result(NULL);
    }
    pbuf_free(p);
}

static NTP_STATE_T* ntp_client_init(void) {
    NTP_STATE_T *state = calloc(1, sizeof(NTP_STATE_T));
    if (!state) {
        return NULL;
    }
    state->ntp_pcb = udp_new_ip_type(IPADDR_TYPE_ANY);
    if (state->ntp_pcb) {
        udp_recv(state->ntp_pcb, ntp_recv, state);
    }
    return state;
}


void setup_rtc_from_ntp() {
    g_rtc_set_ok = false;
    rtc_init();
    connect_to_wifi(WIFI_SSID, WIFI_PASS);

    NTP_STATE_T *state = ntp_client_init();
    if (!state) {
        printf("ERRO FATAL: Falha ao inicializar cliente NTP.\n");
        return;
    }

    printf("Wi-Fi conectado. Enviando requisição DNS/NTP...\n");

    // Inicia a requisição DNS (que então iniciará a requisição NTP)
    cyw43_arch_lwip_begin();
    dns_gethostbyname(NTP_SERVER, &state->ntp_server_address, ntp_dns_found, state);
    cyw43_arch_lwip_end();

    // Laço de espera bloqueante com timeout
    absolute_time_t timeout_time = make_timeout_time_ms(NTP_TIMEOUT_MS);
    while (absolute_time_diff_us(get_absolute_time(), timeout_time) > 0 && !g_rtc_set_ok) {
        cyw43_arch_poll(); // ESSENCIAL: Permite que a rede funcione
        sleep_ms(10);
    }

    // Limpeza
    udp_remove(state->ntp_pcb);
    free(state);

    if (g_rtc_set_ok) {
        printf("RTC sincronizado com sucesso!\n");
    } else {
        printf("ERRO: Timeout ao sincronizar RTC. Verifique a conexão com a internet.\n");
    }
}

void get_current_timestamp_str(char* buf, size_t len) {
    if (!g_rtc_set_ok) {
        snprintf(buf, len, "RTC nao sincronizado");
        return;
    }

    datetime_t now;
    rtc_get_datetime(&now);

    snprintf(buf, len, "%02d/%02d/%04d %02d:%02d:%02d",
             now.day, now.month, now.year,
             now.hour-3, now.min, now.sec);
}