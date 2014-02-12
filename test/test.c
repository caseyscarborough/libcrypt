#include "../src/crypt.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s 'string'\n", argv[0]);
        return 1;
    } else {
        char *text = argv[1];
        char *rot13_encoded_input = rot13(text);
        char *rot47_encoded_input = rot47(text);
        char *base64_encoded_input = base64_encode(text);
        char *base64_decoded_input = base64_decode(base64_encoded_input);
        char *md5_hashed_input = md5(text);
        
        printf("ROT13: %s\n", rot13_encoded_input);
        printf("ROT47: %s\n", rot47_encoded_input);
        printf("Base64 Encoded: %s\n", base64_encoded_input);
        printf("Base64 Decoded: %s\n", base64_decoded_input);
        printf("MD5 Hashed: %s\n", md5_hashed_input);

        free(rot13_encoded_input);
        free(rot47_encoded_input);
        free(base64_encoded_input);
        free(base64_decoded_input);
        free(md5_hashed_input);
    }
    
    return 0;
}