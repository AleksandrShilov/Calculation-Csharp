#include "rpn.h"

namespace my {

ModelCalc::ModelCalc() : infix_str_(""), result_(0) {}

std::string ModelCalc::CheckInputStr(std::string const &str) const {
  Validation error(str);
  std::string answer = error.GetError();
  return answer;
}

double ModelCalc::Calc(std::string const &str, double x) {
  infix_str_ = str;
  if (CheckInputStr(infix_str_) == "Ok") {
    my::Parse parse(infix_str_);
    my::Calculate calculate(parse.GetPostfixStr());
    result_ = calculate.CalculatePostfix(x);
  }
  return result_;
}

void ModelCalc::CalcCredit(double const &amount_credit,
                           double const &percent_credit,
                           double const &time_credit, double &month_pay,
                           double &accrued_inter, double &all_credit) {
  double month_loan_rate = percent_credit / 12 / 100;
  double annuity_ratio =
      (month_loan_rate * pow((1 + month_loan_rate), time_credit)) /
      (pow((1 + month_loan_rate), time_credit) - 1);
  month_pay = annuity_ratio * amount_credit;
  all_credit = month_pay * time_credit;
  accrued_inter = all_credit - amount_credit;
}

double ModelCalc::CalcCreditDif(double const &sum_credit,
                                int const &time_credit,
                                double const &percent_credit,
                                int const &count_pay) {
  double month_pay = 0;
  month_pay = (sum_credit / time_credit) +
              (sum_credit - (sum_credit / time_credit) * count_pay) *
                  (percent_credit / 100) / 12;
  return month_pay;
}

double ModelCalc::CalculationByDaysCapital(int const &current_year,
                                           double const &percent_deposit,
                                           double const &deposit_amount) {
  CalculateDeposit calculatedeposit;
  return calculatedeposit.CalculationByDaysCapital(
      current_year, percent_deposit, deposit_amount);
}

double ModelCalc::CalculateTax(const double &tax_rate,
                               const double &accrued_interest) {
  CalculateDeposit calculatedeposit;
  return calculatedeposit.CalculateTax(tax_rate, accrued_interest);
}

double ModelCalc::CalculatAccruedInterestForMonthWithoutCapitaliz(
    int const &temp_year, int const &temp_month, double const &deposit_amount,
    double const &percent_deposit) {
  CalculateDeposit calc_deposit;
  return calc_deposit.CalculatAccruedInterestForMonthWithoutCapitaliz(
      temp_year, temp_month, deposit_amount, percent_deposit);
}

double ModelCalc::CalculatAccruedInterestForMonthWithCapitaliz(
    const int &temp_year, const int &temp_month, const double &deposit_amount,
    const double &percent_deposit) {
  CalculateDeposit calc_deposit;
  return calc_deposit.CalculatAccruedInterestForMonthWithCapitaliz(
      temp_year, temp_month, deposit_amount, percent_deposit);
}

double ModelCalc::CalculationByDays(const int &current_year,
                                    const double &percent_deposit,
                                    const double &deposit_amount) {
  CalculateDeposit calc_deposit;
  return calc_deposit.CalculationByDays(current_year, percent_deposit,
                                        deposit_amount);
}

double ModelCalc::CalculatForYears(const int &current_year,
                                   const double &percent_deposit,
                                   const double &deposit_amount) {
  CalculateDeposit calc_deposit;
  return calc_deposit.CalculatForYears(current_year, percent_deposit,
                                       deposit_amount);
}

bool ModelCalc::CheckingForLeapYear(const int &year,
                                    int &temp_number_days_year) const {
  CalculateDeposit calc_deposit;
  return calc_deposit.CheckingForLeapYear(year, temp_number_days_year);
}

double ModelCalc::CalculatForDayWithoutCapitalization(
    const int &placement_period, const int &deposit_year,
    const double &deposit_amount, const double &percent_deposit) {
  CalculateDeposit calc_deposit;
  return calc_deposit.CalculatForDayWithoutCapitalization(
      placement_period, deposit_year, deposit_amount, percent_deposit);
}

bool ModelCalc::CheckInputNumberFractional(std::string const &str) {
  int flag_err = false;
  int flag_dot = 0;

  for (size_t i = 0; i < str.length(); i++) {
    if ((str.data()[i] >= '0' && str.data()[i] <= '9') ||
        str.data()[i] == '.') {
      if (str.data()[i] == '.') {
        flag_dot++;
      }

      if (flag_dot > 1) {
        flag_err = true;
        break;
      }
    } else {
      flag_err = true;
      break;
    }
  }
  return flag_err;
}

double ModelCalc::CalculateSimplePercentage(std::string const &str) {
  double result = 0;
  if (!CheckInputNumberFractional(str)) {
    result = stof(str) / 100;
  }
  return result;
}

}  // namespace my
