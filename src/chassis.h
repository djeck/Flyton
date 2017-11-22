/*
 * chassis.h
 *
 *  Created on: 17 nov. 2017
 *      Author: a.detrez.14
 */

#ifndef CHASSIS_H_
#define CHASSIS_H_

void initChassis();
void avancer(int vitesse, int distance);
void avancerVitesse(int vitesse);
void arreter();			//tested

void tourner(signed int correction);	//tested
void tournerAngle(signed int angle);	//tested

#endif /* CHASSIS_H_ */
