#ifndef LOG_H
#define LOG_H


#include <stdarg.h>
#include <string.h>
#include "config.h"




void setKey(const char * password, int len);

void cipher_buf(unsigned char *buf, uint32_t expand_buf_len);

void decipher_log(const char *password, int pw_len, const char *in_filepath, const char *out_filepath);

void write_log(const char *level, const char *file, const char *function, const long line, const char *fmt, ...);


#define log_error(...) write_log("error", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define log_debug(...) write_log("debug", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#endif // LOG_H
