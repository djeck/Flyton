/*
 * capteurInfrarouge.h
 *
 *  Created on: 17 nov. 2017
 *      Author: Marion & Oceane
 */


#ifndef CAPTEURINFRAROUGE_H_
#define CAPTEURINFRAROUGE_H_


/*
 * exemple :
 * 	 ADC_init();
 *   ADC10AE0 |= BIT5;
 *   initInfrarouge();
 *
 *   volatile int detectionObstacle = 1000;//pour pas qu il s arrete pas au debut
 *   detectionObstacle = obstacle();
 */
void initInfrarouge();
int obstacle();

#endif /* CAPTEURINFRAROUGE_H_ */
