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

	int flagArrivee = 0;
	initSortie(1,BIT0); // Launchpad led jaune
	initSortie(1,BIT6); // Launchpad led rouge
	initEntree(1,BIT3); // Launchpad led vert //pas sur de marcher

	BCSCTL1 = CALBC1_1MHZ; // frequence d'horloge 1MHz
	DCOCTL = CALDCO_1MHZ; // frequence d'horloge 1MHz

	// initialization 
	initChassis();
	ADC_init();
	initInfrarouge();
	initLuxAir();
	
	//LED indication
	P1OUT |= BIT6;
	P1OUT |= BIT0;
	delay(2000);
	P1OUT &= ~BIT6;
	P1OUT &= ~BIT0;

	//une fois qu'on appuis sur le bouton, on enregistre les valeurs des capteurs lumineux
	while((P1IN & BIT3) == BIT3){
	}

	avancerVitesse(60);
	delay(1000);
	avancerVitesse(85);
	delay(100);

	while (flagArrivee != 1) // avancer
	{
		delay(75);
		detacteObstacleEtArreter();
		flagArrivee = zoneBlancheDroite();
	}

	//detacte le rond d'arrivee
	avancerVitesse(30);
	delay(1300);
	arreter();
	while (1)	{	//clignote la LED
		P1OUT ^= BIT6;
		delay(400);
	}
	return 0;
}
