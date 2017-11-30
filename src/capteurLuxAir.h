/*
 * capteurLuxAir.h
 *
 *  Created on: 17 nov. 2017
 *      Author: Wen et Aubin
 */

#ifndef CAPTEURLUXAIR_H_
#define CAPTEURLUXAIR_H_

// initialise les luxmètres
void initLuxAir();

// retourne la valeure lue par le luxmètre gauche
int railGauche();

// retourne la valeure lue par le luxmètre droit
int railDroit();

// fait tourner le robot selon la detection des rails
void suivreLigneLumineux();

#endif /* CAPTEURLUXAIR_H_ */
