#include "global_define.h"

#include "doorUtils.h"
#include <p24F32KA301.h>
#include <libpic30.h>

void openDoor() {
    RELAY = ON;
    __delay_ms(1000);
    RELAY = OFF;
}

int checkCode() {
    int aux = TMR1;
    while (1) {
        if (PORTBbits.RB14 == 1) {

        }
    }
    return -1;
}
