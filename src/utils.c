#include <msp430.h>
#include "utils.h"
/*
 * utils.c
 * Ce fichier contient les fonctions de base de MSP430 utiles
 *
 *  Created on: Nov 16, 2017
 *      Author: Wen
 */

void initGPIOPort1(int bit){
    P1SEL &= ~(bit);                        //force a 0
    P1SEL2 &= ~(bit);                       //force a 0
}
void initGPIOPort2(int bit){
    P2SEL &= ~(bit);                        //force a 0
    P2SEL2 &= ~(bit);                       //force a 0
}

void initEntree(int port, int bit){
    if(port ==1){
        initGPIOPort1(bit);                	//configurer a GPIO
        P1DIR &= ~(bit);                    //configurer a input
        P1REN |= bit;                       //mettre en route resistance de tirage
        P1OUT |= (bit);                     //mode pulled up
    }else if(port == 2){
        initGPIOPort2(bit);               	//configurer a GPIO
        P2DIR &= ~(bit);                    //configurer a input
        P2REN |= bit;                       //mettre en route resistance de tirage
        P2OUT |= (bit);                     //mode pulled up
    }
}

void initSortie(int port, int bit){
    if(port == 1){
        initGPIOPort1(bit);                	//configurer a GPIO
        P1DIR |= (bit);                     //P1DIR BIT0 a 1 pour mettre output
    }else if(port ==2){
        initGPIOPort2(bit);                	//configurer a GPIO
        P2DIR |= (bit);                     //P1DIR BIT0 a 1 pour mettre output
    }
}


/*
 * activeInterruption : activer l'interruption pour detection sur front montant
 * non teste
 * exemple :
 *          activeInterruption(1,BIT2); // activer l'interruption sur P1.2
 */
//void activeInterruption(int port, int bit){
//    if(port ==1){
//        P1IE |= bit;                        //activation du signal d interruption
//        P1IES |= bit;                       //Detection sur front montant
//    }else if(port == 2){
//        P2IE |= bit;                        //activation du signal d interruption
//        P2IES |= bit;                       //Detection sur front montant
//    }// est ce que je mets enable_interrupt?
//}

void delay(unsigned int ms)
{
	volatile unsigned int i=ms, z;
	while (i--) {
		z=100;
		while(z--);
	}
}
