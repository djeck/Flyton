/*
 * capteurLuxAir.c
 *
 *  Created on: 17 nov. 2017
 *      Author: 8673294
 */

#include <msp430.h>
#include "ADC.h"

#define COEF 0.5f

void initLuxAir()
{
    P1SEL &= ~(BIT4 | BIT7);
    P1SEL2 &= ~(BIT4 | BIT7);
    P1DIR &= ~(BIT4 | BIT7);
    P1REN &= ~(BIT4 | BIT7);	
    ADC10AE0 |= (BIT4 | BIT7);
}

int railGauche()
{
	ADC_Demarrer_conversion(4);
	int valeurRailGauche = 0;
	valeurRailGauche = ADC_Lire_resultat ();
	return valeurRailGauche;
}

int railDroit()
{
	ADC_Demarrer_conversion(7);
	int valeurRailDroit = 0;
	valeurRailDroit = ADC_Lire_resultat ();
	return valeurRailDroit;
}

void suivreLigneLumineux(){
	volatile int diff = railGauche() - railDroit();
	if (TACCR1 + TACCR2 < 100)
		avancerVitesse(50);
	tournerAngle(-(int)(diff*COEF));
}
