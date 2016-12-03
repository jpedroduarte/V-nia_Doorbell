#include "global_define.h"

#include "doorUtils.h"
#include <p24F32KA301.h>
#include <libpic30.h>

void RGB(char color) {

    switch (color) {
        case 'r':
            TRISBbits.TRISB1 = 1;
            TRISBbits.TRISB2 = 1;
            TRISBbits.TRISB0 = 0;
            break;
        case 'g':
            TRISBbits.TRISB0 = 1;
            TRISBbits.TRISB2 = 1;
            TRISBbits.TRISB1 = 0;
            break;
        case 'b':
            TRISBbits.TRISB0 = 1;
            TRISBbits.TRISB1 = 1;
            TRISBbits.TRISB2 = 0;
            break;
    }
}

void openDoor() {
    //RGB('g');
    LATBbits.LATB15 = 1 - INVERT;
    __delay_ms(1000);
    LATBbits.LATB15 = 0 + INVERT;
    //RGB(0);
}

int checkCode() {
    int aux = TMR1;
    while (1) {
        if (PORTBbits.RB14 == 1) {

        }
    }


    return -1;
}
