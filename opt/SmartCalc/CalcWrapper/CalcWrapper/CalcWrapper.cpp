// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CalcWrapper.h"

#include "Model/rpn.h"

// Если вы работаете на Linux, вместо __declspec(dllexport) используется атрибут
// __attribute__((visibility("default"))) :
#if defined(_WIN64)
extern "C" __declspec(dllexport) double CalculateValue(const char* temp,
                                                       double x)
#else
extern "C" __attribute__((visibility("default"))) double CalculateValue(
    const char* temp, double x)
#endif
{
  std::string calcStr = temp;

  my::ModelCalc calc;
  return calc.Calc(calcStr, x);
}
