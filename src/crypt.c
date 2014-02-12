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
            encoded_data[j++] = base64_encoding_table[(triple >> i * 6) & 0x3F];
    }

    for (int i = 0; i < base64_mod_table[input_length % 3]; i++)
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

    if (input_length % 4 != 0) return NULL;
    size_t output_length = (size_t)(input_length / 4 * 3);

    base64_decoding_table_init();
    if (input[input_length - 1] == '=') (output_length)--;
    if (input[input_length - 2] == '=') (output_length)--;

    char *decoded_data = malloc(output_length);
    if (decoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = input[i] == '=' ? 0 & i++ : base64_decoding_table[(int)input[i++]];
        uint32_t sextet_b = input[i] == '=' ? 0 & i++ : base64_decoding_table[(int)input[i++]];
        uint32_t sextet_c = input[i] == '=' ? 0 & i++ : base64_decoding_table[(int)input[i++]];
        uint32_t sextet_d = input[i] == '=' ? 0 & i++ : base64_decoding_table[(int)input[i++]];
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
    if (base64_decoding_table == NULL) {
        base64_decoding_table = malloc(123);
        for (int i = 0; i < 64; i++) {
            base64_decoding_table[(int)base64_encoding_table[i]] = i;
        }
    }
}

/**
 * Frees the memory allocated for the decoding table, and is
 * called by base64_decode.
 */
void base64_decoding_table_cleanup()
{
    free(base64_decoding_table);
    base64_decoding_table = NULL;
}

/**
 * This method takes in a string of user input and returns the
 * MD5 hash of the input as a newly allocated character array.
 * It is up to the caller of this method to free the allocated
 * memory.
 *
 * Example:
 *   char *text = "The quick brown fox jumps over the lazy dog.";
 *   char *md5_text = md5(text);
 *   printf("%s\n", md5_text);
 *   // Outputs e4d909c290d0fb1ca068ffaddf22cbd0
 *   free(md5_text);
 */
char *md5(char *input)
{
    size_t padded_length, offset;
 
    // Get the initial input length
    size_t initial_length = strlen(input);

    // Allocate space for the result
    uint8_t *result = (uint8_t *) malloc(16);

    // Set the length of the padding until length % 512 == 448
    for (padded_length = initial_length + 1; (padded_length) % (512/8) != (448/8); padded_length++);
    
    // Allocate memory for the message to be evaluated
    uint8_t *message = (uint8_t *) malloc(padded_length + 8);
    memcpy(message, input, initial_length);
    
    // Set the '1' after the initial message
    message[initial_length] = 0x80;
    
    // Fill the rest of the padding with zeros
    for(offset = initial_length + 1; offset < padded_length; offset++)
        message[offset] = 0;

    // Set the remaining 64 bits to hold the length of the initial input
    md5_to_bytes(initial_length << 0x03, message + padded_length);
    md5_to_bytes(initial_length >> 0x1D, message + padded_length + 4);

    uint32_t a, b, c, d, f, g, d_temp, w[16];

    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    // Loop through each 8 bytes at a time
    for (int i = 0; i < padded_length; i += (512/8)) {
        a = a0, b = b0, c = c0, d = d0;
        
        // Break the chunks into 32-bit integers
        for (int j = 0; j < 16; j++)
            w[j] = md5_to_int32(message + i + j * 4);
 
        // Operate on the 8 bytes, two at a time
        // See RFC 1321 3.4
        for(int j = 0; j < 64; j++) {
            if (j < 16) {
                f = (b & c) | ((~b) & d);
                g = j;
            } else if (j < 32) {
                f = (d & b) | ((~d) & c);
                g = ((5 * j) + 1) % 16;
            } else if (j < 48) {
                f = b ^ c ^ d;
                g = (3 * j + 5) % 16;          
            } else if (j < 64) {
                f = c ^ (b | (~d));
                g = (7 * j) % 16;
            }

            d_temp = d;
            d = c;
            c = b;
            b = b + MD5_LEFT_ROTATE((a + f + md5_k[j] + w[g]), md5_shift_amounts[j]);
            a = d_temp;
        }
        
        a0 += a;
        b0 += b;
        c0 += c;
        d0 += d;
    }

    md5_to_bytes(a0, result);
    md5_to_bytes(b0, result + 4);
    md5_to_bytes(c0, result + 8);
    md5_to_bytes(d0, result + 12);

    // Get a string of the hashed result
    char *hashed_string = md5_build_string(result);

    // Free allocated memory
    free(message);
    free(result);

    return hashed_string;
}

char *md5_build_string(uint8_t *result)
{
    char *output = malloc(sizeof(char) * 33);
    char a[3];
    for (int i = 0; i < 16; i++) {
        sprintf(a, "%2.2x", result[i]);
        strcat(output, a);
    }
    output[32] = '\0';
    return output;
}

void md5_to_bytes(uint32_t val, uint8_t *bytes)
{
    for (int i = 0; i < 4; i++) bytes[i] = (uint8_t) (val >> (i * 8));
}

uint32_t md5_to_int32(const uint8_t *bytes)
{
    return ((uint32_t) bytes[0] << 0x00) | ((uint32_t) bytes[1] << 0x08) |
           ((uint32_t) bytes[2] << 0x10) | ((uint32_t) bytes[3] << 0x18) ;
}