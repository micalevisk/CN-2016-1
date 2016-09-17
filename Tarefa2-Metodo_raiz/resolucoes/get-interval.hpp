//
//  [get-interval.hpp]
//  Created by Micael Levi on 07/15/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//
//  Dada uma string no formato: [xx, yy]
//  que representa um intervalo (o intervalo inicial do cálculo)
//  retorna a tupla com "xx" e "yy" convertidos para double.
//

#include <string>
#include <tuple>
#include <sstream>
using namespace std;

//                                           "[a0, b0]"
tuple<double,double> tuplaDoIntervalo(string intervalo = "[0, 0]"){
  size_t posColcheteInicial = intervalo.find('[');
  size_t posColcheteFinal = intervalo.find(']');
  size_t posVirgula = intervalo.find(',');

  double extremoEsquerdo = 0.0;
  istringstream(intervalo.substr(posColcheteInicial+1, (posVirgula - (posColcheteInicial+1)))) >> extremoEsquerdo;

  double extremoDireito = 0.0;
  istringstream(intervalo.substr(posVirgula+1, (posColcheteFinal - (posVirgula+1)))) >> extremoDireito;

  return tuple<double, double>(extremoEsquerdo, extremoDireito);
}


/* ///////////////////// C++11 ////////////////////////////////////
#include <string>
#include <tuple>
using namespace std;

//                                           "[a0, b0]"
tuple<double,double> tuplaDoIntervalo(string intervalo = "[0, 0]"){
  size_t posColcheteInicial = intervalo.find('[');
  size_t posColcheteFinal = intervalo.find(']');
  size_t posVirgula = intervalo.find(',');

  double extremoEsquerdo = stof( intervalo.substr(posColcheteInicial+1, (posVirgula - (posColcheteInicial+1))) );
  double extremoDireito = stof( intervalo.substr(posVirgula+1, (posColcheteFinal - (posVirgula+1))) );

  tuple<double, double> resultado(extremoEsquerdo, extremoDireito);

  return resultado;
}
*/
