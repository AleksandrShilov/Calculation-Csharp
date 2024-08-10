#ifndef CALCULATEDEPOSIT_H
#define CALCULATEDEPOSIT_H

#include <cmath>
#include <iomanip>
#include <iostream>

namespace my {

class CalculateDeposit {
 public:
  CalculateDeposit() = default;
  CalculateDeposit(const CalculateDeposit &other) = delete;
  CalculateDeposit &operator=(const CalculateDeposit &other) = delete;
  CalculateDeposit(CalculateDeposit &&other) = delete;
  CalculateDeposit &operator=(CalculateDeposit &&other) = delete;
  ~CalculateDeposit() = default;

 public:
  bool CheckingForLeapYear(int const &year, int &temp_number_days_year) const;
  double CalculateTax(double const &tax_rate, double const &accrued_interest);
  double CalculationByDaysCapital(int const &current_year,
                                  double const &percent_deposit,
                                  double const &deposit_amount);
  double CalculatAccruedInterestForMonthWithoutCapitaliz(
      int const &temp_year, int const &temp_month, double const &deposit_amount,
      double const &percent_deposit);
  double CalculatAccruedInterestForMonthWithCapitaliz(
      int const &temp_year, int const &temp_month, double const &deposit_amount,
      double const &percent_deposit);
  double CalculationByDays(int const &current_year,
                           double const &percent_deposit,
                           double const &deposit_amount);
  double CalculatForYears(int const &current_year,
                          double const &percent_deposit,
                          double const &deposit_amount);
  double CalculatForDayWithoutCapitalization(int const &placement_period,
                                             int const &deposit_year,
                                             double const &deposit_amount,
                                             double const &percent_deposit);
};

}  // namespace my

#endif  // CALCULATEDEPOSIT_H
