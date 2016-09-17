//
//  [calcularRaizReal.cpp]
//  Created by Micael Levi on 07/15/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//
//  Executar o seguinte comando para compilar:
//  $ g++ -std=c++11 -o metodo_x calcularRaizReal.cpp
//
//  e.g. de execução:
//  $ ./metodo_newtonRapshon "x^2 + 2^x - 3" "0.001" "1"
//  $ ./metodo_bisseccao "x3 - 9x + 3" "0.01" "[0,1]"
//  $ ./metodo_falsaPosicao "x^3 - 9x + 3" "0.01" "[0,1]"
//                           ^^^^^^^^^^^^^   ^^^^^
//                           ~ função        ~ erro (tolerância/precisão)
//


///////////////////////////////////
#include "get-precision.hpp"
#include "get-function.hpp"

#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const unsigned short NARGS = 4;
#define str_FUNCAO argv[1]
#define str_ERRO string(argv[2])
#define str_INTERVALO_VALOR argv[3]
using namespace std;
///////////////////////////////////


/*========[ESCOLHER UM DOS MÉTODOS]============*/
#include "bisseccao/usarBisseccao.hpp"
// #include "falsaPosicao/usarFalsaPosicao.hpp"
// #include "newtonRaphson/usarNewtonRaphson.hpp"
/*=============================================*/


int main(int argc, char** argv){

  if(argc != NARGS){
    cerr << "Execute com os seguintes argumentos: <funcao_polinomial> <precisao> <intervalo/aproximacao_inicial>\n";
    cerr << "(tudo entre aspas duplas!)\n";
    return 1;
  }

  string funcao(str_FUNCAO);

  const unsigned short nCasasErro  = precisaoDoErro(str_ERRO);
  auto fx = definir_funcao(funcao); // parser: string -> vector

  /*
  // ++++++++++++++++++++++[IMPRESSÃO DOS VALORES DE ENTRADA]++++++++++++++++++++++++
  vector<int>::iterator inicio = fx.begin();
  vector<int>::iterator final = ( fx.size() % 2 ) ? fx.end()-1 : fx.end();
  vector<int>::iterator it;
  printf("função           : ");
  for(it = inicio; it < final; it+=2) printf("%+d%c^%u ", *it, ::variavel, *(it+1));
  if(it != fx.end()) printf("%+d", fx.at(fx.size()-1));
  printf("\nerro             : %.*f",nCasasErro , str_ERRO ); // termo independente.
  // printf("\nintervalo inicial: %s\n\n", str_INTERVALO_VALOR);     // intervalo inicial.
  printf("\nvalor inicial    : %s\n\n", str_INTERVALO_VALOR);     // aproximação inicial.
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  */

  double precisao=0; istringstream(str_ERRO) >> precisao; // convertendo string para double
  double raiz = calcularRaiz(fx, precisao, str_INTERVALO_VALOR, nCasasErro+1);

  cout << "Uma raiz eh = " << fixed << setprecision(nCasasErro+1) << raiz << endl;

  return 0;
}

//  http://www.cplusplus.com/articles/D9j2Nwbp/#n2s
//  https://en.wikipedia.org/wiki/Include_guard
