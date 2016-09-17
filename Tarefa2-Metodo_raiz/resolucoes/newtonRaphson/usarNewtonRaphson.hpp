//
//  [usarNewtonRaphson.hpp]
//  Created by Micael Levi on 07/15/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "../calcular_derivar.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <sstream>
using namespace std;

// Recebe um vetor de inteiros que representa um polinômio, a precisão, e os extremos (inteiros "double").
// retorna a raiz real encontrada
// além da impressão da tabela com resultados.

/* ALGORITMO:
entradas: aproximação inicial (X0) e precisão (erro)

1.  iteracao := 0
2.  Se |X0| < erro, FIM --> X0 é a raiz
3.  iteracao := 1
4.  X1 = X0 - ( f(X0)/f'(X0) )
5.  Se |f(X1)| <= erro ou |X1 - X0| < erro, FIM --> X1 é raiz
6.  X0 := X1
7.  iteracao := iteracao + 1
7.  Voltar para o passo 4
*/

double calcularRaiz(vector<int> funcao, const double erro, string aproximacaoInicial, const unsigned short nCasas){
  double a; istringstream(aproximacaoInicial) >> a; // será o X0.
  unsigned iteracao = 0;
  double b, fb, ffb;    // 'b' será o Xi+1
  double fa, ffa;       // f(a) e f'(a), respectivamente.
  double aux;
  vector<int> ffx = derivadaDe(funcao);

  printf("|--------------+------------------------------------------------|\n");
  printf("|   ITERACAO   |\tXi\t|\tf(Xi)\t|\tf'(Xi)\t|\n");
  printf("|--------------+------------------------------------------------|\n");

  fa  = calcularPara(a, funcao);
  ffa = calcularPara(a, ffx);
  if( abs(a) < erro ) goto fim;
  do{
    printf("|%8u%6c|\t%.*f\t|\t%.*f\t|\t%.*f\t|\n",
    iteracao, ' ',
    nCasas, a,
    nCasas, fa,
    nCasas, ffa);

    b = a - (fa/ffa);
    aux = a;
    a = b;
    fa  = calcularPara(a, funcao);
    ffa = calcularPara(a, ffx);

    ++iteracao;

  }while( (iteracao <= 15) && (!(abs(fa) <= erro) || !(b - aux < erro)) );

  fim:
  printf("|%8u%6c|\t%.*f\t|\t%.*f\t|\t%.*f\t|\n",  iteracao, ' ',  nCasas, a,  nCasas, fa,  nCasas, ffa);
  printf("|--------------+------------------------------------------------|\n");

  cout << "Quantidade de iteracoes: " << iteracao+1 << endl;

  if((iteracao >= 15) && (!(abs(fa) <= erro))) cout << " (nao convergiu)" << endl;

  return b;
}


/* FORMATO DA TABELA:


|--------------+----------+-----------+--------------|
|...ITERAÇÃO...|....Xi....|...f(Xi)...|....f'(Xi)....|
|--------------+-------------------------------------|
|.......0......|..........|..........|...............|
|.......1......|..........|..........|...............|
|--------------+----------+----------+---------------|
*/
