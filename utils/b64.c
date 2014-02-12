/**
 * Base64 Converter
 *
 * Copyright 2014 (c) Casey Scarborough
 * https://github.com/caseyscarborough/libcrypt
 *
 * Description:
 *
 *   This utility takes encodes text from one file into Base64 encoded data into
 *   another file. It will also decode the Base64 data from one file back into
 *   text in another file.
 *
 *   For example:
 *     // Encode data from one file into another
 *     b64 -e data.txt output.txt
 *
 *     // Decode data from one file to another
 *     b64 -d base64_data.txt output.txt
 *
 *     // Display help menu
 *     b64 -h
 *
 *   This utility also relies on the libcrypt library, which is available at
 *   https://github.com/caseyscarborough/libcrypt.
 *   You can compile this by placing crypt.h and crypt.c in the same directory
 *   and issuing the following commands:
 *   
 *     gcc -c b64.c -o b64.o
 *     gcc b64.o crypt.o -o b64
 *
 * License:
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *   
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *   
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#include "../src/crypt.h"
#include <errno.h>

void die(char *error)
{
    printf("%s\n", error);
    exit(1);
}

void print_usage_menu()
{
    printf("Usage: b64 -option <input-file> <output-file>\n");
    printf("  -e     Encode input file to output file\n");
    printf("  -d     Decode input file to output file\n");
    printf("  -h     Display this help menu\n");
    exit(1);
}

int main(int argc, char **argv)
{
    FILE *input_file, *output_file;
 
    if (argc < 4) {
        print_usage_menu();
        return 1;
    } else if (strncmp(argv[1], "-h", 2) == 0) {
        print_usage_menu();
        return 0;
    } else if (strncmp(argv[1], "-d", 2) == 0 || strncmp(argv[1], "-e", 2) == 0) {
        char *input_filename = argv[2];
        char *output_filename = argv[3];
        int i;

        input_file = fopen(argv[2], "r");
        if (input_file == NULL) {
            die("ERROR: Could not open input file");
        }

        output_file = fopen(argv[3], "w");
        if (output_file == NULL) {
            die("ERROR: Could not open output file");
        }

        if (strncmp(argv[1], "-d", 2) == 0) {
            printf("Decoding %s into %s...\n", input_filename, output_filename);

            char word[5];
            while (feof(input_file) == 0) {
                for (i = 0; i < 4; i++)
                    word[i] = getc(input_file);
                word[i] = '\0';

                if (feof(input_file) == 0) {
                    char *decoded_data = base64_decode(word);
                    fputs(decoded_data, output_file);
                    free(decoded_data);
                }
            }
        } else if (strncmp(argv[1], "-e", 2) == 0) {
            printf("Encoding %s into %s...\n", input_filename, output_filename);

            char word[4];
            while (feof(input_file) == 0) {
                for (i = 0; i < 3; i++)
                    word[i] = getc(input_file);
                word[i] = '\0';

                if (feof(input_file) == 0) {
                    char *encoded_data = base64_encode(word);
                    fputs(encoded_data, output_file);
                    free(encoded_data);
                }
            }
        }
    } else {
        printf("Incorrect option '%s'\n", argv[1]);
        print_usage_menu();
    }
    return 0;
}