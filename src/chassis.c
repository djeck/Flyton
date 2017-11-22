/*
 * chassis.c
 *
 *  Created on: 17 nov. 2017
 *      Author: a.detrez.14
 */
#include <msp430.h>
#include "chassis.h"
#include "utils.h"

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

void initPID()//interruption toute 100 ms
{
	// 100 ms timer
	TA0CTL = 0 | (TASSEL_2 | ID_3); // 8 divider
	//TA0CTL |= MC_1; // up
	TA0CTL |= MC_0; // stop
	TA0CTL |= TAIE;
	TA0CCR0 = 12500;
	__enable_interrupt();
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
	initPID();
}

void avancer(int vitesse, int distance)
{

	P2OUT &= ~BIT1; 	// sens avant moteur A
	P2OUT |= BIT5; 		// sens avant moteur B
	TA1CCR1 = vitesse; 		// gauche
	TA1CCR2 = vitesse; 		// droite
	TA1CTL |= MC_1;
	// TODO
}

void avancerVitesse(int vitesse)
{
	P2OUT &= ~BIT1; 	// sens avant moteur A
	P2OUT |= BIT5; 		// sens avant moteur B
	TA1CCR1 = vitesse; 		// gauche
	TA1CCR2 = vitesse; 		// droite
	TA1CTL |= MC_1;
}

/*
 * valeur positive pour tourner a droite
 */
void tourner(signed int correction)
{
	int roueGauche;
	if((P2OUT & BIT1) == 0){	// si la roue A est en sens avant
		roueGauche = TA1CCR1 + correction;
	}else{
		roueGauche = TA1CCR1 - correction;
	}

	int roueDroite;
	if((P2OUT & BIT5) == BIT5){	// si la roue gauche est en sens avant
		roueDroite = TA1CCR2 - correction;
	}else{
		roueDroite = TA1CCR2 + correction;
	}

	if(roueGauche < 0){
		P2OUT |= BIT1;		//inverse sens de moteur A
		TA1CCR1 = -roueGauche;
	}else{
		P2OUT &= ~BIT1;		//sens avant de moteur A
		TA1CCR1 = roueGauche;
	}

	if(roueDroite < 0){
		P2OUT &= ~BIT5;		// inverse sens du moteur B
		TA1CCR2 = -roueDroite;
	}else{
		P2OUT |= BIT5;		//sens avant de moteur B
		TA1CCR2 = roueDroite;
	}

}

/*
 * angle: 127 -> tourner sur place vers la droite
 * 		 -127 -> tourner sur place vers la gauche
 *
 */
void tournerAngle(signed int angle)	//tested
{
	float vitesseMoy = (TA1CCR1+TA1CCR2)/2;
	if(angle >= -127 && angle <= -63 ) {
		P2OUT |= BIT1;		//inverse sens de moteur A
		P2OUT |= BIT5; 		// sens avant moteur B
		float val1 = (vitesseMoy/(127-63));
		float val2 = val1 * (-angle-63);
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

void arreter()
{
	TA1CCR1 = 0;
	TA1CCR2 = 0;
}


