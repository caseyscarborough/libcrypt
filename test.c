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
    }
    return 0;
}