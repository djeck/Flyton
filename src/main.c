#include <msp430.h> 
#include "utils.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
		initEntree(1,BIT3);
		initSortie(1,BIT0);
	while(1){
			delay(1000);
			P1OUT ^= BIT0;

	}
	return 0;
}
