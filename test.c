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
        char *a = malloc(strlen(input)+1);
        
        strcpy(a, input);
        printf("ROT13: %s\n", rot13(a));
        
        strcpy(a, input);
        printf("ROT47: %s\n", rot47(a));
        
        free(a);

        char *name = "Casey Adam Scarborough";
        size_t input_len = strlen((const char *)name);
        size_t output_len = (size_t)(input_len * 4 / 3);
        char * base64_e_name = base64_encode((const unsigned char *) name, input_len, &output_len);
        unsigned char * base64_d_name = base64_decode(base64_e_name, output_len, &input_len);
        printf("Encode: %s\nDecode: %s\n", base64_e_name, base64_d_name);
        base64_cleanup();
    }
    return 0;
}