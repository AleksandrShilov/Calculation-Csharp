#include "parse.h"

namespace my {

Parse::Parse(std::string const &expr)
    : result_(0), err_(0), infix_str_(expr), postfix_str_("") {
  ToPostFix();
}

// экспоненциальная запись
void Parse::ConversionExponent(std::string &postfix_str, size_t &pos) {
  if (infix_str_[pos] == 'e') {
    postfix_str.push_back(' ');
    postfix_str.push_back('1');
    postfix_str.push_back('0');
    postfix_str.push_back(' ');
    pos++;
    if (infix_str_[pos] == '-') {
      pos++;
      while (isdigit(infix_str_[pos])) {
        postfix_str.push_back(infix_str_[pos]);
        pos++;
      }
      postfix_str.push_back(' ');
      postfix_str.push_back('~');
      postfix_str.push_back(' ');
      postfix_str.push_back('^');
      postfix_str.push_back(' ');
      postfix_str.push_back('*');
    } else if (infix_str_[pos] == '+') {
      pos++;
      while (isdigit(infix_str_[pos])) {
        postfix_str.push_back(infix_str_[pos]);
        pos++;
      }
      postfix_str.push_back(' ');
      postfix_str.push_back('^');
      postfix_str.push_back(' ');
      postfix_str.push_back('*');
    }
  }
}

void Parse::ParseNumber(std::string &postfix_str, size_t &pos) {
  if (isdigit(infix_str_[pos])) {
    while (isdigit(infix_str_[pos]) || infix_str_[pos] == '.') {
      postfix_str.push_back(infix_str_[pos]);
      pos++;
      ConversionExponent(postfix_str, pos);
    }
    postfix_str.push_back(' ');
  }
}

int Parse::GetPriority(char const ch) const {
  if (ch == '+' || ch == '-' || ch == '~') return 1;
  if (ch == '/' || ch == '*' || ch == 'm') return 2;
  if (ch == '^') return 3;
  if (ch == 'c' || ch == 's' || ch == 't' || ch == 'o' || ch == 'i' ||
      ch == 'a' || ch == 'l' || ch == 'q' || ch == 'g')
    return 4;
  return 0;
}

void Parse::CheckUnaryMinus(char &ch, std::string const &infix_str,
                            size_t const &pos) const {
  std::string operators = "+-*/^(";
  if (ch == '-' &&
      (pos == 0 || (operators.find(infix_str[pos - 1]) != std::string::npos))) {
    ch = '~';
  }
}

void Parse::ParseOperator(char const ch, std::stack<char> &stack_oper) {
  if (ch == '+' || ch == '-' || ch == '~' || ch == '*' || ch == '/' ||
      ch == '^') {
    if (stack_oper.size() == 0) {
      stack_oper.push(ch);
    } else if (GetPriority(ch) > GetPriority(stack_oper.top())) {
      stack_oper.push(ch);
    } else if (GetPriority(ch) <= GetPriority(stack_oper.top())) {
      while (stack_oper.size() > 0 &&
             GetPriority(ch) <= GetPriority(stack_oper.top())) {
        postfix_str_.push_back(stack_oper.top());
        postfix_str_.push_back(' ');
        stack_oper.pop();
      }
      stack_oper.push(ch);
    }
  }
}

void Parse::ParseLeftBracket(char const ch,
                             std::stack<char> &stack_oper) const {
  if (ch == '(') {
    stack_oper.push(ch);
  }
}

void Parse::ParseRightBracket(char const ch, std::stack<char> &stack_oper) {
  if (ch == ')') {
    while (stack_oper.size() > 0 && stack_oper.top() != '(') {
      postfix_str_.push_back(stack_oper.top());
      postfix_str_.push_back(' ');
      stack_oper.pop();
    }
    stack_oper.pop();
  }
}

void Parse::PushTrigonometric(std::string const &trig,
                              std::stack<char> &stack_oper) const {
  if (trig.find("acos") != std::string::npos) {
    stack_oper.push('o');
  } else if (trig.find("asin") != std::string::npos) {
    stack_oper.push('i');
  } else if (trig.find("atan") != std::string::npos) {
    stack_oper.push('a');
  } else if (trig.find("cos") != std::string::npos) {
    stack_oper.push('c');
  } else if (trig.find("sin") != std::string::npos) {
    stack_oper.push('s');
  } else if (trig.find("tan") != std::string::npos) {
    stack_oper.push('t');
  } else if (trig.find("ln") != std::string::npos) {
    stack_oper.push('l');
  } else if (trig.find("log") != std::string::npos) {
    stack_oper.push('g');
  } else if (trig.find("sqrt") != std::string::npos) {
    stack_oper.push('q');
  } else if (trig.find("mod") != std::string::npos) {
    stack_oper.push('m');
  }
}

void Parse::ParseTrigonometric(char const ch, std::stack<char> &stack_oper,
                               size_t &pos) const {
  if (ch == 'c' || ch == 's' || ch == 't' || ch == 'a' || ch == 'l' ||
      ch == 'm') {
    std::string trig;
    while (isalpha(infix_str_[pos])) {
      trig.push_back(infix_str_[pos]);
      pos++;
    }
    pos--;
    PushTrigonometric(trig, stack_oper);
  }
}

void Parse::ParseX(char const ch) {
  if (ch == 'x' || ch == 'X') {
    postfix_str_.push_back(ch);
    postfix_str_.push_back(' ');
  }
}

void Parse::ToPostFix() {
  std::stack<char> stack_oper;

  for (size_t i = 0; i < infix_str_.size(); i++) {
    ParseNumber(postfix_str_, i);
    ParseTrigonometric(infix_str_[i], stack_oper, i);
    ParseLeftBracket(infix_str_[i], stack_oper);
    ParseRightBracket(infix_str_[i], stack_oper);
    CheckUnaryMinus(infix_str_[i], infix_str_, i);
    ParseOperator(infix_str_[i], stack_oper);
    ParseX(infix_str_[i]);
  }

  while (stack_oper.size()) {
    postfix_str_.push_back(stack_oper.top());
    postfix_str_.push_back(' ');
    stack_oper.pop();
  }
}

}  // namespace my