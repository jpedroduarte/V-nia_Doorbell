
#ifndef GLOBAL_DEFINE_H
#define	GLOBAL_DEFINE_H

//#define FCY 121
#define FCY 15500

//TRIS
#define OPTOCOUPLER_TRIS    TRISAbits.TRISA6
#define RELAY_TRIS  TRISBbits.TRISB15
#define LED_TRIS    TRISBbits.TRISB7

//LAT / PORT
#define OPTOCOUPLER PORTAbits.RA6
#define RELAY       LATBbits.LATB15
#define LED         LATBbits.LATB7

#define ON  1
#define OFF 0

#define INPUT   1
#define OUTPUT  0

#endif	/* GLOBAL_DEFINE_H */

