#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "ad_engine.h"
#include "effects.h"
#include "models.h"
#include "lcd_driver.h"
#include "timer.h"

static const uint8_t LCD_COLS = 16;
static const uint8_t LCD_ROWS = 2;
static const uint32_t SLOT_TIME = 20000UL;

static uint32_t slotStart = 0;

static void startNextAd() {
  const Customer* c = pickNextCustomer();
  const Message* m = pickMessage(c);

  (void)c; // customer chosen but not shown separately right now

  lcd_clear();
  effectsStart(m->text, m->effect);
  slotStart = millis_avr();
}

int main() {
  lcd_init();
  timer0_init();
  sei();  // enable global interrupts

  initCustomers();
  effectsBegin();

  lcd_clear();
  lcd_set_cursor(0, 0);
  lcd_print("REKLAMTAVLAN");
  _delay_ms(1000);

  startNextAd();

  while (1) {
    if (millis_avr() - slotStart >= SLOT_TIME) {
      startNextAd();
    }

    effectsUpdate();
  }

  return 0;
}