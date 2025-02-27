#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "driver/i2c.h"

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

void lcd_init();
void lcd_clear();
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_print(const char *str);

#endif
