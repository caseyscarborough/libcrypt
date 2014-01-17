#include "crypt.h"
#include <errno.h>

int main(int argc, char *argv[])
{
    char *text = "The Quick Brown Fox Jumps Over The Lazy Dog.";

    char *rot13_encoded_input = rot13(text);
    char *rot47_encoded_input = rot47(text);
    char * base64_encoded_name = base64_encode((const unsigned char *) text);
    unsigned char * base64_decoded_name = base64_decode(base64_encoded_name);
    
    printf("ROT13: %s\n", rot13_encoded_input);
    printf("ROT47: %s\n", rot47_encoded_input);
    printf("Base64 Encoded: %s\n", base64_encoded_name);
    printf("Base64 Decoded: %s\n", base64_decoded_name);

    free(rot13_encoded_input);
    free(rot47_encoded_input);
    free(base64_encoded_name);
    free(base64_decoded_name);
    base64_cleanup();
    
    return 0;
}