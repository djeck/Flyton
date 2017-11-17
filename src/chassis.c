/*
 * chassis.c
 *
 *  Created on: 17 nov. 2017
 *      Author: a.detrez.14
 */
#include <msp430.h>
#include "chassis.h"

unsigned long int cmpt_a = 0;
unsigned long int cmpt_b = 0;

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

void initChassis()
{
	initMoteurs();
	initOptoCoupleur();
}

void avancer(int vitesse, int distance)
{
	TA1CCR1 = vitesse; 		// gauche
	TA1CCR2 = vitesse; 		// droite
	TA1CTL |= MC_1;
	// TODO
}

void avancerVitesse(int vitesse)
{
	TA1CCR1 = vitesse; 		// gauche
	TA1CCR2 = vitesse; 		// droite
	TA1CTL |= MC_1;
}

void arreter()
{
	TA1CCR1 = 0;
	TA1CCR2 = 0;
}
