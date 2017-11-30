#ifndef ADC_H
#define ADC_H

/*
 * Initialise l'ADC
 */
void ADC_init(void);

/*
 * Démarre l'acquisition par l'ADC
 */
void ADC_Demarrer_conversion(unsigned char voie);
 
/*
 * Lire les résultats de l'ADC
 */
int ADC_Lire_resultat ();

#endif // ADC_H
