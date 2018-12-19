
#include "log.h"
#include "config.h"

const char *encrypt_file_name = "encrypted.log";
const char *decrypt_file_name = "decrypted.log";


int main(int argc, char *argv[])
{

    char *pw = "<F*`4%r@#!Sv{8?|bJH";
    setKey(pw, strlen(pw));

    for(int n=0; n<1000; n++){
        log_debug("hello %d.", n);
    }
    decipher_log(pw, strlen(pw), encrypt_file_name, decrypt_file_name);

    return 0;
}
