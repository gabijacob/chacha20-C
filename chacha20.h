// chacha20.h
#ifndef CHACHA20_H
#define CHACHA20_H

#include <stdint.h>

#define ROUNDS 20

void chacha20_block(uint32_t out[16], const uint32_t key[8], uint32_t counter[2], const uint32_t nonce[2]);
void print_block(const char* label, uint32_t block[16]);

#endif