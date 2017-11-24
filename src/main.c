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

	initSortie(1,BIT0); // Launchpad led
	initSortie(1,BIT4); // test

	BCSCTL1 = CALBC1_1MHZ; // frequence d'horloge 1MHz
	DCOCTL = CALDCO_1MHZ; // frequence d'horloge 1MHz

	initChassis();
	///////////////////////////////////////
	// initialization capt IR
	ADC_init();
	initInfrarouge();

	//LED indication
	P1OUT |= BIT0;
	delay(3000);
	P1OUT &= ~BIT0;
	///////////////////////////////////////////
	// capt lux air
//	int lumgauche = 0;
//	int lumdroite = 0;
//	initLuxAir();
//	ADC_init();
//	ADC10AE0 |= (BIT4 | BIT7);
//	while (1)
//	{
//		lumgauche = railGauche();
//		lumdroite = railDroit();
//	}




	while (1) // avancer
	{
		delay(100);
		detacteObstacleEtArreter();


	}
	return 0;
}
