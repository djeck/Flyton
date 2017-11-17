#include <msp430.h> 
#include "utils.h"


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
		avancerVitesse(50);
		delay(2000);
		arreter();
		delay(1000);
		P1OUT ^= BIT0;
		P1OUT ^= BIT4;
	}
	return 0;
}
