#include "crypt.h"

char *rot13(char *s) {
    for(int i = 0; s[i] != '\0'; i++) {
        if (isupper(s[i]))
            s[i] += s[i] < 'N' ? 13 : -13;
        else if (islower(s[i]))
            s[i] += s[i] < 'n' ? 13 : -13;
    }
    return s;
}

char *rot47(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] > 32 && s[i] < 80)
            s[i] += 47;
        else if (s[i] > 79 && s[i] < 127)
            s[i] -= 47;
    }
    return s;
}