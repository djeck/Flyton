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
	int flagArrivee = 0;

	WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

	initSortie(1,BIT0); // Launchpad led jaune
	initSortie(1,BIT6); // Launchpad led rouge
	initEntree(1,BIT3); // Bouton pour démarer

	BCSCTL1 = CALBC1_1MHZ; // frequence d'horloge 1MHz
	DCOCTL = CALDCO_1MHZ; // frequence d'horloge 1MHz

	// initialization 
	initChassis();
	ADC_init();
	initInfrarouge();
	initLuxAir();
	
	// LED indication
	P1OUT |= BIT6;
	P1OUT |= BIT0;
	delay(2000);
	P1OUT &= ~BIT6;
	P1OUT &= ~BIT0;

	// Attente du signal de dépard
	while((P1IN & BIT3) == BIT3){
	}

	// sort de la zone de départ
	avancerVitesse(60);
	delay(1000);
	avancerVitesse(85);
	delay(100);

	// avance tant que la zone d'arrivée est pas détectée
	while (flagArrivee != 1)
	{
		delay(75);
		detacteObstacleEtArreter(); // bloque si un obstacle est détecté
		flagArrivee = zoneBlanche(); // test si on arrive dans la zone blanche
	}

	// se place dans le rond d'arrivé
	avancerVitesse(30);
	delay(1300);
	arreter();

	// fait clignoter la led
	while (1) {
		P1OUT ^= BIT6;
		delay(400);
	}
	return 0;
}
