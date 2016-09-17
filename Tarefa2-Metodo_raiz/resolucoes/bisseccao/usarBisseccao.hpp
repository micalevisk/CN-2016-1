//
//  [usarBisseccao.hpp]
//  Created by Micael Levi on 07/15/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//


#include "../calcular_derivar.hpp"
#include "../get-interval.hpp"

#include <iostream>
#include <tuple>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
using namespace std;


// Recebe um vetor de inteiros que representa um polinômio, a precisão, e os extremos (inteiros "double").
// retorna a raiz real encontrada
// além da impressão da tabela com resultados.

/* ALGORITMO:
entradas: extremante esquerdo (a), extremante direito (b) e precisao (erro)

1.  iteracao := 0
2.  Se f(a)*f(b) < 0, continua. Senão, ABORTA PROGRAMA.
3.  c := (a+b)/2
4.  Se |b - a| < erro, FIM --> c é raiz
5.  Se f(a)*f(c) < 0, b := c. Senão, a := c
6.  iteracao := iteracao + 1
7.  Voltar para o passo 3
*/

double calcularRaiz(vector<int> funcao, const double erro, string intervalo, const unsigned short nCasas){
  tuple<double, double> intervaloInicial = tuplaDoIntervalo(intervalo);
  double a = get<0>(intervaloInicial);
  double b = get<1>(intervaloInicial);
  unsigned K = ceil( (log10(b-a) - log10(erro))/(double)log10(2) );
  unsigned iteracao = 0;
  double c, fa, fc;
  bool ehMenor;

  if( !(calcularPara(a, funcao) * calcularPara(b, funcao) < 0) ) exit(1);

  printf("|--------------+------------------------------------------------------------------------------------------------|\n");
  printf("|   ITERACAO   |\ta\t|\tc\t|\tb\t||\tf(c)\t| f(a)*f(c)\t| abs(b - a)\t|\n");
  printf("|--------------+------------------------------------------------------------------------------------------------|\n");

  c = (a+b) / 2.0;
  while( (iteracao <= K) && !(abs(b - a) < erro) ){
    fa = calcularPara(a, funcao);
    fc = calcularPara(c, funcao);

    ehMenor = (fa * fc) < 0;

    printf("|%8u%6c|\t%.*f\t|\t%.*f\t|\t%.*f\t||\t%.*f\t|\t%s\t|\t%.*f\t|\n",
    iteracao, ' ',
    nCasas, a,
    nCasas, c,
    nCasas, b,
    nCasas, fc, (ehMenor ? "< 0": "> 0"), nCasas,abs(b-a));

    ((fa * fc) < 0) ? b=c : a=c;
    c = (a+b) / 2.0;
    ++iteracao;
  }

  printf("|%8u%6c|\t%.*f\t|\t%.*f\t|\t%.*f\t||\t%.*f\t|\t%s\t|\t%.*f\t|\n", iteracao, ' ',  nCasas, a,  nCasas, c,  nCasas, b, nCasas, fc, " ", nCasas,abs(b-a));
  printf("|--------------+------------------------------------------------------------------------------------------------|\n");

  cout << "Quantidade de iteracoes: " << iteracao+1 << endl;

  return c;
}


/* FORMATO DA TABELA:

|--------------+---------+---------+---------++------------+-------------+------------|
|...ITERAÇÃO...|....a....|....c....|....b....||....f(c)....|..f(a)*f(c)..|.abs(b - a).|
|--------------+---------+---------+---------||------------+-------------+------------+
|.......0......|.........|.........|.........||............|.....< 0.....|............|
|.......1......|.........|.........|.........||............|.....< 0.....|............|
|--------------+---------+---------+---------++------------+-------------+------------|
*/
