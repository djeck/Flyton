/*
 * capteurLuxSol.c
 *
 *  Created on: 22 nov. 2017
 *      Author: Marion & Oceane
 */
#include <msp430.h>
#include "ADC.h"

int flagArrivee;

void initLuxSol(){
    P1SEL &= ~(BIT1|BIT2);                    //force a 0//0x09
    P1SEL2 &= ~(BIT1|BIT2);
    P1DIR &= ~(BIT1|BIT2);
    ADC10AE0 |= (BIT1|BIT2);
}

int zoneBlancheGauche(){
//    int valeurZBGauche = 0;
//            ADC_Demarrer_conversion(6);
//            valeurZBGauche = ADC_Lire_resultat();
//            if (valeurZBGauche<=1000){
//                valeurZBGauche = 1;
//            }
//            else{
//                valeurZBGauche = 0;
//            }
//        return valeurZBGauche;
}

int zoneBlancheDroite(){
    int valeurZBDroite = 0;
            ADC_Demarrer_conversion(2);
            valeurZBDroite = ADC_Lire_resultat();
            if (valeurZBDroite<=950){
                valeurZBDroite = 1;
            }
            else{
                valeurZBDroite = 0;
            }
        return valeurZBDroite;
}

void detacteZoneBlancheDroiteEtArreter(){
	if (zoneBlancheDroite()){
		flagArrivee = 1;
	}
	return flagArrivee;
}
