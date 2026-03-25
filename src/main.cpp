#include <Arduino.h>
#include <LiquidCrystal.h>

#include "ad_engine.h"
#include "effects.h"
#include "models.h"

// LCD pins: RS=12, E=11, D4=4, D5=5, D6=6, D7=7
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

static const int LCD_COLS = 16;
static const int LCD_ROWS = 2;
static const unsigned long SLOT_TIME = 20000UL;

static unsigned long slotStart = 0;

// Start next advertisement
void startNextAd() {
  const Customer* c = pickNextCustomer();
  const Message* m = pickMessage(c);

  lcd.clear();
  effectsStart(m->text, m->effect);

  slotStart = millis();
}

void setup() {
  lcd.begin(LCD_COLS, LCD_ROWS);

  initCustomers();
  effectsBegin();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REKLAMTAVLAN");
  delay(1000);

  startNextAd();
}

void loop() {
  // Change ad every 20 seconds
  if (millis() - slotStart >= SLOT_TIME) {
    startNextAd();
  }

  // Update effects (scroll, blink)
  effectsUpdate();
}