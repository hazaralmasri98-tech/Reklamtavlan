#include "lcd_driver.h"
#include <avr/io.h>
#include <util/delay.h>

// Pin mapping (ATmega328P)
// RS -> PB4  (Arduino D12)
// E  -> PB3  (Arduino D11)
// D4 -> PD4  (Arduino D4)
// D5 -> PD5  (Arduino D5)
// D6 -> PD6  (Arduino D6)
// D7 -> PD7  (Arduino D7)

static void lcd_pulse_enable() {
  PORTB |= (1 << PB3);   // E high
  _delay_us(1);
  PORTB &= ~(1 << PB3);  // E low
  _delay_us(100);
}

static void lcd_write4(uint8_t value) {
  // Clear D4-D7 first
  PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));

  // Put 4-bit value on D4-D7
  if (value & 0x01) PORTD |= (1 << PD4);
  if (value & 0x02) PORTD |= (1 << PD5);
  if (value & 0x04) PORTD |= (1 << PD6);
  if (value & 0x08) PORTD |= (1 << PD7);

  lcd_pulse_enable();
}

static void lcd_send(uint8_t value, uint8_t rs) {
  if (rs) PORTB |= (1 << PB4);   // RS = 1 for data
  else    PORTB &= ~(1 << PB4);  // RS = 0 for command

  lcd_write4(value >> 4);      // high nibble
  lcd_write4(value & 0x0F);    // low nibble
}

static void lcd_command(uint8_t cmd) {
  lcd_send(cmd, 0);
  _delay_us(50);
}

static void lcd_data(uint8_t data) {
  lcd_send(data, 1);
  _delay_us(50);
}

void lcd_init() {
  // Set pins as output
  DDRB |= (1 << PB4) | (1 << PB3);                          // RS, E
  DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7); // D4-D7

  _delay_ms(50);

  // 4-bit init sequence
  PORTB &= ~((1 << PB4) | (1 << PB3));

  lcd_write4(0x03);
  _delay_ms(5);

  lcd_write4(0x03);
  _delay_us(150);

  lcd_write4(0x03);
  _delay_us(150);

  lcd_write4(0x02); // 4-bit mode
  _delay_us(150);

  // Function set: 4-bit, 2 lines, 5x8 font
  lcd_command(0x28);

  // Display on, cursor off, blink off
  lcd_command(0x0C);

  // Entry mode: increment, no shift
  lcd_command(0x06);

  // Clear display
  lcd_clear();
}

void lcd_clear() {
  lcd_command(0x01);
  _delay_ms(2);
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
  static const uint8_t row_offsets[] = {0x00, 0x40};
  lcd_command(0x80 | (col + row_offsets[row]));
}

void lcd_print_char(char c) {
  lcd_data((uint8_t)c);
}

void lcd_print(const char* s) {
  while (*s) {
    lcd_print_char(*s);
    s++;
  }
}