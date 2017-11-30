/*
 * chassis.h
 *
 *  Created on: 17 nov. 2017
 *      Author: Wen et Aubin
 */

#ifndef CHASSIS_H_
#define CHASSIS_H_


/*
 * initChassis : public
 * Initialise les roues moteurs
 */
void initChassis();

/*
 * avancerVitesse : fait avancer le robot en mettant le même rapport cyclique sur deux roues
 */
void avancerVitesse(int vitesse);

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
