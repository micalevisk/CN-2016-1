//
//  serieSeno.c
//  Serie De Taylor Para Seno
//
//  Created by Micael Levi L. Cavalcante on 06/05/16.
//  Copyright (c) 2016 Micael. All rights reserved.
//

#include <stdio.h>          // função: printf
#include <math.h>           // função: pow | constante: M_PI

#define NSOMAS      5       // quantidade de somas da série.
#define PRECISAO    float   // tipo de precisão.
#define NTESTE      1       // número do teste (1 a 8).
#define TESTECURR   0       // seno a ser calculado.



PRECISAO fatorial(PRECISAO eq){
	unsigned long fat=1;
	int i;
	for(i=2; i <= eq; i++) fat *= i;
	return fat;
}


PRECISAO serieSeno(PRECISAO num, unsigned nSomas){
    num = (num*M_PI)/180.0; // convertendo de graus para radianos.
    unsigned i;
    PRECISAO nCurr;
    PRECISAO soma = 0.0;
    unsigned long denomidador;
    short sinal;

    for(i=0; i < nSomas; i++){
        sinal = pow(-1,i);
        nCurr = 2*i+1;
        denomidador = fatorial(nCurr);
        soma += sinal*(pow(num, nCurr))/denomidador;
    }

    return soma;
}



int main(void){
    printf("\n%hu. %-3u\t\t\t| %+-15.21f\n", NTESTE, TESTECURR, serieSeno(TESTECURR, NSOMAS));
    return 0;
}
