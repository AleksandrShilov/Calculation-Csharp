#include <iostream>
#include <string>

#include "rpn.h"

int main() {
  // char arr[255];
  std::string str;
  std::cin >> str;
  my::ModelCalc x;

  std::cout << "Otvet " << x.Calc(str, 0) << std::endl;
  return 0;
}