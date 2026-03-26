#pragma once
#include <stdint.h>

void rng_seed(uint32_t seed);
uint32_t rng_next();
uint32_t rng_range(uint32_t max);
