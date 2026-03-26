#include "effects.h"
#include "lcd_driver.h"
#include "timer.h"

#include <string.h>
#include <stdint.h>

static const uint8_t LCD_COLS = 16;
static const uint8_t LCD_ROWS = 2;

static const uint32_t BLINK_TIME = 450UL;
static const uint32_t SCROLL_STEP_MS = 450UL;
static const uint32_t SCROLL_PAUSE_START_MS = 1000UL;
static const uint32_t SCROLL_PAUSE_END_MS = 1200UL;
static const int SCROLL_GAP = 6;

struct LineState {
  char textBuf[96];
  Effect effect;
  uint32_t lastUpdate;

  bool blinkOn;

  int scrollPos;
  uint8_t pausePhase;   // 0=none, 1=start pause, 2=end pause
  uint32_t pauseStart;
};

static LineState line0;
static LineState line1;

static void clearRow(uint8_t row) {
  lcd_set_cursor(0, row);
  for (uint8_t i = 0; i < LCD_COLS; i++) {
    lcd_print_char(' ');
  }
}

static void printPaddedRow(uint8_t row, const char* txt) {
  lcd_set_cursor(0, row);

  uint8_t i = 0;
  while (txt && txt[i] && i < LCD_COLS) {
    lcd_print_char(txt[i]);
    i++;
  }

  while (i < LCD_COLS) {
    lcd_print_char(' ');
    i++;
  }
}

static void splitToTwoLines16(const char* txt,
                              char out0[LCD_COLS + 1],
                              char out1[LCD_COLS + 1]) {
  if (!txt) txt = "";

  for (uint8_t i = 0; i < LCD_COLS; i++) {
    out0[i] = ' ';
    out1[i] = ' ';
  }

  out0[LCD_COLS] = '\0';
  out1[LCD_COLS] = '\0';

  int len = (int)strlen(txt);

  for (int i = 0; i < (int)LCD_COLS && i < len; i++) {
    out0[i] = txt[i];
  }

  for (int i = 0; i < (int)LCD_COLS && (i + (int)LCD_COLS) < len; i++) {
    out1[i] = txt[i + LCD_COLS];
  }
}

static void renderScrollFrame(uint8_t row, const char* txt, int pos) {
  int len = (int)strlen(txt);
  int totalLen = len + SCROLL_GAP;

  lcd_set_cursor(0, row);
  for (uint8_t i = 0; i < LCD_COLS; i++) {
    int index = (pos + i) % totalLen;
    char outChar = (index < len) ? txt[index] : ' ';
    lcd_print_char(outChar);
  }
}

static void startLine(LineState &L, uint8_t row, const char* txt, Effect eff) {
  if (!txt) txt = "";

  strncpy(L.textBuf, txt, sizeof(L.textBuf) - 1);
  L.textBuf[sizeof(L.textBuf) - 1] = '\0';

  L.effect = eff;
  L.lastUpdate = millis_avr();
  L.blinkOn = true;
  L.scrollPos = 0;
  L.pausePhase = 0;
  L.pauseStart = 0;

  if (eff == NORMAL || eff == BLINK) {
    printPaddedRow(row, L.textBuf);
  } else {
    int len = (int)strlen(L.textBuf);
    if (len <= (int)LCD_COLS) {
      printPaddedRow(row, L.textBuf);
    } else {
      renderScrollFrame(row, L.textBuf, 0);
      L.pausePhase = 1;
      L.pauseStart = millis_avr();
    }
  }
}

static void updateLine(LineState &L, uint8_t row) {
  uint32_t now = millis_avr();

  if (L.effect == NORMAL) return;

  if (L.effect == BLINK) {
    if (now - L.lastUpdate >= BLINK_TIME) {
      L.lastUpdate = now;
      L.blinkOn = !L.blinkOn;

      if (L.blinkOn) {
        printPaddedRow(row, L.textBuf);
      } else {
        clearRow(row);
      }
    }
    return;
  }

  int len = (int)strlen(L.textBuf);
  if (len <= (int)LCD_COLS) {
    printPaddedRow(row, L.textBuf);
    return;
  }

  if (L.pausePhase != 0) {
    uint32_t needed = (L.pausePhase == 1) ? SCROLL_PAUSE_START_MS : SCROLL_PAUSE_END_MS;
    if (now - L.pauseStart < needed) return;

    if (L.pausePhase == 2) {
      L.scrollPos = 0;
      renderScrollFrame(row, L.textBuf, 0);
      L.pausePhase = 1;
      L.pauseStart = now;
      L.lastUpdate = now;
      return;
    }

    L.pausePhase = 0;
    L.lastUpdate = now;
  }

  if (now - L.lastUpdate < SCROLL_STEP_MS) return;
  L.lastUpdate = now;

  int totalLen = len + SCROLL_GAP;
  int lastPos = totalLen - LCD_COLS;

  if (L.scrollPos >= lastPos) {
    renderScrollFrame(row, L.textBuf, lastPos);
    L.pausePhase = 2;
    L.pauseStart = now;
    return;
  }

  L.scrollPos++;
  renderScrollFrame(row, L.textBuf, L.scrollPos);
}

void effectsBegin() {
  startLine(line0, 0, "", NORMAL);
  startLine(line1, 1, "", NORMAL);
}

void effectsStart(const char* txt, Effect eff) {
  int len = txt ? (int)strlen(txt) : 0;

  if (len <= (int)LCD_COLS) {
    startLine(line0, 0, txt, eff);
    startLine(line1, 1, "", NORMAL);
  } else {
    if (eff == SCROLL) {
      startLine(line0, 0, txt, eff);
      startLine(line1, 1, "", NORMAL);
    } else {
      char tmp0[LCD_COLS + 1];
      char tmp1[LCD_COLS + 1];
      splitToTwoLines16(txt, tmp0, tmp1);
      startLine(line0, 0, tmp0, eff);
      startLine(line1, 1, tmp1, eff);
    }
  }
}

void effectsUpdate() {
  updateLine(line0, 0);
  updateLine(line1, 1);
}