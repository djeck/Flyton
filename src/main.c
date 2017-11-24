#include <msp430.h> 
#include "utils.h"
#include "chassis.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	initSortie(1,BIT0); // Launchpad led
	initSortie(1,BIT4); // test

	BCSCTL1 = CALBC1_1MHZ; // frequence d'horloge 1MHz
	DCOCTL = CALDCO_1MHZ; // frequence d'horloge 1MHz

	initChassis();

	while(1){
		avancerVitesse(15);
		delay(1000);
//		tourner(-15);
//		arreter();
//		delay(1000);


	}
	return 0;
}
