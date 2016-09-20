//
//	[newton.h]
//	Created by Micael Levi on 09/02/2016
//	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
//
//	Calcula uma função interpoladora a partir de uma tabela de pontos usando a Forma de Newton.
//
//	USO:
//	COMPILAR NA LINHA DE COMANDO:
//	(1)	$	gcc -D AUTO -o polinomioNewton main.c
//	(2)	$	gcc -o polinomioNewton main.c
//
//	EXECUTAR NA LINHA DE COMANDO:
//	(1.1)	$	./polinomioNewton < arqEntradas
//	(2.1)	$	./polinomioNewton
//
//	O 'arqEntradas' DEVE OBEDECER AO SEGUINTE FORMATO:
//	N
//	X0 Y0
//	X1 Y1
//	...
//	Xn-1 Yn-1
//
//	ONDE, 'N' É UM NÚMERO NATURAL QUE INDICA A QUANTIDAE DE PONTOS A SEREM LIDOS A SEGUIR.
//
//	NOS DOIS CASOS, PODE-SE AINDA DEFINIR UMA OUTRA PRECISÃO (SENDO 0.001 A PADRÃO)
//	AO COMPILAR NA LINHA DE COMANDO:
//	(a)	$	gcc -D PRECISAO -o polinomioNewton main.c
//	(b)	$	gcc -D PRECISAO=p -o polinomioNewton main.c
//	ONDE "p" É UM NATURAL DE 0 A 6 QUE INDICA O NÚMERO DE CASAS DECIMAIS.
//
//	SAÍDA:
//	(o polinômio interpolador)
//	Pn(x) = a + b(x - x0) + c(x - x0)(x - x1) + ...
//
//	DIRETIVAS DE PRE-PROCESSAMENTO VALIDAS:
//	PRECISAO	(alterar precisao padrao)
//	AUTO	(nao mostrar instrucoes; para leituras redirecionadas)
//

#ifndef NEWTON_H
#define NEWTON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	float x, y;
}Tupla;

#define X(i) tabelaDeCoordenadas[i].x
#define Y(i) tabelaDeCoordenadas[i].y
#define a(i,j) tabelaDiferencasDivididas[i][j]


short lerValores(Tupla* tabelaDeCoordenadas, unsigned qtdPontos);

float** tabelaDasDiferencasDivididas(Tupla* tabelaDeCoordenadas, unsigned qtdPontos);

float calcularPonto(float X, Tupla* tabelaDeCoordenadas, float** tabelaDiferencasDivididas, unsigned qtdPontos, char* FORMATO, char* FORMATO_TERMO);


#endif
