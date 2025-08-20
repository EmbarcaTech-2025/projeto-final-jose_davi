#include "include/i2c_config.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include <stdio.h>

void i2c_init_protocol() {
    i2c_init(I2C_PORT, 100 * 1000); 

    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
}