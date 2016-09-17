#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include <stdio.h>
#define show(v,dir) { for(auto const i: v) printf(dir, i);  cout << endl; }


void removeSpaces(string& input){ input.erase(remove(input.begin(),input.end(),' '),input.end()); }

void adicionarCoeficiente(string& input){
	string::size_type posX=1;
	string delim = "x";

	if(!input.empty()){
		if((input[0] == 'x')){ input.insert(0, "+1"); ++posX; }
		else if((input[0] == '-')){ input.insert(1, "1"); ++posX; }
		for(; (posX = input.find(delim, posX)) != string::npos; posX += delim.size())
			if( !isdigit(input.at(posX-1)) ) input.insert(posX, "1");
	}
}

int main(int argc, char* argv[]){
	if(argc != 2) return 1;

	string funcao(argv[1]), buff;
	vector<int> coeficiente_grau;
	unsigned posVector(0);
	size_t posX, posSinal;

	removeSpaces(funcao);
	adicionarCoeficiente(funcao);
	cout << funcao << endl;

	for(unsigned posCurrChar(0); posCurrChar < funcao.length(); ){

		if( (posX = funcao.find_first_of("x", posCurrChar+1)) == string::npos ){
			buff.assign(funcao, posCurrChar, funcao.length() - (posCurrChar)); // buff := termo independente
			coeficiente_grau.push_back(stoi(buff));
			break;
		}

		buff.assign(funcao, posCurrChar, posX-posCurrChar);
		coeficiente_grau.push_back(stoi(buff));
		posCurrChar = posX+1; // pára no circunflexo.

		if(funcao[posCurrChar] == '^'){
			posSinal = funcao.find_first_of("+-", posCurrChar);
			buff.assign(funcao, posCurrChar+1, (posSinal)-(posCurrChar));
			posCurrChar = posSinal;
			coeficiente_grau.push_back(stoi(buff)); // inserção do grau.
		}
		else coeficiente_grau.push_back(1); // grau 1.

	}
	show(coeficiente_grau, "%d, ");

	/*
	cout << funcao << endl;
	posX = funcao.find("x");
	if(posX!=string::npos) cout << posX << endl;
	*/

/*
	// for(char it : funcao) cout << it << "_";
	// cout << endl;

	// int posFound = funcao.find("x");
	// cout << posFound << endl; return 1;

	// buff.assign(funcao+0, 1);
	buff.assign(funcao,0, 1);
	cout << buff << endl;
	coeficiente_grau.push_back(stoi(buff));

	// buff.assign(funcao+2, 1);
	buff.assign(funcao,2, 1);
	cout << buff << endl;
	coeficiente_grau.push_back(stoi(buff));

	show(coeficiente_grau);

	for(vector<int>::iterator it = coeficiente_grau.begin(); it != coeficiente_grau.end(); it += 2)
		cout << *it << *(it + 1) << endl;
	*/

	return 0;
}
