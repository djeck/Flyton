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
__interrupt void PIDAjouster(void);


/*
 * initPID : set up a 100 ms timer
 */
void initPID();

/*
 * @return 1 si le PID est activé, 0 sinon
 */
unsigned short int statusPID();

#endif  //PID_H
