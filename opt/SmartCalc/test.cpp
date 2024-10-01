#include <gtest/gtest.h>

#include <iomanip>

#include "CalcWrapper/CalcWrapper/Model/rpn.h"

using namespace std;

// ************************ Test correct ************************
TEST(Copy, test_1) {
  my::ModelCalc obj;
  double result = 124.86638314531139;
  ASSERT_DOUBLE_EQ(result, obj.Calc("123-sin(4)*ln(13)-cos(15+225)/ln(78)", 0));
}

TEST(Copy, test_2) {
  my::ModelCalc obj;
  double result = 123.76825817990353;
  ASSERT_DOUBLE_EQ(result,
                   obj.Calc("123-sin(4)*log(13)-cos(15+225)/ln(78)", 0));
}

TEST(Copy, test_3) {
  my::ModelCalc obj;
  double result = 71.029115591698442;
  ASSERT_DOUBLE_EQ(result, obj.Calc("sqrt(5+(atan(-5+3)))*6^2", 0));
}

TEST(Copy, test_4) {
  my::ModelCalc obj;
  double result = 91.403435201274476;
  ASSERT_DOUBLE_EQ(result, obj.Calc("sqrt(5+(atan(5+3)))*6^2", 0));
}

TEST(Copy, test_5) {
  my::ModelCalc obj;
  double result = -1.8003964193342079;
  ASSERT_DOUBLE_EQ(result,
                   obj.Calc("asin(0.3)-acos(0.3)*tan(0.3/atan(0.3))", 0));
}

TEST(Copy, test_6) {
  my::ModelCalc obj;
  double result = -8.2362772590068225;
  ASSERT_DOUBLE_EQ(
      result, obj.Calc("tan(acos(0.166231))/"
                       "sin(log(atan(0.166231)))+cos(sqrt(2.12321-0.166231))",
                       0));
}

TEST(Copy, test_7) {
  my::ModelCalc obj;
  double result = 72.029115591698442;
  ASSERT_DOUBLE_EQ(result, obj.Calc("sqrt(5+(atan(-5+3)))*6^2+5mod2", 0));
}

TEST(Copy, test_8) {
  my::ModelCalc obj;
  double result = -0.99735176906234413;
  ASSERT_DOUBLE_EQ(result, obj.Calc("cos(sin(8)+ln(8))", 0));
}

TEST(Copy, test_9) {
  my::ModelCalc obj;
  double result = -115.0;
  ASSERT_DOUBLE_EQ(result, obj.Calc("(-1)+(-2)*3/4^(-2)+6*(-3)", 0));
}

TEST(Copy, test_10) {
  my::ModelCalc obj;
  double result = -71.1876543209876543;
  ASSERT_DOUBLE_EQ(result, obj.Calc("9^(-2)+4/5-(-36)*(-2)", 0));
}

TEST(Copy, test_11) {
  my::ModelCalc obj;
  double result = 3.6116666666666664;
  ASSERT_DOUBLE_EQ(
      result,
      obj.Calc("(-2-(-5)^(-2)+4^(-3)*56)/3+5*(2+(-4))/(-5)+sqrt(4)", 0));
}

TEST(Copy, test_12) {
  my::ModelCalc obj;
  double result = 1808.5;
  ASSERT_DOUBLE_EQ(result, obj.Calc("(-4+sqrt(9)*(-3))/2+(-34)+(-2+45)^2", 0));
}

TEST(Copy, test_13) {
  my::ModelCalc obj;
  double result = -30.07216494845361;
  ASSERT_DOUBLE_EQ(
      result,
      obj.Calc("15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
               "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))",
               0));
}

TEST(Copy, test_14) {
  my::ModelCalc obj;
  double result = -2.3325660514880582;
  ASSERT_DOUBLE_EQ(
      result,
      obj.Calc("cos(6^4)/sqrt(4)+(36+23)mod(3*2)-tan(ln(24)+log(25mod34))", 0));
}

TEST(Copy, test_15) {
  my::ModelCalc obj;
  double result = 48.625;
  ASSERT_DOUBLE_EQ(
      result,
      obj.Calc("2+2+(2)+(-2)+(-2)+2*2*(2)*(-2)*(-2)-2/2/(2)/(-2)/"
               "(-2)+2^2+(2)^(2)+(-2)^(-2)+(-2)^2+(-2)^(-2)+2^(-2)+sqrt(4)",
               0));
}

TEST(Copy, test_16) {
  my::ModelCalc obj;
  double result = 0.3170580303842070;
  ASSERT_DOUBLE_EQ(result, obj.Calc("2mod(sin1)", 0));
}

TEST(Copy, test_17) {
  my::ModelCalc obj;
  double result = 45.3450040166407691;
  ASSERT_DOUBLE_EQ(
      result,
      obj.Calc("45.345+5342*345345.2324234/(12312.456456+21431234^2)", 0));
}

// ************************ Test X ************************

TEST(TestX, test_1) {
  my::ModelCalc obj;
  double result = 4;
  ASSERT_DOUBLE_EQ(result, obj.Calc("2+x", 2));
}

TEST(TestX, test_2) {
  my::ModelCalc obj;
  double result = 392;
  ASSERT_DOUBLE_EQ(result, obj.Calc("1565146modx", 542));
}

TEST(TestX, test_3) {
  my::ModelCalc obj;
  double result = 67.03540902830543;
  ASSERT_DOUBLE_EQ(result, obj.Calc("1565146modx*tan(0.7)/5+1", 542));
}

// ************************ Test Ex ************************

TEST(TestEx, test_1) {
  my::ModelCalc obj;
  double result = 10455;
  ASSERT_DOUBLE_EQ(result, obj.Calc("1.0454e+4+1", 0));
}

TEST(TestEx, test_2) {
  my::ModelCalc obj;
  double result = 1.00010454;
  ASSERT_DOUBLE_EQ(result, obj.Calc("1.0454e-4+1", 0));
}

// ************************ Test Incorrect ************************

TEST(TestIncorrect, test_1) {
  my::ModelCalc obj;
  std::string result = "The operator was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr("1++2"));
}

TEST(TestIncorrect, test_2) {
  my::ModelCalc obj;
  std::string result = "The operator was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr("/2"));
}

TEST(TestIncorrect, test_3) {
  my::ModelCalc obj;
  std::string result = "The operator was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr("1++d"));
}

TEST(TestIncorrect, test_4) {
  my::ModelCalc obj;
  std::string result = "The bracket and operators was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr("(1)1+1"));
}

TEST(TestIncorrect, test_5) {
  my::ModelCalc obj;
  std::string result = "The operator was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr("1+.(1)"));
}

// zero
TEST(TestIncorrect, test_6) {
  my::ModelCalc obj;
  std::string result = "It is not desirable to divide by zero :)";
  ASSERT_EQ(result, obj.CheckInputStr("2/0"));
}

// dot
TEST(TestIncorrect, test_7) {
  my::ModelCalc obj;
  std::string result = "The point was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr(".("));
}

TEST(TestIncorrect, test_8) {
  my::ModelCalc obj;
  std::string result = "The point was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr("1."));
}

// trigonometric

// asin acos atan
TEST(TestIncorrect, test_9) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("asib"));
}

TEST(TestIncorrect, test_10) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("acod"));
}

TEST(TestIncorrect, test_11) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("atay"));
}

TEST(TestIncorrect, test_12) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("ason"));
}

TEST(TestIncorrect, test_13) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("acis"));
}

TEST(TestIncorrect, test_14) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("atog"));
}

TEST(TestIncorrect, test_15) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("adin"));
}

TEST(TestIncorrect, test_16) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("azis"));
}

TEST(TestIncorrect, test_17) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("arog"));
}

// sin
TEST(TestIncorrect, test_18) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("sif"));
}

TEST(TestIncorrect, test_19) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("son"));
}

// sqrt
TEST(TestIncorrect, test_20) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("sqrw"));
}

TEST(TestIncorrect, test_21) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("squt"));
}

TEST(TestIncorrect, test_22) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("sirt"));
}

// cos
TEST(TestIncorrect, test_23) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("coa"));
}

TEST(TestIncorrect, test_24) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("cis"));
}

// ln
TEST(TestIncorrect, test_25) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("lk"));
}

// tan
TEST(TestIncorrect, test_26) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("tas"));
}

TEST(TestIncorrect, test_27) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("ten"));
}

// mod
TEST(TestIncorrect, test_28) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("mow"));
}

// log
TEST(TestIncorrect, test_29) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("lok"));
}

TEST(TestIncorrect, test_30) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("mid"));
}

TEST(TestIncorrect, test_31) {
  my::ModelCalc obj;
  std::string result = "The trigonometric function is incorrectly entered!";
  ASSERT_EQ(result, obj.CheckInputStr("or"));
}

// bracket
TEST(TestIncorrect, test_32) {
  my::ModelCalc obj;
  std::string result = "The bracket was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr("(1+2"));
}

TEST(TestIncorrect, test_33) {
  my::ModelCalc obj;
  std::string result = "The bracket was entered incorrectly!";
  ASSERT_EQ(result, obj.CheckInputStr("1+1(1)"));
}

// ************************ Test Deposit ************************

// Раз в месяц

TEST(TestDeposit, test_1) {
  my::ModelCalc obj;
  double result = 575.34246575342468;
  double deposit = 100000;
  double deposit_result =
      obj.CalculatAccruedInterestForMonthWithoutCapitaliz(2022, 11, deposit, 7);
  ASSERT_DOUBLE_EQ(result, deposit_result);
}

TEST(TestDeposit, test_2) {
  my::ModelCalc obj;
  double result = 554.64480874316939;
  double deposit = 100000;
  double deposit_result =
      obj.CalculatAccruedInterestForMonthWithoutCapitaliz(2024, 02, deposit, 7);
  ASSERT_DOUBLE_EQ(result, deposit_result);
}

TEST(TestDeposit, test_3) {
  my::ModelCalc obj;
  double result = 594.5205479451979;
  double deposit = 100000;
  double deposit_result =
      obj.CalculatAccruedInterestForMonthWithCapitaliz(2022, 01, deposit, 7);
  ASSERT_DOUBLE_EQ(result, deposit_result);
}

TEST(TestDeposit, test_4) {
  my::ModelCalc obj;
  double result = 554.64480874316359;
  double deposit = 100000;
  double deposit_result =
      obj.CalculatAccruedInterestForMonthWithCapitaliz(2024, 02, deposit, 7);
  ASSERT_DOUBLE_EQ(result, deposit_result);
}

// Раз в день + капитализация

TEST(TestDeposit, test_5) {
  my::ModelCalc obj;
  double result = 19.125683060105075;
  double deposit = 100000;
  double deposit_result = obj.CalculationByDaysCapital(2000, 7, deposit);
  ASSERT_DOUBLE_EQ(result, deposit_result);
}

TEST(TestDeposit, test_6) {
  my::ModelCalc obj;
  double result = 19.17808219177823;
  double deposit = 100000;
  double deposit_result = obj.CalculationByDays(2022, 7, deposit);
  ASSERT_DOUBLE_EQ(result, deposit_result);
}

// tax
TEST(TestDeposit, test_7) {
  my::ModelCalc obj;
  double result = 665;
  double deposit_result = obj.CalculateTax(7, 52000);
  ASSERT_DOUBLE_EQ(result, deposit_result);
}

// високосный
TEST(TestDeposit, test_8) {
  my::ModelCalc obj;
  int number_days_in_year;
  obj.CheckingForLeapYear(2021, number_days_in_year);
  ASSERT_DOUBLE_EQ(365, number_days_in_year);
}

// ************************ Test Credit ************************

TEST(TestCredit, test_1) {
  my::ModelCalc obj;
  double result = 1043861.149025064;
  double credit = 1000000;
  double month_pay;
  double accrued_inter;
  double all_credit;
  obj.CalcCredit(credit, 8, 12, month_pay, accrued_inter, all_credit);
  ASSERT_DOUBLE_EQ(result, all_credit);
}

TEST(TestCredit, test_2) {
  my::ModelCalc obj;
  double result = 5050;
  double credit = 10000;
  double month_pay = obj.CalcCreditDif(credit, 2, 12, 1);
  ASSERT_DOUBLE_EQ(result, month_pay);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
