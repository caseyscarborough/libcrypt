#include "crypt.h"

/*
 * This method returns a newly allocated 'string' that is encoded
 * using the ROT13 cipher. It is up to the user to free the memory 
 * from the data returned from this method (shown below).
 *
 * Example:
 *   char *text = "This is sample text.";
 *   char *rot13_text = rot13(text);
 *   printf("%s\n", rot13_text);
 *   free(rot13_text);
 */
char *rot13(const char *input)
{
    char *output = malloc(strlen(input) + 1);
    strcpy(output, input);
    for(int i = 0; output[i] != '\0'; i++) {
        if (isupper(output[i]))
            output[i] += output[i] < 'N' ? 13 : -13;
        else if (islower(output[i]))
            output[i] += output[i] < 'n' ? 13 : -13;
    }
    return output;
}

/*
 * This method returns a newly allocated 'string' that is encoded
 * using the ROT13 cipher. It is up to the user to free the memory 
 * from the data returned from this method (shown below).
 *
 * Example:
 *   char *text = "This is sample text.";
 *   char *rot47_text = rot47(text);
 *   printf("%s\n", rot47_text);
 *   free(rot47_text);
 */
char *rot47(const char *input)
{
    char *output = malloc(strlen(input) + 1);
    strcpy(output, input);
    for (int i = 0; output[i] != '\0'; i++) {
        if (output[i] > 32 && output[i] < 80) {
            output[i] += 47;
        } else if (output[i] > 79 && output[i] < 127) {
            output[i] -= 47;
        }
    }
    return output;
}

/*
 * This method takes in a string and returns the string encoded
 * into the Base64 encoding scheme. It is up to the user of this
 * method to free the memory returned from it. (shown below)
 *
 * Example:
 *   char *text = "The Quick Brown Fox Jumps Over The Lazy Dog.";
 *   char *base64_encoded_text = base64_encode(text);
 *   printf("%s\n", base64_encoded_text);
 *   // Outputs: VGhlIFF1aWNrIEJyb3duIEZveCBKdW1wcyBPdmVyIFRoZSBMYXp5IERvZy4=
 *   free(base64_encoded_text);
 */
char *base64_encode(const char *input)
{
    size_t input_length = strlen(input);
    size_t output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = malloc(output_length);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? input[i++] : 0;
        uint32_t octet_b = i < input_length ? input[i++] : 0;
        uint32_t octet_c = i < input_length ? input[i++] : 0;
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        for (int i = 3; i >= 0; i--)
            encoded_data[j++] = encoding_table[(triple >> i * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[output_length - 1 - i] = '=';

    return encoded_data;
}

/*
 * This method takes in a string of Base64 encoded data and returns the
 * decoded version of it. It is up to the user of this method to free
 * the memory returned from it. (shown below)
 *
 * Example:
 *   char *text = "VGhpcyBpcyBzb21lIGR1bW15IHRleHQgdG8gYmUgZW5jb2RlZCBhbmQgZGVjb2RlZC4=";
 *   char *base64_decoded_text = base64_decode(text);
 *   printf("%s\n", base64_decoded_text);
 *   // Outputs: This is some dummy text to be encoded and decoded.
 *   free(base64_decoded_text);
 */
char *base64_decode(const char *input)
{
    size_t input_length = strlen(input);
    size_t output_length = (size_t)(input_length / 4 * 3);
    if (input_length % 4 != 0) return NULL;

    base64_decoding_table_init();
    if (input[input_length - 1] == '=') (output_length)--;
    if (input[input_length - 2] == '=') (output_length)--;

    char *decoded_data = malloc(output_length);
    if (decoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = input[i] == '=' ? 0 & i++ : decoding_table[input[i++]];
        uint32_t sextet_b = input[i] == '=' ? 0 & i++ : decoding_table[input[i++]];
        uint32_t sextet_c = input[i] == '=' ? 0 & i++ : decoding_table[input[i++]];
        uint32_t sextet_d = input[i] == '=' ? 0 & i++ : decoding_table[input[i++]];
        uint32_t triple = (sextet_a << 0x12) + (sextet_b << 0x0C) + (sextet_c << 0x06) + sextet_d;

        if (j < output_length) decoded_data[j++] = (triple >> 0x10) & 0xFF;
        if (j < output_length) decoded_data[j++] = (triple >> 0x08) & 0xFF;
        if (j < output_length) decoded_data[j++] = (triple >> 0x00) & 0xFF;
    }

    base64_decoding_table_cleanup();
    return decoded_data;
}

/**
 * This method initializes the decoding table used to decode
 * data that has been Base64 encoded, and is called by base64_decode.
 */
void base64_decoding_table_init()
{
    if (decoding_table == NULL) {
        decoding_table = malloc(123);
        for (int i = 0; i < 64; i++) {
            decoding_table[encoding_table[i]] = i;
        }
    }
}

/**
 * Frees the memory allocated for the decoding table, and is
 * called by base64_decode.
 */
void base64_decoding_table_cleanup()
{
    free(decoding_table);
    decoding_table = NULL;
}