#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d)(  \
	a += b, d ^= a, d = ROTL(d, 16), \
	c += d, b ^= c, b = ROTL(b, 12), \
	a += b, d ^= a, d = ROTL(d, 8),  \
	c += d, b ^= c, b = ROTL(b, 7))

#define ROUNDS 20

void print_block(const char* label, uint32_t block[16]) {
    printf("%s:\n", label);
    for (int i = 0; i < 16; i++) {
        printf("%08x ", block[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
}

void chacha20_block(uint32_t out[16], const uint32_t key[8], uint32_t counter[2], const uint32_t nonce[2]) {
    uint32_t state[16];
    int i;

    // Initializing chacha20 state
    // constant "expand 32-byte k"
    state[0] = 0x61707865; 
    state[1] = 0x3320646e;
    state[2] = 0x79622d32;
    state[3] = 0x6b206574;
    
    // Copying the 256-bit key into the state
    for (i = 0; i < 8; ++i)
        state[4 + i] = key[i];
    
    // Adding counter and nonce
    state[12] = counter[0];
    state[13] = counter[1];
    state[14] = nonce[0];
    state[15] = nonce[1];

    // Printing the initial state for debugging
    print_block("estado inicial", state);
    
    // Copying the initial state
    uint32_t x[16];
    memcpy(x, state, sizeof(state));
    
    // executing the ChaCha20 rounds
    for (i = 0; i < ROUNDS; i += 2) {
        // Odd round
        QR(x[0], x[4], x[8], x[12]);
        QR(x[1], x[5], x[9], x[13]);
        QR(x[2], x[6], x[10], x[14]);
        QR(x[3], x[7], x[11], x[15]);
        // Even round
        QR(x[0], x[5], x[10], x[15]);
        QR(x[1], x[6], x[11], x[12]);
        QR(x[2], x[7], x[8], x[13]);
        QR(x[3], x[4], x[9], x[14]);
    }
    
    // Adding the initial state to the final state to generate the key stream
    for (i = 0; i < 16; ++i)
        out[i] = x[i] + state[i];
}