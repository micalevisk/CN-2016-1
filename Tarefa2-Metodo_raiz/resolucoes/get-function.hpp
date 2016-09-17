//
//  [get-function.hpp]
//  Created by Micael Levi on 07/15/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//
//  Recebe uma string (que representa uma função polinomial) e
//  retorna o vetor de inteiros no formato: [<coeficiente>,<grau>,...]
//
//  EXEMPLO DE FORMATO DA STRING: aX^g + bX^h - c
//  ONDE:
//    X     = qualquer caractere alfabético (variável da função);
//    a/b/c = números inteiros quaisquer (coeficiente e termo independente);
//    g/h   = números naturais quaisquer (grau do termo);
//  OBS:
//    Não funciona para mais de uma variável (programa abortado);
//    Tanto os coeficientes como os graus podem ser omitidos e serão considerados 1;
//    Menor polinônimo aceito: X
//    Os únicos caracteres válidos após o sinal são: X (a variável), espaços, dígitos;
//    Aceita apenas funções polinomiais (coeficientes inteiros);
//

#include <iostream> // cin, cout.
#include <vector>
#include <string>
#include <algorithm> // remove.
#include <sstream>
using namespace std;

char variavel = 'x';

void removeChar(string& input, const char c){
  input.erase(remove(input.begin(),input.end(), c),input.end());
}


void adicionarCoeficiente(string& input){
  string::size_type posX=1;
  string var(1, ::variavel);
	if(!input.empty()){
		if(input[0] == ::variavel){ input.insert(0, "+1"); ++posX; }
		else if((input[0] == '-') && (!isdigit(input[1]))){ input.insert(1, "1"); ++posX; }
		for(; (posX = input.find(var, posX)) != string::npos; posX += var.size()){
			if( input[posX+1] != '^'){
        if(isdigit(input[posX+1])) input.insert(posX+1, "^");
        else input.insert(posX+1, "^1");
      }
			if( !isdigit(input.at(posX-1)) ) input.insert(posX, "1");
		}
	}
}


vector<int> split_int(string data, string token){
    vector<int> output;
    size_t pos = string::npos; // size_t to avoid improbable overflow
    int result=0;

    do{
        pos = data.find(token);
        istringstream(data.substr(0, pos)) >> result;
        output.push_back(result);
        // output.push_back(stoi(data.substr(0, pos)));
        if(string::npos != pos) data = data.substr(pos + token.size());
    } while(string::npos != pos);
    return output;
}

//////////////////////////////////////////////////////////////////////

vector<int> definir_funcao(string& input){
  removeChar(input,' ');
  adicionarCoeficiente(input);

  // Encontra a primeira variável e a define como padrão.
  // for(char c : input) if(isalpha(c)){ ::variavel = c; break; }
  string::size_type posFirstVariavel = input.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
  if(posFirstVariavel == string::npos) exit(1); // aborta caso não tenha variável.
  ::variavel = input[posFirstVariavel];

  string buffer(input);
  removeChar(buffer, ::variavel);
  if((buffer.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")) != string::npos) exit(1); // aborta caso tenha mais variáveis.

  string::size_type  n;
  string delim("^");  delim.insert(0, 1, ::variavel);
  string::size_type tam = delim.length();
  buffer = input;
  unsigned short i, offset;

  for(offset=0, n=1; (n = buffer.find_first_of("+-", n)) != string::npos; n += tam){
    input.insert(n+offset, delim);
    offset += tam;
  }

  return split_int(input, delim);
}
