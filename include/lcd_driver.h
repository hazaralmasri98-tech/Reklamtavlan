#pragma once
#include <stdint.h>

void lcd_init();
void lcd_clear();
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_print_char(char c);
void lcd_print(const char* s);