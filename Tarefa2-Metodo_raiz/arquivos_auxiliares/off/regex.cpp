// regex_iterator constructor
#include <iostream>
#include <string>
#include <regex>

int main ()
{
  std::string s ("-1h^1+2h^2-3h^3+3");
  std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

  std::regex_iterator<std::string::iterator> rit ( s.begin(), s.end(), e );
  std::regex_iterator<std::string::iterator> rend;

  while (rit!=rend) {
    std::cout << rit->str() << std::endl;
    ++rit;
  }

  return 0;
}