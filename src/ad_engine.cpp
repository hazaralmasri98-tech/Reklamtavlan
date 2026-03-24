#include "ad_engine.h"
#include <Arduino.h>

// -------- Messages --------

static const Message harryMsgs[] = {
  {"Kop bil hos Harry", SCROLL},
  {"En god bilaffar (for Harry!)", NORMAL},
  {"Hederlige Harrys Bilar", BLINK}
};

static const Message farmorMsgs[] = {
  {"Kop paj hos Farmor Anka", SCROLL},
  {"Skynda innan Marten atit alla pajer", NORMAL}
};

static const Message petterEven = {"Lat Petter bygga at dig", SCROLL};
static const Message petterOdd  = {"Bygga svart? Ring Petter", NORMAL};

static const Message langbenMsgs[] = {
  {"Mysterier? Ring Langben", NORMAL},
  {"Langben fixar biffen", NORMAL}
};

static const Message iotMsgs[] = {
  {"Synas har? IOT:s Reklambyra", NORMAL}
};

static Customer customers[] = {
  {"Harry",   5000, harryMsgs,   3, false},
  {"Farmor",  3000, farmorMsgs,  2, false},
  {"Petter",  1500, nullptr,     0, true },
  {"Langben", 4000, langbenMsgs, 2, false},
  {"IOT",     1000, iotMsgs,     1, false}
};

static const uint8_t CUSTOMER_COUNT = sizeof(customers) / sizeof(customers[0]);

static int lastCustomer = -1;

static bool isEvenMinute() {
  return ((millis() / 60000UL) % 2UL) == 0;
}

// -------- API --------

void initCustomers() {
  randomSeed(analogRead(A0));
}

const Customer* pickNextCustomer() {
  long total = 0;

  for (int i = 0; i < CUSTOMER_COUNT; i++) {
    if (i == lastCustomer) continue;
    total += customers[i].weight;
  }

  long r = random(total);
  long sum = 0;

  for (int i = 0; i < CUSTOMER_COUNT; i++) {
    if (i == lastCustomer) continue;
    sum += customers[i].weight;

    if (r < sum) {
      lastCustomer = i;
      return &customers[i];
    }
  }

  return &customers[0];
}

const Message* pickMessage(const Customer* c) {
  if (c->specialPetter) {
    return isEvenMinute() ? &petterEven : &petterOdd;
  }

  uint8_t i = random(c->msgCount);
  return &c->msgs[i];
}