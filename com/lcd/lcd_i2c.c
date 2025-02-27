#include "lcd_i2c.h"
#include <string.h>

#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 100000

static void i2c_master_init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

static void lcd_send_cmd(uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd};
    i2c_master_write_to_device(I2C_MASTER_NUM, LCD_ADDR, data, 2, 1000 / portTICK_PERIOD_MS);
}

static void lcd_send_data(uint8_t data) {
    uint8_t buffer[2] = {0x40, data};
    i2c_master_write_to_device(I2C_MASTER_NUM, LCD_ADDR, buffer, 2, 1000 / portTICK_PERIOD_MS);
}

void lcd_init() {
    i2c_master_init();
    lcd_send_cmd(0x33);
    lcd_send_cmd(0x32);
    lcd_send_cmd(0x28);
    lcd_send_cmd(0x0C);
    lcd_send_cmd(0x06);
    lcd_send_cmd(0x01);
    vTaskDelay(5 / portTICK_PERIOD_MS);
}

void lcd_clear() {
    lcd_send_cmd(0x01);
    vTaskDelay(5 / portTICK_PERIOD_MS);
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_send_data((uint8_t)(*str));
        str++;
    }
}
