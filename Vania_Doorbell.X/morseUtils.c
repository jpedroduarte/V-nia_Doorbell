//TODO getMorseSequence function

#include "morseUtils.h"

extern const unsigned char morse[36];

int getMorse(char c){
    if(c>='A' && c<='Z')
        return morse[c-'A'];
    else if(c>='a' && c<='z')
        return morse[c-'a'];
    else if(c>='0' && c<='9')
        return morse[alphabet_size+c-'0'];
    return -1;
}
