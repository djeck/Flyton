/*
 * utils.h
 *
 *  Created on: Nov 16, 2017
 *      Author: Wen-W7Pro-VM
 */
#ifndef UTILS_H
#define UTILS_H

// ms: delay d'attente en mili-seconde
void delay(unsigned int ms);

/*
 * initEntree : configurer un bit dans port1 ou port2 a une entree
 * exemple :
 *      initEntree(1,BIT2); // initialise P1.2 a une entree
 */
void initEntree(int port, int bit);

/*
 * initSortie : configurer un bit dans port1 ou port2 a une sortie
 * exemple :
 *      initSortie(2,BIT2); // initialise P2.2 a une sortie
 */
void initSortie(int port, int bit);

//void activeInterruption(int port, int bit);

#endif // UTILS_H
