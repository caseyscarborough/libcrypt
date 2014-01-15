#include "crypt.h"

char *rot13(char *str) {
    size_t i;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] > 64 && str[i] < 91) {
            str[i] += str[i] < 78 ? 13 : -13;
        } else if (str[i] > 96 && str[i] < 123) {
            str[i] += str[i] < 110 ? 13 : -13;
        }
    }
    return str;
}

char *rot47(char *str) {
    size_t i;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] > 32 && str[i] < 80) {
            str[i] += 47;
        } else if (str[i] > 79 && str[i] < 127) {
            str[i] -= 47;
        }
    }
    return str;
}