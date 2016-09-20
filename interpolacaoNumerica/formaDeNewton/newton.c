//
//	[newton.c]
//	Created by Micael Levi on 09/02/2016
//	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
//	https://github.com/micalevisk/CompNumerica/tree/master/interpolacaoNumerica/formaDeNewton
//
//	Calcula uma função interpoladora a partir de uma tabela de pontos usando a Forma de Newton.
//	USO: vide o cabeçalho "newton.h"
//

#include "newton.h"


short lerValores(Tupla* tabelaDeCoordenadas, unsigned qtdPontos){
	unsigned i;

	#ifndef AUTO
		printf(">> Digite no formato \"x f(x)\" (sem aspas) seguido de um ENTER a cada Xi\n");
		printf("i\n");
	#endif

	for(i=0; i < qtdPontos; ++i){
		#ifndef AUTO
			printf("%u: ", i);
		#endif
		if( scanf("%f %f", &tabelaDeCoordenadas[i].x, &tabelaDeCoordenadas[i].y) != 2 ) return 0;
	}
	return (i == qtdPontos);
}


float** tabelaDasDiferencasDivididas(Tupla* tabelaDeCoordenadas, unsigned qtdPontos){
	int m = qtdPontos-1; if(m < 0) return NULL;

	unsigned i, j;
	float** tabelaDiferencasDivididas = malloc(sizeof(float*) * qtdPontos);
	for(i=0; i < qtdPontos; ++i) tabelaDiferencasDivididas[i] = malloc(sizeof(float));

	/// passo 1:
	for(i=0, j=0; i <= m; ++i) a(i,j) = Y(i);

	/// passo 2:
	for(i=0, j=1; i < m; ++i)
		a(i,j) = (Y(i+j)  - Y(i)) / (X(i+j) - X(i));

	/// passo 3:
	for(j=2; j <= m; ++j){
		for(i=0; i <= m-j; ++i)
			a(i,j) = ( a(i+1,j-1) - a(i,j-1) ) / ( X(i+j) - X(i) );
	}
	return tabelaDiferencasDivididas;
}


float calcularPonto(float X, Tupla* tabelaDeCoordenadas, float** tabelaDiferencasDivididas, unsigned qtdPontos, char* FORMATO, char* FORMATO_TERMO){
	/// mostrando o polinômio interpolador:
	unsigned j, k;

	#ifdef MOSTRAR
		printf("\n P%u(x) =\n", qtdPontos-1);
		printf("\t"); printf(FORMATO, a(0,0)); printf("\n");
	#endif

	float Y = a(0,0);
	for(j=1; j < qtdPontos; ++j){
		float produtorio = 1;

		#ifdef MOSTRAR
			printf("\t"); printf(FORMATO, a(0,j));
		#endif

			for(k=0; k < j; ++k){
				bool ispositive = X(k) >= 0;

				#ifdef MOSTRAR
					printf(FORMATO_TERMO, (ispositive ? '-' : '+'), (ispositive ? X(k) : (X(k)*-1)));
				#endif

				produtorio *= (X - X(k));
			}
			#ifdef MOSTRAR
				printf("\n");
			#endif

			Y += a(0,j) * produtorio;
	}

	return Y;
}


int main()
{
	Tupla* tabela = NULL;
	float** tabelaDiferencas = NULL;
	float xInterpolar, yInterpolar;
	unsigned nPontos=0;

	/*****************************************************************************/
	char* FORMATO = calloc(11, sizeof(char));
	char* FORMATO_TERMO = calloc(22, sizeof(char));

	#ifdef PRECISAO
		char PRECISAO_str[2];
		if((PRECISAO >= 0) && (PRECISAO <= 6)) sprintf(PRECISAO_str, "%d", PRECISAO);
		else sprintf(PRECISAO_str, "%d", 6);
		sprintf(FORMATO, "%%+.%sf", PRECISAO_str);
		sprintf(FORMATO_TERMO, " * (x %%c %%.%sf)", PRECISAO_str);
	#else
		strcpy(FORMATO,"%+.3f"); // precisão padrão é 3.
		strcpy(FORMATO_TERMO," * (x %c %.3f)");
	#endif
	/*****************************************************************************/


	#ifndef AUTO
		printf(">> Digite a abcissa (x) do ponto interpolado: ");
	#endif
	scanf("%f", &xInterpolar);

	#ifndef AUTO
		printf(">> Digite a quantidade de pontos (numero natural): ");
	#endif
	scanf("%u", &nPontos);

	if(!nPontos) return 1;

	tabela = malloc(sizeof(Tupla) * nPontos);
	if(!lerValores(tabela, nPontos)) return -1;

	tabelaDiferencas = tabelaDasDiferencasDivididas(tabela, nPontos);

	yInterpolar = calcularPonto(xInterpolar, tabela, tabelaDiferencas, nPontos, FORMATO, FORMATO_TERMO);

	printf("\nP%u(", nPontos-1); printf(FORMATO, xInterpolar); printf(") = ");
	printf(FORMATO, yInterpolar);
	printf("\n");

	return 0;
}
