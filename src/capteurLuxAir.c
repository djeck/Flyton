/*
 * capteurLuxAir.c
 *
 *  Created on: 17 nov. 2017
 *      Author: 8673294
 */

#include <msp430.h>
#include "ADC.h"

void initLuxAir()
{
    P1SEL &= ~(BIT1 | BIT2 | BIT3 | BIT4);
    P1SEL2 &= ~(BIT1 | BIT2 | BIT3 | BIT4);
    P1DIR &= ~(BIT1 | BIT2 | BIT3 | BIT4);
    P1REN &= ~(BIT1 | BIT2 | BIT3 | BIT4);
}

int railGauche()
{
	ADC_Demarrer_conversion(1);
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

