#ifndef PROJECT_PARS_H_
#define PROJECT_PARS_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>

#include "calculate.h"
#include "calculatedeposit.h"
#include "parse.h"
#include "validate.h"



/*
  cos - c, sin - s, tan - t, acos - o
  asin - i, atan - a, sqrt - q, ln - l
  log - g, mode - m
*/

namespace my {

class ModelCalc {
 public:
  explicit ModelCalc();
  ModelCalc(const ModelCalc &other) = delete;
  ModelCalc &operator=(const ModelCalc &other) = delete;
  ModelCalc(ModelCalc &&other) = delete;
  ModelCalc operator=(ModelCalc &&other) = delete;
  ~ModelCalc() = default;

 public:
  std::string CheckInputStr(std::string const &str) const;
  double Calc(std::string const &str, double x);
  void CalcCredit(double const &amount_credit, double const &percent_credit,
                  double const &time_credit, double &month_pay,
                  double &accrued_inter, double &all_credit);
  double CalcCreditDif(double const &sum_credit, int const &time_credit,
                       double const &percent_credit, int const &count_pay);

 public:
  double CalculationByDaysCapital(int const &current_year,
                                  double const &percent_deposit,
                                  double const &deposit_amount);
  double CalculateTax(double const &tax_rate, double const &accrued_interest);
  double CalculatAccruedInterestForMonthWithoutCapitaliz(
      int const &temp_year, int const &temp_month, double const &deposit_amount,
      double const &percent_deposit);
  double CalculatAccruedInterestForMonthWithCapitaliz(
      int const &temp_year, int const &temp_month, double const &deposit_amount,
      double const &percent_deposit);
  double CalculationByDays(int const &current_year,
                           double const &percent_deposit,
                           double const &deposit_amount);
  // year
  double CalculatForYears(int const &current_year,
                          double const &percent_deposit,
                          double const &deposit_amount);
  bool CheckingForLeapYear(int const &year, int &temp_number_days_year) const;

  // day
  double CalculatForDayWithoutCapitalization(int const &placement_period,
                                             int const &deposit_year,
                                             double const &deposit_amount,
                                             double const &percent_deposit);
  bool CheckInputNumberFractional(std::string const &str);
  double CalculateSimplePercentage(std::string const &str);

 private:
  std::string infix_str_;
  double result_;
};

}  // namespace my

#endif  // PROJECT_PARS_H_
