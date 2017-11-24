/*
 * capteurLuxSol.c
 *
 *  Created on: 22 nov. 2017
 *      Author: Marion & Oceane
 */
#include <msp430.h>
#include "ADC.h"

void initLuxSol(){
    P1SEL &= ~(BIT3|BIT4);                    //force a 0//0x09
    P1SEL2 &= ~(BIT3|BIT4);
    P1DIR &= ~(BIT3|BIT4);
}

int zoneBlancheGauche(){
    int valeurZBGauche = 0;
            ADC_Demarrer_conversion(3);
            valeurZBGauche = ADC_Lire_resultat();
            if (valeurZBGauche<=1000){
                valeurZBGauche = 1;
            }
            else{
                valeurZBGauche = 0;
            }
        return valeurZBGauche;
}

int zoneBlancheDroite(){
    int valeurZBDroite = 0;
            ADC_Demarrer_conversion(4);
            valeurZBDroite = ADC_Lire_resultat();
            if (valeurZBDroite<=1000){
                valeurZBDroite = 1;
            }
            else{
                valeurZBDroite = 0;
            }
        return valeurZBDroite;
}

