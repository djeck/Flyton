/*
 * capteurInfrarouge.c
 *
 *  Created on: 17 nov. 2017
 *      Author: Marion & Oceane
 */

#include <msp430.h>

int valeurSeuilIR = 100;

void initInfrarouge(){
    P1SEL &= ~(BIT5);                    //force a 0//0x09
    P1SEL2 &= ~(BIT5);
    P1DIR &= ~(BIT5);                    //P1DIR BIT5 a 0 pour mettre input
}

int obstacle(){
    int valeurIR = 1000;
        ADC_Demarrer_conversion(5);
        valeurIR = ADC_Lire_resultat();
        if (valeurIR>=valeurSeuilIR){
            valeurIR = 1;
        }
        else{
            valeurIR = 0;
        }
    return valeurIR;
}
