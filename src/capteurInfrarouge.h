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

/*
 * @return 1 si un obstable est détecter, 0 sinon
 */
int obstacle();

/*
 * s'arrête si un obstacle est détecter,
 * repart et suit la ligne lorsque il n'y a plus d'obstacle
 */
void detacteObstacleEtArreter();

#endif /* CAPTEURINFRAROUGE_H_ */
