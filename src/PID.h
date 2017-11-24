/*
 * PID.h
 *
 *  Created on: Nov 22, 2017
 *      Author: Wen
 */
#ifndef PID_H
#define PID_H

__interrupt void PORT2_ISR(void);


//timer 1 interrupt for PID regulations
__interrupt void Timer_A1(void);


/*
 * initPID : set up a 100 ms timer
 */
void initPID();

#endif  //PID_H
