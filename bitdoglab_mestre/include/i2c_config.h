#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

#include "hardware/i2c.h"
#include <stdint.h> 

#define I2C_PORT i2c1
#define I2C_SDA_PIN 2
#define I2C_SCL_PIN 3

#define SLAVE_ADDR 0x26

// Estrutura que define o pacote de dados I2C
typedef struct {
    char product_name[32];  // Nome do produto 
    int32_t quantity;       // Quantidade 
    char operation;         // Operação 'B' para Cadastro ou 'C' para Retirada
} I2C_Payload;

void i2c_init_protocol();

#endif