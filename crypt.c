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
char *rot13(const char *a)
{
    char *s = malloc(strlen(a) + 1);
    strcpy(s, a);
    for(int i = 0; s[i] != '\0'; i++) {
        if (isupper(s[i]))
            s[i] += s[i] < 'N' ? 13 : -13;
        else if (islower(s[i]))
            s[i] += s[i] < 'n' ? 13 : -13;
    }
    return s;
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
char *rot47(const char *a)
{
    char *s = malloc(strlen(a) + 1);
    strcpy(s, a);
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] > 32 && s[i] < 80)
            s[i] += 47;
        else if (s[i] > 79 && s[i] < 127)
            s[i] -= 47;
    }
    return s;
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
char *base64_encode(const char *data)
{
    size_t input_length = strlen(data);
    size_t output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = malloc(output_length);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;
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
char *base64_decode(const char *data)
{
    size_t input_length = strlen(data);
    size_t output_length = (size_t)(input_length / 4 * 3);

    if (decoding_table == NULL) {
        decoding_table = malloc(256);
        for (int i = 0; i < 64; i++)
            decoding_table[(unsigned char) encoding_table[i]] = i;
    }

    if (input_length % 4 != 0) return NULL;
    if (data[input_length - 1] == '=') (output_length)--;
    if (data[input_length - 2] == '=') (output_length)--;

    char *decoded_data = malloc(output_length);
    if (decoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);

        if (j < output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
    
    free(decoding_table);
    return decoded_data;
}