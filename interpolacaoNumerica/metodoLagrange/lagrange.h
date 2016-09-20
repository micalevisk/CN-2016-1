//
//	[lagrange.h]
//	Created by Micael Levi on 09/19/2016
//	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
//
//	USO:
//	COMPILAR NA LINHA DE COMANDO:
//	(1)	$	gcc -std=gnu11 -D AUTO -o polinomioLagrange lagrange.c
//	(2)	$	gcc -std=gnu11 -o polinomioLagrange lagrange.c
//
//	EXECUTAR NA LINHA DE COMANDO:
//	(1.1)	$	./polinomioLagrange < arqEntradas
//	(2.1)	$	./polinomioLagrange
//
//	O 'arqEntradas' DEVE SER UM ARQUIVO TEXTO QUE OBEDECE AO SEGUINTE FORMATO:
//	x
//	N
//	X0 Y0
//	X1 Y1
//	...
//	Xn-1 Yn-1
//
//	ONDE, 'x' é o ponto interpolado, 'N' É UM NÚMERO NATURAL QUE INDICA A QUANTIDAE DE PONTOS A SEREM LIDOS A SEGUIR.
//
//	NOS DOIS CASOS, PODE-SE AINDA DEFINIR UMA OUTRA PRECISÃO (SENDO 0.001 A PADRÃO)
//	AO COMPILAR NA LINHA DE COMANDO:
//	(a)	$	gcc -D PRECISAO -o polinomioLagrange lagrange.c
//	(b)	$	gcc -D PRECISAO=p -o polinomioLagrange lagrange.c
//	ONDE "p" É UM NATURAL DE 0 A 6 QUE INDICA O NÚMERO DE CASAS DECIMAIS.
//
//	SAÍDA:
//	(a ordenada do ponto interpolado)
//
//	DIRETIVAS DE PRE-PROCESSAMENTO VALIDAS:
//	PRECISAO	(alterar precisao padrao)
//	MOSTRAR	(exibir o polinomio interpolador)
//	AUTO	(nao mostrar instrucoes; para leituras redirecionadas)
//

#ifndef LAGRANGE_H
#define LAGRANGE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	float x, y;
}Tupla;

#define X(i) tabelaDeCoordenadas[i].x
#define Y(i) tabelaDeCoordenadas[i].y


short lerValoresParaTabela(Tupla* tabelaDeCoordenadas, unsigned qtdPontos);

float calcularPonto(float X, Tupla* tabelaDeCoordenadas, unsigned qtdPontos, char* FORMATO, char* FORMATO_NUMERADOR, char* FORMATO_DENOMINADOR);


#endif
