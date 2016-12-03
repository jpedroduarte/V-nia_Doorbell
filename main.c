//#define FCY 15500

#include "global_define.h"
#include <p24F32KA301.h>
#include <libpic30.h>
#include <stdio.h>

#include "config.h"
#include "doorUtils.h"
#include "morseUtils.h"

int nseq = 0;

void __attribute__((__interrupt__, auto_psv)) _IC1Interrupt(void) {
    IFS0bits.IC1IF = 0; //resets and reenables the Rx1 interrupt flag

    if (IC1BUF <= max_time_ticks) {

    }
}

int main(void) {

    int a;

    //UART
    //U1MODEbits.UARTEN = 1;
    //U1MODEbits.BRGH = 1;
    //U1STAbits.UTXEN = 1;
    //U1BRG = 2;

    //printf("Welcome UART1 :D\r");

    TRISBbits.TRISB14 = 1;
    // ADC
    ANSA = 0; //Port A is digital input
    ANSB = 0; //Port B is digital input
    ANSB += 0x4000; //B14
    AD1CHSbits.CH0SA = 0b01010;
    AD1CON1bits.ADON = 1;
    AD1CON1bits.SSRC = 0b0100;
    AD1CON1bits.ASAM = 1;
    
    AD1CON5bits.CTMUREQ = 1;

    // CTMU Setup
    CTMUICONbits.IRNG = 0x3; // Current Range
    CTMUCON1bits.CTMUEN = 1; // Turn on CTMU
    AD1CTMUENLbits.CTMEN10 = 1;
     CTMUCON1bits.EDGEN = 1;
CTMUCON1bits.CTTRIG = 1;
    //CTMUCON2bits.EDG1MOD = 1;
    //CTMUCON2bits.EDG2MOD = 1;
    
    // I/O pins
    TRISAbits.TRISA6 = 1;
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB7 = 0;
    LED = 0;



    CLKDIVbits.DOZE = 0b111; //Divide frequency by 128
    //CLKDIVbits.DOZEN = 1; //Enable DOZE

    // Input Capture
    //IEC0bits.IC1IE = 1; //Enable interrupt Input Capture 1

    //IC1CON1bits.ICM = 0b011; //Every Rising edge
    //IC1CON1bits.IC1TSEL = 0b111; //System clock
    //IC1CON2bits.ICTRIG = 1; //Start with trigger
    //IC1CON2bits.SYNCSEL = 0b10100; //Input Capture 1 is the trigger (?)
    //IC1CON2bits.TRIGSTAT = 0b11000; //Waiting for trigger

    TRISBbits.TRISB15 = 0;


    /*
    PR1=5000;

    T1CONbits.TCS=0;
    T1CONbits.TCKPS=0;

    T1CONbits.TON=1;
    TMR1=0;*/

    LATBbits.LATB15 = 0 + INVERT;

    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
    LATBbits.LATB2 = 0;

    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    
    LATBbits.LATB0 = 1;
    LATBbits.LATB1 = 1;
    LATBbits.LATB2 = 1;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;

    T1CONbits.TON = 1;
    PR1 = 50;
    
    T2CONbits.TON = 1;
    PR2 = 16;
    
    OC3CON1bits.OCM = 0b111;
    OC3CON2bits.SYNCSEL = 0b01100;
    OC3RS = PR2;
    OC3R = PR2;
    
    OC2CON1bits.OCM = 0b111;
    OC2CON2bits.SYNCSEL = 0b01100;
    OC2RS = PR2;
    OC2R = PR2;
    
    
    while (1) {
        //LATBbits.LATB2 = !LATBbits.LATB2 ;


        //AD1CON1bits.SAMP = 0;
        //__delay_ms(50);

        if (PORTAbits.RA6 == 0 + INVERT) {
            LED = 1;
            //RGB('b');
            __delay_ms(1000);
            openDoor();
            LED = 0;
        } else {
            // LATBbits.LATB15 = 0;
        }
        //RGB('r');

        
        //if(checkCode())
          //  openDoor();
/*        while(AD1CON1bits.DONE == 0)
        {
            printf(".");
        }
        AD1CON1bits.DONE = 0;
        a = ADC1BUF0;
        printf("%4i\r", a);
        a=a*2-1024;
        if(a<512)
        {
            OC3R = 0;
            OC2R = (512-a)>>5;
        }
        else
                  {
            OC3R = (a-512)>>5;
            OC2R = 0;
        }  
*/
      
  
    }
    return 0;
}

