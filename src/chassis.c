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


volatile unsigned long int cmpt_a = 0;
volatile unsigned long int cmpt_b = 0;

#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
	if ((P2IN & BIT0) == BIT0) { // moteur A
		cmpt_a++;
	}
	if ((P2IN & BIT3) == BIT3) { // moteur B
		cmpt_b++;
	}
	P2IFG = 0;
}

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

void initOptoCoupleur()
{
	initEntree(2,BIT0); // opto-coupleur moteur A
	P2IE |= BIT0;       //activation du signal d interruption
	P2IES |= BIT0;

	initEntree(2,BIT3); // opto-coupleur moteur B
	P2IE |= BIT3;       //activation du signal d interruption
	P2IES |= BIT3;

	_enable_interrupt();
}

/*
 * initChassis : public
 * Initialise les roues moteurs, les opto coupleur,
 * et timer pour regulation PID
 */
void initChassis()
{
	initMoteurs();
	initOptoCoupleur();
	initPID();
}

/*
 * avancer : avancer le robot avec une vitesse a une certaine distance
 * <!!>pour instant pareil que avancerVitesse
 */
void avancer(int vitesse, int distance)
{
	P2OUT &= ~BIT1; 	// sens avant moteur A
	P2OUT |= BIT5; 		// sens avant moteur B
	TA1CCR1 = vitesse; 		// gauche
	TA1CCR2 = vitesse; 		// droite
	TA1CTL |= MC_1;
	// TODO
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
 * tourner : tourner le robot avec une petite correction
 * parametres :
 *      correction : valeur positive pour tourner a droite,
 *      cette valeur ne doit pas etre tres grande par rapport a TA1CCR1 et TA1CCR2
 */
void tourner(signed int correction)
{
	volatile int roueGauche;
	volatile int roueDroite;

	// si la roue A est en sens avant
	if((P2OUT & BIT1) == 0){
		roueGauche = TA1CCR1 + correction;
	}else{
		roueGauche = TA1CCR1 - correction;
	}

	// si la roue gauche est en sens avant
	if((P2OUT & BIT5) == BIT5){
		roueDroite = TA1CCR2 - correction;
	}else{
		roueDroite = TA1CCR2 + correction;
	}

	// si la valeur de calcule est negative, inverse la
	if(roueGauche < 0){
		P2OUT |= BIT1;		    //inverse sens de moteur A
		TA1CCR1 = -roueGauche;
	}else{
		P2OUT &= ~BIT1;		    //sens avant de moteur A
		TA1CCR1 = roueGauche;
	}
	if(roueDroite < 0){
		P2OUT &= ~BIT5;		    // inverse sens du moteur B
		TA1CCR2 = -roueDroite;
	}else{
		P2OUT |= BIT5;		    //sens avant de moteur B
		TA1CCR2 = roueDroite;
	}
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
