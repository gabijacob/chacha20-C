// test_chacha20.c
#include "chacha20.h"
#include <stdio.h>
#include <stdint.h>

void test_chacha20_block_with_known_values() {
    uint32_t key[8] = {
        0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
        0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c
    };
    uint32_t nonce[2] = { 0x00000009, 0x0000004a };
    uint32_t counter[2] = { 0x00000001, 0x00000000 };
    uint32_t out[16];

    chacha20_block(out, key, counter, nonce);
    print_block("Resultado para valores conhecidos", out);
}

void test_chacha20_block_with_zero_key_and_nonce() {
    uint32_t key[8] = { 0 };
    uint32_t nonce[2] = { 0 };
    uint32_t counter[2] = { 0 };
    uint32_t out[16];

    chacha20_block(out, key, counter, nonce);
    print_block("Resultado para chave e nonce zero", out);
}

int main() {
    test_chacha20_block_with_known_values();
    test_chacha20_block_with_zero_key_and_nonce();
    return 0;
}
