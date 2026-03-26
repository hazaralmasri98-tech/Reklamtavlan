#include "rng.h"

static uint32_t rng_state = 1;

void rng_seed(uint32_t seed) {
  rng_state = (seed == 0) ? 1 : seed;
}

uint32_t rng_next() {
  rng_state = rng_state * 1103515245UL + 12345UL;
  return rng_state;
}

uint32_t rng_range(uint32_t max) {
  if (max == 0) return 0;
  return rng_next() % max;
}