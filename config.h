#ifndef CONFIG_H
#define CONFIG_H


#define IS_CIPHER 1

#define MD5_HASHBYTES 16

#define MAX_LOG_LENGTH 1024

#define aes_expand(n)	(n&0x000F ? (n+0x000F)&0xFFF0 : n)

typedef unsigned int uint32_t;

typedef unsigned char uint8_t;

typedef struct MD5Context {
    uint32_t buf[4];
    uint32_t bits[2];
    unsigned char in[64];
} MD5_CTX;

#endif // CONFIG_H

