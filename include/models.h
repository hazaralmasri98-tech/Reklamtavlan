#pragma once
#include <stdint.h>

enum Effect : uint8_t { NORMAL, SCROLL, BLINK };

struct Message {
  const char* text;
  Effect effect;
};

struct Customer {
  const char* name;
  int weight;
  const Message* msgs;
  uint8_t msgCount;
  bool specialPetter;
};