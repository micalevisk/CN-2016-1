//
//	[main.c]
//	Created by Micael Levi on 09/02/2016
//	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
//
//	Calcula uma função interpoladora a partir de uma tabela de pontos.
//
//	USO:
//	COMPILAR NA LINHA DE COMANDO:
//	(1)	$	gcc -o polinomioNewton main.c
//	(2)	$	gcc -D MANUAL -o polinomioNewton main.c
//
//	EXECUTAR NA LINHA DE COMANDO:
//	(1.1)	$	./polinomioNewton < arqEntradas
//	(2.1)	$	./polinomioNewton
//
//	NOS DOIS CASOS, PODE-SE DEFINIR UMA OUTRA PRECISÃO (3 É A PADRÃO)
//	AO COMPILAR NA LINHA DE COMANDO:
//	(a)	$	gcc -D PRECISAO -o polinomioNewton main.c
//	(b)	$	gcc -D PRECISAO=p -o polinomioNewton main.c
//	ONDE 'p' é um natural de 0 a 6
//
//	SAÍDA:
//	(o polinômio interpolador)
//	Pn(x) = a + b(x - x0) + c(x - x0)(x - x1) + ...
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

float* valoresX;
float* valoresFx;
float** tabelaDiferencasDivididas;
unsigned nPontos=0;
int m=0;

#define X valoresX
#define fX valoresFx
#define a tabelaDiferencasDivididas



short lerValores(void){
	unsigned i;

	#ifdef MANUAL
		printf(">> Digite no formato \"x f(x)\" (sem aspas) seguido de um ENTER a cada Xi\n");
		printf("i\n");
	#endif
	for(i=0; i < nPontos; ++i){
		#ifdef MANUAL
			printf("%u: ", i);
		#endif
		if( scanf("%f %f", &valoresX[i], &valoresFx[i]) != 2 ) return 0;
	}
	return (i == nPontos);
}


void tabelaDasDiferencasDivididas(void){

	m = nPontos-1; if(m < 0) return;
	unsigned i, j;
	tabelaDiferencasDivididas = malloc(sizeof(float*)*nPontos);
	for(i=0; i < nPontos; ++i) tabelaDiferencasDivididas[i] = malloc(sizeof(float*));

	/// passo 1:
	for(i=0, j=0; i <= m; ++i) a[i][j] = fX[i];

	/// passo 2:
	for(i=0, j=1; i < m; ++i)
		a[i][j] = (fX[i+j]  - fX[i]) / (X[i+j] - X[i]);

	/// passo 3:
	for(j=2; j <= m; ++j){
		for(i=0; i <= m-j; ++i)
			a[i][j] = (a[i+1][j-1] - a[i][j-1]) / ( X[i+j] - X[i] );
	}

}





int main(){

	/*****************************************************************************/
	char FORMATO[11]; memset(FORMATO,'\0',11);
	#ifdef PRECISAO
		// #define FORMATO "%+." PRECISAO "f"
		char PRECISAO_str[2];
		if((PRECISAO >= 0) && (PRECISAO <= 6)) sprintf(PRECISAO_str, "%d", PRECISAO);
		else sprintf(PRECISAO_str, "%d", 6);
		sprintf(FORMATO, " %%+.%sf", PRECISAO_str);
	#else
		strcpy(FORMATO," %+.3f"); // precisão padrão é 3.
	#endif
	/*****************************************************************************/


	#ifdef MANUAL
		printf(">> Digite a quantidade de pontos (numero natural): ");
	#endif
	scanf("%u", &nPontos);

	if(!nPontos) return 1;

	valoresX = calloc(nPontos, sizeof(float));
	valoresFx= calloc(nPontos, sizeof(float));
	if(!lerValores()) return 1;

	tabelaDasDiferencasDivididas();

	/// mostrando o polinômio interpolador:
	unsigned j, k;
	printf("\nP%u(x) =", m); printf(FORMATO, a[0][0]);
	for(j=1; j <= m; ++j){
		printf(FORMATO, a[0][j]);
			for(k=0; k < j; ++k){
				bool ispositive = (X[k] > 0);
				if(!X[k])
					printf("(x)"); // caso Xi seja igual a zero.
				else
					printf("(x %c %.1f)", (ispositive ? '+' : '-'), (ispositive ? X[k] : (X[k]*-1)));
			}
	}
	printf("\n\n");

	return 0;
}
