/*
 * capteurInfrarouge.c
 *
 *  Created on: 17 nov. 2017
 *      Author: Marion & Oceane
 */

#include <msp430.h>
#include "ADC.h"
#include "capteurInfrarouge.h"
#include "chassis.h"
#include "utils.h"

int valeurSeuilIR = 350;

void initInfrarouge(){
    P1SEL &= ~(BIT5);                    //force a 0//0x09
    P1SEL2 &= ~(BIT5);
    P1DIR &= ~(BIT5);                    //P1DIR BIT5 a 0 pour mettre input
    ADC10AE0 |= BIT5;
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

void detacteObstacleEtArreter(){
	volatile int detectionObstacle = 1000;//pour pas qu il s arrete pas au debut
	detectionObstacle = obstacle();
	if (detectionObstacle == 1) {
		P1OUT |= BIT6;
		arreter();
		delay(1000);
	} else {
		P1OUT &= ~BIT6;
		avancerVitesse(85);
		suivreLigneLumineux();
		delay(50);
	}
}
