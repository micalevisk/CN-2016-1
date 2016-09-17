//
//  [calcular_derivar.hpp]
//  Created by Micael Levi on 07/15/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include <vector>
#include <cmath> // pow
using namespace std;

// inline void show(vector<int> v) { for(auto const& e : v) cout << e << ", "; }

// calcula f(x) dado um x e o vetor de inteiros que representa f(x);
double calcularPara(double x, vector<int> funcao){
  size_t tam = funcao.size();
  // se tiver o termo independente:
  double resultado = (tam % 2) ? funcao[--tam] : 0;

  // calcula termos dependentes:
  for(unsigned i=0; i < tam; i+=2)
    resultado += funcao[i] * pow(x, funcao[i+1]); // = a * x^g

  return resultado;
}

// retorna o polinômio (de inteiros) em um vetor de inteiros representando sua primeira derivada.
vector<int> derivadaDe(vector<int> funcao){
  auto tam = funcao.size();
  vector<int> resultado = funcao;
  if(tam % 2) resultado.resize(--tam); // retira o termo independente (se existir).

  for(unsigned i=0; i < tam; i+=2){
    resultado[i] *= resultado[i+1];
    resultado[i+1]--;
    if(!resultado[i+1]) resultado.erase(resultado.begin() + i+1); // apaga o que seria x^0.
  }

  return resultado;
}
