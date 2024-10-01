#ifndef PROJECT_VALIDATION_H_
#define PROJECT_VALIDATION_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>

namespace my {

class Validation {
 public:
  explicit Validation(std::string const &str);
  Validation(const Validation &other) = delete;
  Validation &operator=(const Validation &other) = delete;
  Validation(Validation &&other) = delete;
  Validation operator=(Validation &&other) = delete;
  ~Validation() = default;

 public:
  std::string GetError() { return error_; }

 private:
  int ValidationStr();
  int ValidationOperators(size_t pos) const;
  int ValidationZero(size_t pos) const;
  int ValidationBracket(size_t pos, int &flag_bracket) const;
  int ValidationDot(size_t pos);
  int ValidationAsin(size_t &pos) const;
  int ValidationAcos(size_t &pos) const;
  int ValidationAtan(size_t &pos) const;
  int ValidationSinSqrt(size_t &pos) const;
  int ValidationCos(size_t &pos) const;
  int ValidationLn(size_t &pos) const;
  int ValidationTan(size_t &pos) const;
  int ValidationMod(size_t &pos) const;
  int ValidationTrigonometric(size_t &pos) const;

 private:
  std::string infix_str_;
  std::string error_;
};

}  // namespace my

#endif  // PROJECT_VALIDATION_H_
