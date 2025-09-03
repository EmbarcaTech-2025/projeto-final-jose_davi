#ifndef DISPLAY_OLED_H
#define DISPLAY_OLED_H

#include "../inc/ssd1306.h"  // Biblioteca do display OLED SSD1306
#include "../inc/ssd1306_i2c.h" // Biblioteca de I2C do SSD1306

// Define os pinos GPIO conectados ao SDA e SCL do display OLED
#define I2C_SDA 14
#define I2C_SCL 15

// Dimensões do display OLED (em pixels)
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

extern uint8_t ssd[ssd1306_buffer_length]; // Buffer do display OLED

extern struct render_area frame_area; // Estrutura que define uma área de renderização

void display_init(); // Função para inicializar o display OLED
void draw_centered_string(uint8_t* buffer, int y, char* text); // Função para desenhar texto centralizado
#endif