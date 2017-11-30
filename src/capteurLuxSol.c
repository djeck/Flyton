/*
 * capteurLuxSol.c
 *
 *  Created on: 22 nov. 2017
 *      Author: Marion & Oceane
 */
#include <msp430.h>
#include "ADC.h"

void initLuxSol(){
    P1SEL &= ~(BIT2);
    P1SEL2 &= ~(BIT2);
    P1DIR &= ~(BIT2);
    ADC10AE0 |= (BIT2);
}

int zoneBlanche(){
    int valeurZBDroite = 0;
            ADC_Demarrer_conversion(2);
            valeurZBDroite = ADC_Lire_resultat();
            if (valeurZBDroite<=800){
                valeurZBDroite = 1;
            }
            else{
                valeurZBDroite = 0;
            }
        return valeurZBDroite;
}

