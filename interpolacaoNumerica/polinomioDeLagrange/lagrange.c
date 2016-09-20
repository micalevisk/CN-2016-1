//
//	[lagrange.c]
//	Created by Micael Levi on 09/19/2016
//	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
//	https://github.com/micalevisk/CompNumerica/tree/master/interpolacaoNumerica/polinomioDeLagrange
//
//	Calcula uma função interpoladora a partir de uma tabela de pontos usando o polinômio de Lagrange.
//	USO: vide o cabeçalho "lagrange.h"
//

#include "lagrange.h"


short lerValoresParaTabela(Tupla* tabelaDeCoordenadas, unsigned qtdPontos){
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


float calcularPonto(float X, Tupla* tabelaDeCoordenadas, unsigned qtdPontos, char* FORMATO, char* FORMATO_NUMERADOR, char* FORMATO_DENOMINADOR){
		#ifdef MOSTRAR
			printf("\n P%u(x) = \n", qtdPontos-1);
		#endif

		float Y = 0;
		for(unsigned j=0; j < qtdPontos; ++j){

			#ifdef MOSTRAR
				printf("\t");
				printf(FORMATO, Y(j));
			#endif

			float produtorio = 1;
			for(unsigned i=0; i < qtdPontos; ++i){
				if(i != j){

					#ifdef MOSTRAR
						bool ispositive = X(i) >= 0;
						printf(FORMATO_NUMERADOR, (ispositive ? '-' : '+'), (ispositive ? X(i) : (X(i)*-1)));
						printf(FORMATO_DENOMINADOR, X(j), (ispositive ? '-' : '+'), (ispositive ? X(i) : (X(i)*-1)));
					#endif

					produtorio *= ( (X - X(i)) / (X(j) - X(i)) );
				}
			}
			Y += produtorio * Y(j);

			#ifdef MOSTRAR
				printf("\n");
			#endif

		}

		return Y;
}


int main()
{
	Tupla* tabela = NULL;
	unsigned nPontos = 0;
	float xInterpolar, yInterpolar;

	/*****************************************************************************/
	char* FORMATO = calloc(11, sizeof(char));
	char* FORMATO_NUMERADOR = calloc(22, sizeof(char));
	char* FORMATO_DENOMINADOR = calloc(22, sizeof(char));

	#ifdef PRECISAO
		char PRECISAO_str[2];
		if((PRECISAO >= 0) && (PRECISAO <= 6)) sprintf(PRECISAO_str, "%d", PRECISAO);
		else sprintf(PRECISAO_str, "%hu", 6);
		sprintf(FORMATO, "%%+.%sf", PRECISAO_str);
		sprintf(FORMATO_NUMERADOR, " * (x %%c %%.%sf)", PRECISAO_str);
		sprintf(FORMATO_DENOMINADOR, "/(%%+.%sf %%c %%.%sf)", PRECISAO_str, PRECISAO_str);
	#else
		strcpy(FORMATO,"%+.3f"); // precisão padrão é 3.
		strcpy(FORMATO_NUMERADOR," * (x %c %.3f)"); // precisão padrão é 3.
		strcpy(FORMATO_DENOMINADOR,"/(%+.3f %c %.3f)"); // precisão padrão é 3.
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
	if(!lerValoresParaTabela(tabela, nPontos)) return 1;

	yInterpolar = calcularPonto(xInterpolar, tabela, nPontos, FORMATO, FORMATO_NUMERADOR, FORMATO_DENOMINADOR);

	printf("\nP%u(", nPontos-1); printf(FORMATO, xInterpolar); printf(") = ");
	printf(FORMATO, yInterpolar);
	printf("\n");

	free(FORMATO);
	free(FORMATO_NUMERADOR);
	free(FORMATO_DENOMINADOR);

	return 0;
}
