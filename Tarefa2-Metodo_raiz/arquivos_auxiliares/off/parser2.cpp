#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
// #include <sstream>
// #include <iterator>

using namespace std;


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

void removeChar(string& input, const char c){ input.erase(remove(input.begin(),input.end(), c),input.end()); }

void adicionarCoeficiente(string& input){
	string::size_type posX=1;
	string delim = "x";

	if(!input.empty()){
    // if((input[0] == 'x')){ input.insert(0, "+1"); ++posX; }
		if(!(input.compare(0,1,delim))){ input.insert(0, "+1"); ++posX; }
		else if((input[0] == '-')){ input.insert(1, "1"); ++posX; }
		for(; (posX = input.find(delim, posX)) != string::npos; posX += delim.size()){
      if( input[posX+1] != '^') input.insert(posX+1, "^1");
			if( !isdigit(input.at(posX-1)) ) input.insert(posX, "1");
    }
	}
}

void convert(string& input){
  removeChar(input,' ');
  adicionarCoeficiente(input);

  string buffer(input);
  string::size_type  n;
  const string delim("x^");
  // const string delim("+");
  // for( n=1; n = buffer.find(delim,  n))!=string::npos;  n += delim.size()){
  //   cout << "find on: " << n << endl;
  //   input.insert(n, ":");
  // }
  vector<string> temp = {"+","-"};
  unsigned short i, offset;
  for(i=offset=0, n=1; (i < 2);  n += delim.size()){
    if( (n = buffer.find_first_of(temp[i],  n)) != string::npos){
      input.insert(n+offset, "x^");
      offset += 2;
    }
    else ++i;
  }

  auto a = split_int(input, "x^");
  // std::cout << "\ndepois da quebra: " << std::endl;
  for(int digit : a) cout << digit << ", ";

  // string original = "-2x^1+3x^2-4";
  // size_t s = original.find("+");
  // size_t e = original.find("^", s);
  // string sub = original.substr(s + 1, e - s -1);
  // cout << sub << " == "<< endl;
}



int main(int argc, char** argv){
  if(argc != 2) return 1;
  string funcao(argv[1]);
  
  // cout << funcao << endl;
  convert(funcao);

//   convert(funcao);
// // -9x^6 +12x^3 -23x^2 +9x -6
//   auto a = split(funcao, delimiter);
//   // auto a = split("-9x^6:+12x^3:-23x^2:+9x:-6", ":");
//   for(string word : a) cout << word << endl;
  return 0;
}


void replaceSubStringsOf(string& str, const string s = "x^", const string t = ":"){
  string::size_type n;
  for(n=0; (n =  str.find(s, n)) != std::string::npos; n+=t.size())
    str.replace( n, s.size(), t );
}


vector<string> split(string data, string token){
    vector<string> output;
    size_t pos = string::npos; // size_t to avoid improbable overflow
    do{
        pos = data.find(token);
        output.push_back(data.substr(0, pos));
        if(string::npos != pos) data = data.substr(pos + token.size());
    } while(string::npos != pos);
    return output;
}


/*
string str,sub; // str is string to search, sub is the substring to search for

vector<size_t> positions; // holds all the positions that sub occurs within str

size_t pos = str.find(sub, 0);
while(pos != string::npos)
{
    positions.push_back(pos);
    pos = str.find(sub,pos+1);
}
*/


/*
// You could also take an existing vector as a parameter.
vector<string> split(string str, char delimiter){
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while(getline(ss, tok, delimiter)) internal.push_back(tok);
  return internal;
}

int main(int argc, char **argv) {
  string myCSV = "-9x^6:+12x^3:-23x^2:+9x:-6";
  vector<string> sep = split(myCSV, ':');

  // If using C++11 (which I recommend)
  for(string t : sep) cout << t << endl;

  // for(int i = 0; i < sep.size(); ++i)   cout << sep[i] << endl;
}
*/

/*
int main() {
    using namespace std;
    string sentence = "And I feel fine...";
    istringstream iss(sentence);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
    for(string word : tokens) cout << word << endl;
}
*/
