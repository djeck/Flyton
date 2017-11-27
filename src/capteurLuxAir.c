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
    P1SEL &= ~(BIT4 | BIT7);
    P1SEL2 &= ~(BIT4 | BIT7);
    P1DIR &= ~(BIT4 | BIT7);
    P1REN &= ~(BIT4 | BIT7);
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
	int diff = railGauche() - railDroit();
	int seuilLuxAir = 8;
	if (diff > seuilLuxAir){
		tournerAngle(-30);
	}else if (diff < - seuilLuxAir){
		tournerAngle(30);
	}else{
		avancerVitesse(70);
	}
}
