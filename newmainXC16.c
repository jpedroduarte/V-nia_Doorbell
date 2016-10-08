/*
 * File:   newmainXC16.c
 * Author: Red
 *
 * Created on 8 de Outubro de 2016, 16:11
 */

#define FCY 15500
#include <p24F32KA301.h>
#include <libpic30.h>


/*My includes*/
#include "doorUtils.h"

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Enable Configuration bit (CLKO output signal is active on the OSCO pin)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)

#define max_time_ticks 330
int nseq=0;



void __attribute__((__interrupt__, auto_psv)) _IC1Interrupt(void) {
    IFS0bits.IC1IF = 0; //resets and reenables the Rx1 interrupt flag
    
    if(IC1BUF <= max_time_ticks){
        
    }
    
    
}


int main(void) {
    ANSA = 0;
    ANSB = 0;

    /*Enable interrupt Input Capture 1*/
    IEC0bits.IC1IE=1;
    
    /*Input Capture 1*/
    IC1CON1bits.ICM=0b011;
    IC1CON1bits.ICI=0;
    IC1CON1bits.IC1TSEL=0b111;
    
    
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 1;
    PR1=5000;

    T1CONbits.TCS=0;
    T1CONbits.TCKPS=0;

    T1CONbits.TON=1;
    TMR1=0;
    
    while (1) {
        /*
        if(checkCode())
            openDoor();*/
    }
    return 0;
}

