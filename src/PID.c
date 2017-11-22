/*
 * PID.c
 *
 *  Created on: Nov 22, 2017
 *      Author: Wen
 */
#include <msp430.h>
#include "PID.h"

//timer 1 interrupt for PID regulations
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
    P1OUT ^= BIT0;//test for shining the led on P1.0
    TA0CTL &= ~TAIFG;
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

    __enable_interrupt();
}
