#include <msp430.h> 
#include "utils.h"
#include "chassis.h"
#include "capteurLuxAir.h"
#include "capteurInfrarouge.h"
#include "ADC.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	initSortie(1,BIT0); // Launchpad led jaune
	initSortie(1,BIT6); // Launchpad led rouge
	initSortie(1,BIT3); // Launchpad led vert //pas sur de marcher

	BCSCTL1 = CALBC1_1MHZ; // frequence d'horloge 1MHz
	DCOCTL = CALDCO_1MHZ; // frequence d'horloge 1MHz

	// initialization 
	initChassis();
	ADC_init();
	initInfrarouge();
	initLuxAir();
	
	//LED indication
	P1OUT |= BIT0;
	delay(3000);
	P1OUT &= ~BIT0;

	while (1) // avancer
	{
		delay(100);
		detacteObstacleEtArreter();
		suivreLigneLumineux();
	}
	return 0;
}
