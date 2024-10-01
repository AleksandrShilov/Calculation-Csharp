#include "validate.h"

namespace my {

Validation::Validation(std::string const &str) : infix_str_(str), error_("Ok") {
  ValidationStr();
}

int Validation::ValidationOperators(size_t pos) const {
  int res = 0;
  std::string operators = "+-/*^";
  std::string exceptions = "cstalsx(";
  if (operators.find(infix_str_[pos]) != std::string::npos) {
    if (infix_str_[pos] != '-') {
      pos--;
      if (!(infix_str_[pos] >= '0' && infix_str_[pos] <= '9') &&
          !(infix_str_[pos] == ')')) {
        if (infix_str_[pos] != 'x') {
          res = 1;
        }
      }

      pos++;
      pos++;

      if (!(infix_str_[pos] >= '0' && infix_str_[pos] <= '9') &&
          !(infix_str_[pos] == '(')) {
        if (!(exceptions.find(infix_str_[pos]) != std::string::npos)) {
          res = 1;
        }
      }

    } else {
      pos--;
      if (!(infix_str_[pos] >= '0' && infix_str_[pos] <= '9') &&
          !(infix_str_[pos] == '(' || infix_str_[pos] == ')')) {
        if (infix_str_[pos] == 'x') {
          res = 0;
        }
      }

      pos++;
      pos++;

      if (!(infix_str_[pos] >= '0' && infix_str_[pos] <= '9')) {
        if (!(exceptions.find(infix_str_[pos]) != std::string::npos)) {
          res = 1;
        }
      }
    }
  }

  return res;
}

int Validation::ValidationZero(size_t pos) const {
  if (infix_str_[pos] == '0') {
    pos--;
    if (infix_str_[pos] == '/') {
      return 1;
    }
  }
  return 0;
}

int Validation::ValidationBracket(size_t pos, int &flag_bracket) const {
  int err = 0;
  std::string exceptions_right = ")+-/*^m";
  std::string exceptions_left = "(+-/*^";
  std::string last_character = "sntdg";

  if (infix_str_[pos] == '(') {
    flag_bracket++;
    if (pos > 1) {
      pos--;
      if (!(exceptions_left.find(infix_str_[pos]) != std::string::npos) &&
          !(last_character.find(infix_str_[pos]) != std::string::npos) &&
          !(infix_str_[pos] == 0)) {
        err = 1;
      }
    }
  } else if (infix_str_[pos] == ')') {
    flag_bracket--;
    pos++;
    if (!(exceptions_right.find(infix_str_[pos]) != std::string::npos) &&
        !(infix_str_[pos] == '\0')) {
      err = 1;
    }
  }
  return err;
}

int Validation::ValidationDot(size_t pos) {
  if (infix_str_[pos] == '.') {
    --pos;
    if (!(infix_str_[pos] >= '0' && infix_str_[pos] <= '9')) {
      return 1;
    }
    ++pos;
    ++pos;
    if (!(infix_str_[pos] >= '0' && infix_str_[pos] <= '9')) {
      return 1;
    }
  }
  return 0;
}

int Validation::ValidationAsin(size_t &pos) const {
  int res = 0;
  pos++;
  if (infix_str_[pos] == 'i') {
    pos++;
    if (!(infix_str_[pos] == 'n')) {
      res = 1;
    }
  } else {
    res = 1;
  }

  return res;
}

int Validation::ValidationAcos(size_t &pos) const {
  int res = 0;
  pos++;
  if (infix_str_[pos] == 'o') {
    pos++;
    if (!(infix_str_[pos] == 's')) {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}

int Validation::ValidationAtan(size_t &pos) const {
  int res = 0;
  pos++;
  if (infix_str_[pos] == 'a') {
    pos++;
    if (!(infix_str_[pos] == 'n')) {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}

int Validation::ValidationSinSqrt(size_t &pos) const {
  int res = 0;
  pos++;
  if (infix_str_[pos] == 'i') {
    pos++;
    if (!(infix_str_[pos] == 'n')) {
      res = 1;
    }
  } else if (infix_str_[pos] == 'q') {
    pos++;
    if (infix_str_[pos] == 'r') {
      pos++;
      if (!(infix_str_[pos] == 't')) {
        res = 1;
      }
    } else {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}

int Validation::ValidationCos(size_t &pos) const {
  int res = 0;
  pos++;
  if (infix_str_[pos] == 'o') {
    pos++;
    if (!(infix_str_[pos] == 's')) {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}

int Validation::ValidationLn(size_t &pos) const {
  int res = 0;
  pos++;
  if (infix_str_[pos] == 'o') {
    pos++;
    if (!(infix_str_[pos] == 'g')) {
      res = 1;
    }
  } else if (infix_str_[pos] == 'n') {
    res = 0;
  } else {
    res = 1;
  }
  return res;
}

int Validation::ValidationTan(size_t &pos) const {
  int res = 0;
  pos++;
  if (infix_str_[pos] == 'a') {
    pos++;
    if (!(infix_str_[pos] == 'n')) {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}

int Validation::ValidationMod(size_t &pos) const {
  int res = 0;
  pos++;
  if (infix_str_[pos] == 'o') {
    pos++;
    if (!(infix_str_[pos] == 'd')) {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}

int Validation::ValidationTrigonometric(size_t &pos) const {
  int res = 0;
  std::string first_character = "aclstm";
  std::string exceptions = ")(+-/*^x.";

  if (first_character.find(infix_str_[pos]) != std::string::npos) {
    if (infix_str_[pos] == 'a') {
      pos++;
      if (infix_str_[pos] == 's') {
        res = ValidationAsin(pos);
      } else if (infix_str_[pos] == 'c') {
        res = ValidationAcos(pos);
      } else if (infix_str_[pos] == 't') {
        res = ValidationAtan(pos);
      }
    } else if (infix_str_[pos] == 's') {
      res = ValidationSinSqrt(pos);
    } else if (infix_str_[pos] == 'c' || infix_str_[pos] == 'l' ||
               infix_str_[pos] == 't') {
      if (infix_str_[pos] == 'c') {
        res = ValidationCos(pos);
      } else if (infix_str_[pos] == 'l') {
        res = ValidationLn(pos);
      } else if (infix_str_[pos] == 't') {
        res = ValidationTan(pos);
      }
    } else if (infix_str_[pos] == 'm') {
      res = ValidationMod(pos);
    }
  } else if ((infix_str_[pos] >= '0' && infix_str_[pos] <= '9') ||
             exceptions.find(infix_str_[pos]) != std::string::npos) {
    res = 0;
  } else if (infix_str_[pos] == 'e') {
    pos++;
    if (infix_str_[pos] == '+' || infix_str_[pos] == '-') {
      res = 0;
    }
  } else {
    res = 1;
  }
  return res;
}

int Validation::ValidationStr() {
  int result = 0;
  int flag_bracket = 0;

  for (size_t i = 0; i < infix_str_.size(); ++i) {
    if (ValidationOperators(i)) {
      error_ = "The operator was entered incorrectly!";
      ++result;
      break;
    }

    if (ValidationZero(i)) {
      error_ = "It is not desirable to divide by zero :)";
      ++result;
      break;
    }

    if (ValidationBracket(i, flag_bracket)) {
      error_ = "The bracket and operators was entered incorrectly!";
      ++result;
      break;
    }

    if (ValidationDot(i)) {
      error_ = "The point was entered incorrectly!";
      ++result;
      break;
    }

    if (ValidationTrigonometric(i)) {
      error_ = "The trigonometric function is incorrectly entered!";
      ++result;
      break;
    }
  }

  if (flag_bracket) {
    error_ = "The bracket was entered incorrectly!";
    ++result;
  }

  return result;
}

}  // namespace my
