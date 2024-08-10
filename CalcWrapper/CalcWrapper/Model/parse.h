#ifndef PROJECT_PARSE_H_
#define PROJECT_PARSE_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>

namespace my {

class Parse {
 public:
  Parse() = delete;
  explicit Parse(std::string const &expr);
  Parse(const Parse &other) = delete;
  Parse &operator=(const Parse &other) = delete;
  Parse(Parse &&other) = delete;
  Parse &operator=(Parse &&other) = delete;
  ~Parse() = default;

 public:
  double GetResult() { return result_; }
  std::string GetPostfixStr() { return postfix_str_; }

 private:
  void ConversionExponent(std::string &postfix_str, size_t &pos);
  void ParseNumber(std::string &postfix_str, size_t &pos);
  int GetPriority(char const ch) const;
  void CheckUnaryMinus(char &ch, std::string const &infix_str,
                       size_t const &pos) const;
  void ParseOperator(char const ch, std::stack<char> &stack_oper);
  void ParseLeftBracket(char const ch, std::stack<char> &stack_oper) const;
  void ParseRightBracket(char const ch, std::stack<char> &stack_oper);
  void PushTrigonometric(std::string const &trig,
                         std::stack<char> &stack_oper) const;
  void ParseTrigonometric(char const ch, std::stack<char> &stack_oper,
                          size_t &pos) const;
  void ParseX(char const ch);
  void ToPostFix();

 private:
  std::string infix_str_;
  std::string postfix_str_;
  double result_;
  int err_;
};

}  // namespace my

#endif  // PROJECT_PARSE_H_
