#include "calculate.h"

my::Calculate::Calculate(std::string const &str)
    : postfix_str_(str), result_(0) {}

void my::Calculate::GetNumber(size_t &pos, std::string const &str) {
  std::string numbers;
  while (isdigit(str[pos]) || str[pos] == '.') {
    numbers.push_back(str[pos]);
    pos++;
  }
  stack_num_.push(std::stod(numbers));
}

void my::Calculate::CalculatePlus() {
  double a, b;
  a = stack_num_.top();
  stack_num_.pop();
  b = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(a + b);
}

void my::Calculate::CalculateMinus() {
  double a, b;
  a = stack_num_.top();
  stack_num_.pop();
  b = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(b - a);
}

void my::Calculate::CalculateUnaryMinus() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(-a);
}

void my::Calculate::CalculateMult() {
  double a, b;
  a = stack_num_.top();
  stack_num_.pop();
  b = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(a * b);
}

void my::Calculate::CalculateDiv() {
  double a, b;
  a = stack_num_.top();
  stack_num_.pop();
  b = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(b / a);
}

void my::Calculate::CalculateDeg() {
  double a, b;
  a = stack_num_.top();
  stack_num_.pop();
  b = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(pow(b, a));
}

void my::Calculate::CalculateMod() {
  double a, b;
  a = stack_num_.top();
  stack_num_.pop();
  b = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(fmod(b, a));
}

void my::Calculate::CalculateCos() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(cos(a));
}

void my::Calculate::CalculateSin() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(sin(a));
}

void my::Calculate::CalculateTan() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(tan(a));
}

void my::Calculate::CalculateAcos() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(acos(a));
}

void my::Calculate::CalculateAsin() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(asin(a));
}

void my::Calculate::CalculateAtan() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(atan(a));
}

void my::Calculate::CalculateLn() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(log(a));
}

void my::Calculate::CalculateLog() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(log10(a));
}

void my::Calculate::CalculateSqrt() {
  double a;
  a = stack_num_.top();
  stack_num_.pop();
  stack_num_.push(sqrt(a));
}

double my::Calculate::CalculatePostfix(double const x) {
  for (size_t i = 0; i < postfix_str_.size(); i++) {
    if (isdigit(postfix_str_[i])) {
      GetNumber(i, postfix_str_);
    }
    if (postfix_str_[i] == 'x' || postfix_str_[i] == 'X') {
      stack_num_.push(x);
    }
    if (postfix_str_[i] == '+') {
      CalculatePlus();
    } else if (postfix_str_[i] == '-') {  // minus
      CalculateMinus();
    } else if (postfix_str_[i] == '~') {  // unary minus
      CalculateUnaryMinus();
    } else if (postfix_str_[i] == '*') {  // mult
      CalculateMult();
    } else if (postfix_str_[i] == '/') {  // division
      CalculateDiv();
    } else if (postfix_str_[i] == '^') {  // degree
      CalculateDeg();
    } else if (postfix_str_[i] == 'm') {  // mod
      CalculateMod();
    } else if (postfix_str_[i] == 'c') {  // cos
      CalculateCos();
    } else if (postfix_str_[i] == 's') {  // sin
      CalculateSin();
    } else if (postfix_str_[i] == 't') {  // tan
      CalculateTan();
    } else if (postfix_str_[i] == 'o') {  // acos
      CalculateAcos();
    } else if (postfix_str_[i] == 'i') {  // asin
      CalculateAsin();
    } else if (postfix_str_[i] == 'a') {  // atan
      CalculateAtan();
    } else if (postfix_str_[i] == 'l') {  // ln
      CalculateLn();
    } else if (postfix_str_[i] == 'g') {  // log
      CalculateLog();
    } else if (postfix_str_[i] == 'q') {  // sqrt
      CalculateSqrt();
    }
  }

  double result = 0;
  if (stack_num_.size()) {
    result = stack_num_.top();
    stack_num_.pop();
  }
  return result;
}
