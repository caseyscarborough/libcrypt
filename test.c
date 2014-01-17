#include "crypt.h"
#include <errno.h>

void die(const char *error)
{
    if (errno) {
        perror(error);
    } else {
        printf("ERROR: %s\n", error);
    }
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        die("This script requires one argument as string of text.\n");
    } else {
        char *input = argv[1];
        
        char *rot13_encoded_input = rot13(input);
        char *rot47_encoded_input = rot47(input);

        printf("ROT13: %s\n", rot13_encoded_input);
        printf("ROT47: %s\n", rot47_encoded_input);

        char *text = "The Quick Brown Fox Jumps Over The Lazy Dog.";
                
        char * base64_encoded_name = base64_encode((const unsigned char *) text);
        unsigned char * base64_decoded_name = base64_decode(base64_encoded_name);
        
        printf("Encoded Data: %s\n", base64_encoded_name);
        printf("Decoded Data: %s\n", base64_decoded_name);

        free(rot13_encoded_input);
        free(rot47_encoded_input);
        free(base64_encoded_name);
        free(base64_decoded_name);

        base64_cleanup();
    }
    return 0;
}