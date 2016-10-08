#include "doorUtils.h"

void openDoor(){
    LATBbits.LATB15 = 1;
}

int checkCode(){
    int aux = TMR1;
    while(1){
        if (PORTBbits.RB14 == 1){
            
        }
    }
    
    
    return -1;
}
