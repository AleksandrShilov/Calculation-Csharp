#include "calculatedeposit.h"

namespace my {

// проверка на високосный год
bool CalculateDeposit::CheckingForLeapYear(int const &year,
                                           int &temp_number_days_year) const {
  temp_number_days_year = 365;
  bool leap_year = false;
  if (year % 4 == 0) {
    if (year % 100 == 0) {
      if (year % 400 == 0) {
        leap_year = true;
        temp_number_days_year = 366;
      }
    } else {
      leap_year = true;
      temp_number_days_year = 366;
    }
  }
  return leap_year;
}

double CalculateDeposit::CalculateTax(double const &tax_rate,
                                      double const &accrued_interest) {
  double no_tax = 1000000 * 4.25 / 100;
  double tax = 0;

  if (accrued_interest > no_tax) {
    tax = (accrued_interest - no_tax) * tax_rate / 100;
  }
  return tax;
}

// вычисления для "дней" в таблицу
double CalculateDeposit::CalculationByDaysCapital(
    int const &current_year, double const &percent_deposit,
    double const &deposit_amount) {
  int number_days_year;
  double result_amount;
  double accrued_interest;
  CheckingForLeapYear(current_year, number_days_year);
  result_amount =
      deposit_amount * pow((1 + (percent_deposit / 100) / number_days_year), 1);
  accrued_interest = result_amount - deposit_amount;
  return accrued_interest;
}

// вычисление начисленных процентов, если в чекбоксе месяц
double CalculateDeposit::CalculatAccruedInterestForMonthWithoutCapitaliz(
    int const &temp_year, int const &temp_month, double const &deposit_amount,
    double const &percent_deposit) {
  int const array_year[13] = {0,  31, 28, 31, 30, 31, 30,
                              31, 31, 30, 31, 30, 31};
  double percent_month;
  int temp_number_days_year = 365;
  CheckingForLeapYear(temp_year, temp_number_days_year);

  if (temp_month == 2 &&
      CheckingForLeapYear(temp_year, temp_number_days_year)) {
    percent_month =
        (deposit_amount * percent_deposit * 29 / temp_number_days_year) / 100;
  } else {
    percent_month = (deposit_amount * percent_deposit * array_year[temp_month] /
                     temp_number_days_year) /
                    100;
  }

  return percent_month;
}

// вычисление начисленных процентов, если в чекбоксе месяц и капитализация
double CalculateDeposit::CalculatAccruedInterestForMonthWithCapitaliz(
    int const &temp_year, int const &temp_month, double const &deposit_amount,
    double const &percent_deposit) {
  int const array_year[13] = {0,  31, 28, 31, 30, 31, 30,
                              31, 31, 30, 31, 30, 31};
  double all_amount;
  double percent_month;
  int temp_number_days_year = 365;
  CheckingForLeapYear(temp_year, temp_number_days_year);

  if (temp_month == 2 &&
      CheckingForLeapYear(temp_year, temp_number_days_year)) {
    all_amount = deposit_amount *
                 (1 + (percent_deposit * 29) / (100 * temp_number_days_year));
  } else {
    all_amount =
        deposit_amount * (1 + (percent_deposit * array_year[temp_month]) /
                                  (100 * temp_number_days_year));
  }

  percent_month = all_amount - deposit_amount;
  return percent_month;
}

// вычисления для "дней" в таблицу без капитализации
double CalculateDeposit::CalculationByDays(int const &current_year,
                                           double const &percent_deposit,
                                           double const &deposit_amount) {
  int number_days_year;
  double result_amount;
  double percent_month;
  CheckingForLeapYear(current_year, number_days_year);
  result_amount =
      deposit_amount * (1 + (percent_deposit * 1) / (100 * number_days_year));
  percent_month = result_amount - deposit_amount;
  return percent_month;
}

// вычисления для "лет" без капитализации
double CalculateDeposit::CalculatForYears(int const &current_year,
                                          double const &percent_deposit,
                                          double const &deposit_amount) {
  int temp_number_days_year;
  double percent_year;

  CheckingForLeapYear(current_year, temp_number_days_year);
  percent_year = (deposit_amount * percent_deposit * temp_number_days_year /
                  temp_number_days_year) /
                 100;

  return percent_year;
}

// вычисления для "дней" без капитализации
double CalculateDeposit::CalculatForDayWithoutCapitalization(
    int const &placement_period, int const &deposit_year,
    double const &deposit_amount, double const &percent_deposit) {
  int temp_year = deposit_year;
  int number_days_year;
  double percent_month = 0;

  CheckingForLeapYear(temp_year, number_days_year);
  percent_month =
      (deposit_amount * percent_deposit * placement_period / number_days_year) /
      100;

  return percent_month;
}

}  // namespace my
