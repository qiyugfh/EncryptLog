#include "log.h"
#include "md5.h"
#include "aes.h"
#include <stdio.h>
#include <time.h>



#define IS_CIPHER 1

#define MAX_LOG_LENGTH 1024

extern const char *encrypt_file_name;


void setKey(const char *password, int len)
{
    unsigned char key[MD5_HASHBYTES] = {0};
    /* 密码先MD5散列128位,然后作为AES-128的密钥 */
    MD5Data((unsigned char *)password, len, key);
    aes_set_key(key, len);
}


void decipher_log(const char *password, int pw_len, const char *in_filepath, const char *out_filepath)
{
    unsigned char key[MD5_HASHBYTES];
    MD5Data((unsigned char*)password, pw_len, key);
    aes_set_key(key, MD5_HASHBYTES);

    if (AES_SUCCESS != aes_decipher_file(in_filepath, out_filepath, 0, AES_128)) {
        printf("decipher log failed!\n");
        return;
    }

    printf("decipher log sucess!\n");
}


void cipher_buf(unsigned char *buf, uint32_t expand_buf_len)
{
    unsigned char cipher_buf[AES_BUFSIZ], out[AES_BUFSIZ];
    int uncipher_io_size = expand_buf_len;

    while (uncipher_io_size > 0) {
        memcpy(cipher_buf, buf + expand_buf_len - uncipher_io_size, AES_BUFSIZ);
        if (aes_cipher_data(cipher_buf, AES_BUFSIZ, out, NULL, AES_128) != AES_SUCCESS) {
            printf("failure to encrypt!\n");
            return;
        }
        memcpy(buf + expand_buf_len - uncipher_io_size, out, AES_BUFSIZ);
        uncipher_io_size -= AES_BUFSIZ;
    }
}


void write_log(const char *level, const char *file, const char *function, const long line, const char *fmt, ...)
{
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char datetime[28] = {0};
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", timeinfo);

    FILE *fp = fopen(encrypt_file_name, "ab+");
    if(fp == NULL){
        return;
    }

    char *msgBuf = (char *)malloc(MAX_LOG_LENGTH);
    memset(msgBuf, 0, MAX_LOG_LENGTH);
    sprintf(msgBuf, "[%s][%s](%s:%s:%ld)", datetime, level, file, function, line);

    va_list args;
    va_start(args, fmt);
    vsnprintf(msgBuf + strlen(msgBuf), MAX_LOG_LENGTH - 2, fmt, args);
    va_end(args);
    strcat(msgBuf, "\n");

#if IS_CIPHER
    int buf_len = strlen(msgBuf);
    buf_len= aes_expand(buf_len);
    unsigned char *cipherBuf = (unsigned char *) malloc(buf_len);
    memset(cipherBuf, 0, buf_len);
    memcpy(cipherBuf, msgBuf, strlen(msgBuf));
    cipher_buf(cipherBuf, buf_len);
    fwrite(cipherBuf, buf_len, 1, fp);
    free(cipherBuf);
#else
    fwrite(msgBuf, strlen(msgBuf), 1, fp);
#endif

    fflush(fp);
    fclose(fp);

    // 像屏幕打印
    fprintf(stdout, "%s", msgBuf);
    free(msgBuf);
}
