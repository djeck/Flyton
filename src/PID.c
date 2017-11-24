/*
 * PID.c
 *
 *  Created on: Nov 22, 2017
 *      Author: Wen
 */
#include <msp430.h>
#include "PID.h"
#include "chassis.h"


volatile unsigned long int cmpt_a = 0;
volatile unsigned long int cmpt_b = 0;

unsigned short int enable_pid = 0;

#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
	if ((P2IN & BIT0) == 0) { // moteur A
		cmpt_a++;
		P2IFG &= ~BIT0;		//remettre que le Flag de BIT0 a 0, car on a traite que celui de BIT0
	}
	if ((P2IN & BIT3) == 0) { // moteur B
		cmpt_b++;
		P2IFG &= ~BIT3;		//remettre que le Flag de BIT3 a 0, car on a traite que celui de BIT3
	}
}

//timer 1 interrupt for PID regulations
#pragma vector = TIMER0_A1_VECTOR
__interrupt void PIDAjouster(void)
{
	if (enable_pid == 1) {
		if (cmpt_a > compt_b) {
			tourner(compt_b-compt_a);
		} else if (cmp_b < cmpt_a) {
			tourner(compt_a-compt_b);
		}
		TA0CTL &= ~TAIFG;
	}
}

void activerPID(unsigned short int a)
{
	enable_pid = a;
}

unsigned short int statusPID()
{
	return enable_pid;
}

void initOptoCoupleur()
{
	initEntree(2,BIT0); // opto-coupleur moteur A
	P2IE |= BIT0;       //activation du signal d interruption
	P2IES |= BIT0;

	initEntree(2,BIT3); // opto-coupleur moteur B
	P2IE |= BIT3;       //activation du signal d interruption
	P2IES |= BIT3;
	P2IFG = 0;

	_enable_interrupt();
}


/*
 * initPID : set up a 100 ms timer
 */
void initPID()
{
    TA0CTL = 0 | (TASSEL_2 | ID_3); // 8 divider
    TA0CTL |= MC_1;
    TA0CTL |= TAIE;
    TA0CCR0 = 12500;

    initOptoCoupleur();

    __enable_interrupt();
}
