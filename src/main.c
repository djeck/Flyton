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

	int flagArrivee;
	initEntree(1,BIT3);
	initSortie(1,BIT6); // Launchpad led //LED rouge
	initSortie(1,BIT0);

	BCSCTL1 = CALBC1_1MHZ; // frequence d'horloge 1MHz
	DCOCTL = CALDCO_1MHZ; // frequence d'horloge 1MHz

	initChassis();
	///////////////////////////////////////
	// initialization capt IR
	ADC_init();
	initInfrarouge();

	//LED indication
	P1OUT |= BIT6;
	P1OUT |= BIT0;
	delay(2000);
	P1OUT &= ~BIT6;
	P1OUT &= ~BIT0;

	///////////////////////////////////////////

	/*
	 * Chercher la valeur moyenne de capteurs lumineux
	 */
	volatile int valMoyLuxAirGauche;
	volatile int valMoyLuxAirDroite;

	//une fois qu'on appuis sur le bouton, on enregistre les valeurs des capteurs lumineux

	while((P1IN & BIT3) == BIT3){
		valMoyLuxAirGauche = (railGauche()+railDroit())/2;
	}//TODO

	avancerVitesse(35);
	delay(2000);
	avancerVitesse(85);
	delay(500);

	while (flagArrivee != 1) // avancer
	{
		delay(75);
		detacteObstacleEtArreter();
//		zoneBlancheGauche();
		flagArrivee = detacteZoneBlancheDroiteEtArreter();
	}
	avancerVitesse(30);
	delay(1000);
	arreter();
	while (1)	{
		P1OUT ^= BIT6;
		delay(400);

	}
	return 0;
}
