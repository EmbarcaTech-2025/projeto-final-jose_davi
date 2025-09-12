#include "uart_comm.h"
#include <string.h>

static uint8_t calculate_checksum(const uint8_t *data, size_t len) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < len; i++) {
        checksum ^= data[i];
    }
    return checksum;
}

void uart_comm_init() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

void uart_send_log(const AccessLog *log) {
    uint8_t payload_len = sizeof(AccessLog);
    uint8_t frame[payload_len + 3];

    frame[0] = START_BYTE;
    frame[1] = payload_len;
    memcpy(&frame[2], log, payload_len);
    
    frame[payload_len + 2] = calculate_checksum(&frame[1], payload_len + 1);

    uart_write_blocking(UART_ID, frame, sizeof(frame));
}

bool uart_receive_log(AccessLog *log) {
    if (!uart_is_readable(UART_ID)) {
        return false;
    }

    if (uart_getc(UART_ID) != START_BYTE) {
        return false;
    }

    uint8_t payload_len = uart_getc(UART_ID);
    if (payload_len != sizeof(AccessLog)) {
        for(int i = 0; i < payload_len + 1; i++) uart_getc(UART_ID);
        return false;
    }
    
    uint8_t payload_buffer[sizeof(AccessLog)];
    uart_read_blocking(UART_ID, payload_buffer, payload_len);

    uint8_t received_checksum = uart_getc(UART_ID);

    uint8_t calculated_checksum = payload_len; 
    for(int i = 0; i < payload_len; i++) {
        calculated_checksum ^= payload_buffer[i];
    }

    if (calculated_checksum == received_checksum) {
        memcpy(log, payload_buffer, sizeof(AccessLog));
        return true;
    }

    return false; 
}