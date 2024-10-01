#ifndef PROJECT_CALCULATE_H_
#define PROJECT_CALCULATE_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>

namespace my {

class Calculate {
 public:
  explicit Calculate(std::string const &str);
  Calculate(const Calculate &other) = delete;
  Calculate &operator=(const Calculate &other) = delete;
  Calculate(Calculate &&other) = delete;
  Calculate &operator=(Calculate &&other) = delete;
  ~Calculate() = default;

 public:
  void GetNumber(size_t &pos, std::string const &str);
  void CalculatePlus();
  void CalculateMinus();
  void CalculateUnaryMinus();
  void CalculateMult();
  void CalculateDiv();
  void CalculateDeg();
  void CalculateMod();
  void CalculateCos();
  void CalculateSin();
  void CalculateTan();
  void CalculateAcos();
  void CalculateAsin();
  void CalculateAtan();
  void CalculateLn();
  void CalculateLog();
  void CalculateSqrt();
  double CalculatePostfix(double const x);

 private:
  std::stack<double> stack_num_;
  std::string postfix_str_;
  double result_;
};

}  // namespace my

#endif  // PROJECT_CALCULATE_H_
