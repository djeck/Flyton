/*
 * capteurLuxAir.c
 *
 *  Created on: 17 nov. 2017
 *      Author: 8673294
 */

#include <msp430.h>
#include "ADC.h"

#define COEF 1.0f

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
	int seuilLuxAir = 4;
	/*if (diff > seuilLuxAir || diff < seuilLuxAir){
		float corr = ((float)(diff*COEF));
		tourner((int)(-corr)); // si diff - seuil = 8 => tourne -30
	}*/

	if (diff > 20) {
		P2OUT |= BIT1; //inverse sens de moteur A
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 10;
		TA1CCR2 = 75;
	} else if (diff < -20) {
		P2OUT &= ~BIT5;		    // inverse sens du moteur B
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 75;
		TA1CCR2 = 10;
	} else if (diff > 10) {
		P2OUT &= ~BIT1;		    //sens avant de moteur A
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 20;
		TA1CCR2 = 75;
	} else if (diff < -10) {
		P2OUT &= ~BIT1;		    //sens avant de moteur A
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 75;
		TA1CCR2 = 20;
	} else if (diff > 7) {
		P2OUT &= ~BIT1;		    //sens avant de moteur A
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 50;
		TA1CCR2 = 75;
	} else if (diff < -7) {
		P2OUT &= ~BIT1;		    //sens avant de moteur A
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 75;
		TA1CCR2 = 50;
	} else if (diff > 3) {
		P2OUT &= ~BIT1;		    //sens avant de moteur A
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 63;
		TA1CCR2 = 75;
	} else if (diff < -3) {
		P2OUT &= ~BIT1;		    //sens avant de moteur A
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 75;
		TA1CCR2 = 63;
	} else {
		P2OUT &= ~BIT1;		    //sens avant de moteur A
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR1 = 70;
		TA1CCR2 = 70;
	}
}
