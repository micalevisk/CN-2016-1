//
//  [usarFalsaPosicao.hpp]
//  Created by Micael Levi on 07/15/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "../calcular_derivar.hpp"
#include "../get-interval.hpp"

#include <iostream>
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
3.  c := ( a*f(b) - b*f(a) ) / ( f(b) - f(a) )
4.  Se |f(c)| <= erro, FIM --> c é raiz
5.  Se f(a)*f(c) < 0, b := c. Senão, a := c
6.  iteracao := iteracao + 1
7.  Voltar para o passo 3
*/

double calcularRaiz(vector<int> funcao, const double erro, string intervalo, const unsigned short nCasas){
  tuple<double, double> intervaloInicial = tuplaDoIntervalo(intervalo);
  double a = get<0>(intervaloInicial);
  double b = get<1>(intervaloInicial);

  unsigned iteracao = 0;
  double c, fa, fc, fb;
  bool ehMenor;

  fa = calcularPara(a, funcao);
  fb = calcularPara(b, funcao);
  c = (a*fb - b*fa) / (fb - fa);
  fc = calcularPara(c, funcao);

  if( !(fa * fb) < 0 ) exit(1);

  printf("|--------------+----------------------------------------------------------------------------------------------------------------|\n");
  printf("|   ITERACAO   |\ta\t|\tc\t|\tb\t||\tf(a)\t|\tf(c)\t|\tf(b)\t| f(a)*f(c)\t|\n");
  printf("|--------------+----------------------------------------------------------------------------------------------------------------|\n");

  while( !(abs(fc) <= erro) && (iteracao <= 15) ){
    ehMenor = (fa * fc) < 0;

    printf("|%8u%6c|\t%.*f\t|\t%.*f\t|\t%.*f\t||\t%.*f\t|\t%.*f\t|\t%.*f\t|\t%s\t|\n",
    iteracao, ' ',
    nCasas, a,
    nCasas, c,
    nCasas, b,
    nCasas, fa,
    nCasas, fc,
    nCasas, fb, (ehMenor ? "< 0": "> 0"));

    ((fa * fc) < 0) ? b=c : a=c;
    fa = calcularPara(a, funcao);
    fb = calcularPara(b, funcao);
    c = (a*fb - b*fa) / (fb - fa);
    fc = calcularPara(c, funcao);

    ++iteracao;
  }

  printf("|%8u%6c|\t%.*f\t|\t%.*f\t|\t%.*f\t||\t%.*f\t|\t%.*f\t|\t%.*f\t|\t%s\t|\n", iteracao, ' ', nCasas, a, nCasas, c, nCasas, b, nCasas, fa, nCasas, fc, nCasas, fb, " ");
  printf("|--------------+----------------------------------------------------------------------------------------------------------------|\n");

  cout << "Quantidade de iteracoes: " << iteracao+1 << endl;

  return c;
}


/* FORMATO DA TABELA:


|--------------+---------+---------+---------++------------+------------+------------+-------------|
|...ITERAÇÃO...|....a....|....c....|....b....||....f(a)....|....f(c)....|....f(b)....|..f(a)*f(c)..|
|--------------+-----------------------------||----------------------------------------------------|
|.......0......|.........|.........|.........||............|............|............|.............|
|.......1......|.........|.........|.........||............|............|............|.............|
|--------------+---------+---------+---------++------------+------------+------------+-------------|
*/
