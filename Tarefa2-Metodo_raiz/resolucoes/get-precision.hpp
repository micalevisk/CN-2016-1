//
//  [get-precision.hpp]
//  Created by Micael Levi on 07/15/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//
//  Dada uma constante double que representa o erro do cálculo,
//  retorna o número de casas decimais após o ponto
//

#include <string>
using namespace std;

unsigned short precisaoDoErro(string e = "0.01"){
  return e.find_first_not_of("0.") - e.find('.');
}
