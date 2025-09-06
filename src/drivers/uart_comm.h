#ifndef UART_COMM_H
#define UART_COMM_H
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200 
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define START_BYTE 0x7E

typedef struct {
    char name[64];
    char timestamp[25];
    char operation[8]; 
} AccessLog;

void uart_comm_init();
void uart_send_log(const AccessLog *log);
bool uart_receive_log(AccessLog *log);

#endif