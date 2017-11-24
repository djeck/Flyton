/*
 * chassis.h
 *
 *  Created on: 17 nov. 2017
 *      Author: a.detrez.14 and Wen
 */

#ifndef CHASSIS_H_
#define CHASSIS_H_


/*
 * initChassis : public
 * Initialise les roues moteurs, les opto coupleur,
 * et timer pour regulation PID
 */
void initChassis();

/*
 * avancer : avancer le robot avec une vitesse a une certaine distance
 * <!!>pour instant pareil que avancerVitesse
 */
void avancer(int vitesse, int distance);

/*
 * avancerVitesse : avant le robot en passant meme rapport cyclique sur deux roues
 */
void avancerVitesse(int vitesse);

/*
 * tourner : tourner le robot avec une petite correction
 * parametres :
 *      correction :    valeur positive pour tourner a droite,
 *                      cette valeur ne doit pas etre tres grande
 *                      par rapport a TA1CCR1 et TA1CCR2
 */
void tourner(signed int correction);	//tested

/*
 * tournerAngle : tourner le robot en gardant la meme vitesse moyenne
 * parametres :
 *      angle:  127 -> tourner sur place vers la droite
 *              -127 -> tourner sur place vers la gauche
 */
void tournerAngle(signed int angle);	//tested

/*
 * arreter : arret complet du robot
 */
void arreter();			//tested

#endif /* CHASSIS_H_ */
