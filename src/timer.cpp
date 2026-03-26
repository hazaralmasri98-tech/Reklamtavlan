#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t g_millis = 0;

void timer0_init() {
  // CTC mode
  TCCR0A = (1 << WGM01);

  // Prescaler 64
  TCCR0B = (1 << CS01) | (1 << CS00);

  // 16 MHz / 64 = 250000 Hz
  // 250 ticks = 1 ms
  OCR0A = 249;

  // Enable compare match interrupt
  TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
  g_millis++;
}

uint32_t millis_avr() {
  uint32_t value;

  cli();
  value = g_millis;
  sei();

  return value;
}