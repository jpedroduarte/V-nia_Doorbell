//#define FCY 15500

#include "global_define.h"
#include <p24F32KA301.h>
#include <libpic30.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "doorUtils.h"
#include "morseUtils.h"
#include "morseDump.h"

#define DOT_SIZE 40
#define ABS(x) (((x)>0)?(x):-(x))

typedef struct centro {
    int npontos;
    int x;
    int soma;
    int lastx;
} centro;

typedef struct ponto {
    int centro;
    int x;
} ponto;

int kmeans(ponto * pts, int npontos) {
    int i;
    int min, max, temp, doagain;
    centro ctr[2];

    min = pts[0].x;
    max = pts[0].x;

    for (i = 1; i < npontos; ++i) {
        if (pts[i].x > max)
            max = pts[i].x;
        if (pts[i].x < min)
            min = pts[i].x;
    }


    ctr[0].x = min;
    ctr[1].x = max;



    do {
        ctr[0].npontos = 0;
        ctr[1].npontos = 0;
        ctr[0].soma = 0;
        ctr[1].soma = 0;

        doagain = 0;
        for (i = 0; i < npontos; ++i) {
            //printf("%i\tteste: \t%i\t%i\t",i,ABS(pts[i].x-ctr[0].x),  ABS(pts[i].x-ctr[1].x) );
            if (ABS(pts[i].x - ctr[0].x) < ABS(pts[i].x - ctr[1].x))
                temp = 0;
            else
                temp = 1;

            pts[i].centro = temp;
            ctr[temp].npontos += 1;
            ctr[temp].soma += pts[i].x;
            //printf("ctr[%2i].npontos = %i\r\n", temp, ctr[temp].npontos);
        }


        for (i = 0; i < 2; ++i) {
            if (ctr[i].npontos > 0) {
                ctr[i].x = ctr[i].soma / ctr[i].npontos;
                //printf("problema %i\t%i\r\n", ctr[i].soma, ctr[i].npontos );
                if (ctr[i].x != ctr[i].lastx)
                    doagain = 1;
                ctr[i].lastx = ctr[i].x;
            }
        }


        /*
                printf("pontos:\r\n");
                for(i = 0; i<npontos; ++i)
                    printf("%i\t%i\t%i\n",	i, pts[i].x, pts[i].centro);
			
                printf("\r\n");
         */
    } while (doagain == 1);
    /*
        printf("centros:\r\n");
        for (i = 0; i < 2; ++i)
            printf("%i\t%i\r\n", i, ctr[i].x);
     */
    return 0;
}

int nseq = 0;

ponto goodones[DOT_SIZE];
ponto badones[DOT_SIZE];
int k = -1;

void __attribute__((__interrupt__, auto_psv)) _IC1Interrupt(void) {
    IFS0bits.IC1IF = 0; //resets and reenables the Rx1 interrupt flag

    static unsigned int ic, lastic;
    unsigned delta;
    static char state = 'g';

    ic = IC1BUF;
    delta = ic - lastic;
    if ((delta < 372U) && (delta > 248U)) {
        ++goodones[k].x;
        state = 'g';
    } else {
        if (state == 'g') {
            k >= 9 ? k = 0 : ++k;
            badones[k].x = (int) delta / TICKS_20MS;
        } else {
            badones[k].x += (int) delta / TICKS_20MS;
        }
        state = 'b';
    }
    lastic = ic;
}

int main(void) {
    //UART
    U2MODEbits.UARTEN = 1;
    U2MODEbits.BRGH = 1;
    U2STAbits.UTXEN = 1;
    U2BRG = 2;
    __C30_UART = 2;

    printf("Welcome UART2 :D\r\n");

    // Analog
    ANSA = 0; //Port A is digital input
    ANSB = 0; //Port B is digital input

    // I/O pins
    OPTOCOUPLER_TRIS = INPUT;
    RELAY_TRIS = OUTPUT;
    LED_TRIS = OUTPUT;

    RELAY = OFF;
    LED = OFF;

    //CLKDIVbits.DOZE = 0b111; //Divide frequency by 128
    //CLKDIVbits.DOZEN = 1; //Enable DOZE

    // Input Capture
    IEC0bits.IC1IE = 1; //Enable interrupt Input Capture 1

    IC1CON1bits.ICM = 0b011; //Every Rising edge
    IC1CON1bits.IC1TSEL = 0b111; //System clock
    IC1CON2bits.ICTRIG = 1; //Start with trigger
    IC1CON2bits.SYNCSEL = 0b10100; //Input Capture 1 is the trigger (?)
    IC1CON2bits.TRIGSTAT = 0b1; //Waiting for trigger

    //T2CONbits.TON = 1;
    //PR2 = TICKS_20MS-1;



    OC3CON1bits.OCTSEL = 0b111;
    OC3CON2bits.SYNCSEL = 0x1F;
    OC3CON2bits.OCTRIG = 0;
    OC3RS = 288;
    OC3R = 145;
    OC3CON1bits.OCM = 0b110;
    /*
        OC2CON1bits.OCM = 0b111;
        OC2CON2bits.SYNCSEL = 0b01100;
        OC2RS = PR2;
        OC2R = PR2;*/

    int i = 0;
    char texto[10];

    while (1) {
        int h = 1;
        int t = 0;
        int j = 0;
        int m = 0;
        if (OPTOCOUPLER == 0) {
            LED = 1;
            __delay_ms(6000);
            LED = 0;
            kmeans(badones + 1, k);
            badones[0].centro = 2;
            badones[k + 1].centro = 1;
            kmeans(goodones, k + 1);
            for (i = 0; i < k + 1; ++i) {

                printf("%i %i\r\n", badones[i].centro, goodones[i].centro);
                goodones[i].x = 0;
                badones[i].x = 0;

                if (badones[i + 1].centro == 1) {
                    texto[t] = (h << 5);
                    m = h;
                    for (j = i; j > (i - h); --j) {
                        texto[t] += goodones[j].centro << (h - m);
                        --m;
                    }
                    t += 1;
                    h = 1;
                } else {
                    ++h;
                }
            }
            k = -1;
            printf("\n\r");


            for (i = 0; i < t; ++i) {
                //printf("%x\t", texto[i]);
                for (j = 0; morse[j] != texto[i]; ++j)
                    if (j > 35) break;

                //printf("%c", j + 65);
                texto[i] = (char) (j + 65);

            }
            for (i = t; i < 10; ++i)
                texto[i] = 0;

            printf("\n\r%s\n\r", texto);


        } else {
            ;

            // LATBbits.LATB15 = 0;
        }

        char cod[3] = "SAM";
        if (strcmp(texto, cod) == 0) {
            LED = 1;
            openDoor();
            LED = 0;
            for (i = 0; i < 10; ++i)
                texto[i] = 0;

        }
    }
    return 0;
}

