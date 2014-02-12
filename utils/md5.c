/**
 * MD5 Hasher
 *
 * Copyright 2014 (c) Casey Scarborough
 *
 * Description:
 *
 *   This utility will MD5 hash the contents of a string or given file and
 *   print the resulting hash out to the console.
 *
 *   For example:
 *     // Hash a string
 *     md5 -s "The quick brown fox jumps over the lazy dog."
 *     e4d909c290d0fb1ca068ffaddf22cbd0
 *
 *     // Hash a file
 *     md5 -f sample.txt
 *     322a166e1402bd9ff18e1ce67fe69e61  sample.txt
 *
 *     // Display help menu
 *     md5 -h
 *
 *   This utility also relies on the libcrypt library, which is available at
 *   https://github.com/caseyscarborough/libcrypt.
 *   You can compile this by placing crypt.h and crypt.c in the same directory
 *   this utility and issuing the following command:
 *   
 *     gcc crypt.c md5.c -o md5
 *
 *   OR run `make` from inside the libcrypt project where this utility is located.
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

void print_usage_menu()
{
    printf("Usage: md5 -option <string>|<input-file>\n");
    printf("  -s     Hash a string and print to the console\n");
    printf("  -f     Hash a file's contents and print to the console\n");
    printf("  -h     Display this help menu\n");
}

int main(int argc, char **argv)
{ 
    if (argc < 3) {
        print_usage_menu();
        return 1;
    } else if (strncmp(argv[1], "-h", 2) == 0) {
        print_usage_menu();
        return 0;
    } else if (strncmp(argv[1], "-s", 2) == 0) {
        char *input = argv[2];
        char *hashed_input = md5(input);
        printf("%s\n", hashed_input);
    } else if (strncmp(argv[1], "-f", 2) == 0) {
        FILE *input_file;
        char *input_filename = argv[2];
        long input_file_size;
        char *input_file_contents;
        char *md5_hashed_contents;

        input_file = fopen(input_filename, "rb");
        if (input_file == NULL) {
            perror(input_filename);
            exit(1);
        }
        fseek(input_file, 0, SEEK_END);
        input_file_size = ftell(input_file);
        rewind(input_file);

        input_file_contents = malloc((input_file_size + 1) * sizeof(char));
        fread(input_file_contents, sizeof(char), input_file_size, input_file);
        fclose(input_file);
        
        input_file_contents[input_file_size] = '\0';
        md5_hashed_contents = md5(input_file_contents);
        printf("%s  %s\n", md5_hashed_contents, input_filename);

        free(md5_hashed_contents);
        free(input_file_contents);
    } else {
        printf("Incorrect option '%s'\n", argv[1]);
        print_usage_menu();
        return 1;
    }
    return 0;
}