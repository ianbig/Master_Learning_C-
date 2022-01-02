#include <stdio.h>
#include <stdlib.h>

#define RETIRE 0
#define WORK 1

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double computeBalance(double balance, double rate, double income) {
  double rate_earn = balance * rate;
  double new_balance = balance + rate_earn + income;

  return new_balance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  int i = 0;
  int currentAge = startAge;

  for (i = 0; i < working.months; i++) {
    int ageYears = currentAge / 12;
    int ageMonths = currentAge % 12;

    printf("Age %3d month %2d you have $%.2lf\n", ageYears, ageMonths, balance);

    balance = computeBalance(balance, working.rate_of_return / 12, working.contribution);

    currentAge += 1;
  }

  for (i = 0; i < retired.months; i++) {
    int ageYears = currentAge / 12;
    int ageMonths = currentAge % 12;

    printf("Age %3d month %2d you have $%.2lf\n", ageYears, ageMonths, balance);

    balance = computeBalance(balance, retired.rate_of_return / 12, retired.contribution);

    currentAge += 1;
  }
}

int main() {
  retire_info working, retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;

  double balance = 21345.00;
  int startAges = 327;

  retirement(startAges, balance, working, retired);

  return 0;
}
