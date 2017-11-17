#ifndef ADC_H
#define ADC_H

void ADC_init(void);

void ADC_Demarrer_conversion(unsigned char voie);
 
int ADC_Lire_resultat ();

#endif // ADC_H
