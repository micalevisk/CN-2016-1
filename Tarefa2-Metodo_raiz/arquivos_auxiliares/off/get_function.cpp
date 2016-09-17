//g++ -std=c++11 -o parser get_function.cpp
//
// [get_function.cpp]
// Created by Micael Levi on 07/15/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//
// Recebe uma string (que representa uma função polinomial) e retorna o vetor de inteiros correspondente.
//


#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

using namespace std;

char variavel = 'x'; /***/

void removeChar(string& input, const char c){
  input.erase(remove(input.begin(),input.end(), c),input.end());
}


void adicionarCoeficiente(string& input){
  string::size_type posX=1;
  string var(1, ::variavel);
	if(!input.empty()){
		if(input[0] == ::variavel){ input.insert(0, "+1"); ++posX; }
		else if((input[0] == '-')){ input.insert(1, "1"); ++posX; }
		for(; (posX = input.find(var, posX)) != string::npos; posX += var.size()){
			if( input[posX+1] != '^') input.insert(posX+1, "^1");
			if( !isdigit(input.at(posX-1)) ) input.insert(posX, "1");
		}
	}
}


vector<int> split_int(string data, string token){
    vector<int> output;
    size_t pos = string::npos; // size_t to avoid improbable overflow
    do{
        pos = data.find(token);
        output.push_back(stoi(data.substr(0, pos)));
        if(string::npos != pos) data = data.substr(pos + token.size());
    } while(string::npos != pos);
    return output;
}

//////////////////////////////////////////////////////////////////////

vector<int> definir_funcao(string& input){
  removeChar(input,' ');
  adicionarCoeficiente(input);

  string::size_type  n;
  string delim("^");  delim.insert(0, 1, ::variavel);
  unsigned short i, offset;

  string buffer(input);
	for(offset=0, n=1; (n = buffer.find_first_of("+", n))!=string::npos;  n += delim.size()){
  	input.insert(n+offset, delim);
  	offset += delim.size();
  }

  buffer = input;
	for(offset=0, n=1; (n = buffer.find_first_of("-", n))!=string::npos;  n += delim.size()){
  	input.insert(n+offset, delim);
  	offset += delim.size();
  }

  return split_int(input, delim);
}


#include <stdio.h>
int main(int argc, char** argv){
  if(argc != 2) return 1;
  string funcao(argv[1]);

  for(char c : funcao)
  	if(isalpha(c)){ ::variavel = c; break; }
  // cout << funcao << endl;
  auto a = definir_funcao(funcao);

//   std::cout << "\ndepois da quebra: " << std::endl;
// for(int digit : a) cout << digit << ", ";

	vector<int>::iterator inicio = a.begin();
	vector<int>::iterator final = ( a.size() % 2 ) ? a.end()-1 : a.end();
	vector<int>::iterator it;

	// IMPRESSÃO DO RESULTADO:
  for(it = inicio; it < final; it+=2)
  	printf("%+d%c^%u ", *it, variavel, *(it+1));
    // cout << *it << '^' << *(it+1) << ' ';
  if(it != a.end()) printf("%+d\n", a.at(a.size()-1) );

  return 0;
}



/*
TESTES:
x^1 + 3x^2 + x^3 -4
-x^1 + 2x^2 + x^3 -4
x+ 2x^2 + 3x^1
x + 2x^2 -3 x^3 -4
-9x^6 +12x -23x
-2x^1+^C -1245
 */
