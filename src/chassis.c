/*
 * chassis.c
 *
 *  Created on: 17 nov. 2017
 *      Author: a.detrez.14 and Wen
 */
#include <msp430.h>
#include "chassis.h"
#include "utils.h"
#include "PID.h"



void initPWM()
{
	TA1CTL = TASSEL_2 | MC_0 | ID_1; // source SMCLK pour le timer, mode UP, 2 times divider
	TA1CCTL1 |= OUTMOD_7; // activation mode de sortie 7 (PWM)
	TA1CCTL2 |= OUTMOD_7; // activation mode de sortie 7 (PWM)

	TA1CCR0 = 100;

}
void initMoteurs()
{
	initSortie(2,BIT2); // PWM moteur A (gauche)
	P2SEL |= BIT2; 		// selection fonction Timer1_A3.TA1
	P2SEL2 &= ~BIT2; 	// selection fonction Timer1_A3.TA1

	initSortie(2,BIT1); // sens moteur A
	P2OUT &= ~BIT1; 	// sens avant moteur A

	initSortie(2,BIT4); // PWM moteur B
	P2SEL |= BIT4; 		// selection fonction Timer1_A3.TA2
	P2SEL2 &= ~BIT4; 	// selection fonction Timer1_A3.TA2

	initSortie(2,BIT5); // sens moteur B
	P2OUT |= BIT5; 		// sens avant moteur B

	initPWM();
}


/*
 * initChassis : public
 * Initialise les roues moteurs
 */
void initChassis()
{
	initMoteurs();
}

/*
 * avancerVitesse : avant le robot en passant meme rapport cyclique sur deux roues
 */
void avancerVitesse(int vitesse)
{
	P2OUT &= ~BIT1; 	// sens avant moteur A
	P2OUT |= BIT5; 		// sens avant moteur B
	TA1CCR1 = vitesse; 		// gauche
	TA1CCR2 = vitesse; 		// droite
	TA1CTL |= MC_1;
}

/*
 * tournerAngle : tourner le robot en gardant la meme vitesse moyenne
 * angle: 127 -> tourner sur place vers la droite
 * 		 -127 -> tourner sur place vers la gauche
 */
void tournerAngle(signed int angle)	//tested
{
	volatile float vitesseMoy = (TA1CCR1+TA1CCR2)/2;

	if(angle >= -127 && angle <= -63 ) {
		P2OUT |= BIT1;		//inverse sens de moteur A
		P2OUT |= BIT5; 		// sens avant moteur B
		TA1CCR1 = (int)((vitesseMoy/(127-63)) * (-angle-63));
		TA1CCR2 = (int)((vitesseMoy/(127-63)) * ((127+63) + angle));

	}else if(angle > -63 && angle < 63 ){
		P2OUT &= ~BIT1; 	// sens avant moteur A
		P2OUT |= BIT5; 		// sens avant moteur B
		TA1CCR1 = (int)((vitesseMoy/(127-63)) * (angle + (127-63)));
		TA1CCR2 = (int)((vitesseMoy/(127-63)) * ((127-63) - angle));

	}else if(angle >= 63 && angle <= 127 ){
		P2OUT &= ~BIT1; 	// sens avant moteur A
		P2OUT &= ~BIT5; 	// inverse sens de moteur B
		TA1CCR1 = (int)((vitesseMoy/(127-63)) * ((- angle) + (127+63)));
		TA1CCR2 = (int)((vitesseMoy/(127-63)) * ((-127+63) + angle));
	}
}

/*
 * arreter : arret complet du robot
 */
void arreter()
{
	TA1CCR1 = 0;
	TA1CCR2 = 0;
}
