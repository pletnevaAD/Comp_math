#include "D:\вычмат 4 сем\software\software\FORSYTHE.H"
#include <iostream>
#include <iomanip>

const int n = 11;
double lagranzh(double x[], double f[], double x0);
double integralFunm1(double t);
double integralFunm2(double t);

int main() {
  double x[n];
  double f[n];

  for (size_t i = 0; i < n; i++)
  {
    x[i] = 0.3 * i;
    f[i] = 1 - exp(-x[i]);
  }

  std::cout << "Table function:\n";
  std::cout << "x\tf(x)\n";
  for (size_t i = 0; i < n; i++)
  {
    std::cout << x[i] << "\t" << f[i] << "\n";
  }

  double y[10];
  for (size_t i = 0; i < 10; i++)
  {
    y[i] = 0.15 + 0.3 * i;
  }

  std::cout << std::left << std::setw(22) << "f(x)" << std::setw(22) << "L(x)" << std::setw(22) << "S(x)" << std::setw(22)
    << "|L(x)-f(x)|" << std::setw(22) << "|S(x)-f(x)|" << "\n";
  for (size_t i = 0; i < 10; i++)
  {
    double func = 1 - exp(-y[i]);
    double l = lagranzh(x, f, y[i]);
    double seval = SPLINE(11, x, f).Eval(y[i]);
    std::cout << std::left << std::setw(22) << std::setprecision(12) << func << std::setw(22) << std::setprecision(12) << l
      << std::setw(22) << std::setprecision(12) << seval << std::setw(22) << std::setprecision(12) << abs(l - func)
      << std::setw(22) << std::setprecision(12) << abs(seval - func) << "\n";
  }

  double resultFunm1;
  double errestFunm1;
  int nofunm1;
  double flagFunm1;
  QUANC8(integralFunm1, 0.5, 1.0, 1e-9, 1e-9, resultFunm1, errestFunm1, nofunm1, flagFunm1);

  std::cout << "\nThe result of calculating the integral of integralFunm1(m=-1) by QUANC8: " << "\nresult = " << resultFunm1 << " errest = " << errestFunm1
    << " nofun = " << nofunm1 << " flag = " << flagFunm1 << "\n";
  std::cout << "nofunm1 * errestFunm1 /resultFunm1 = "<<nofunm1 * errestFunm1 /resultFunm1<<"\n";
 
  double resultFunm2;
  double errestFunm2;
  int nofunm2;
  double flagFunm2;
  QUANC8(integralFunm2, 0.5, 1.0, 1e-12, 1e-12, resultFunm2, errestFunm2, nofunm2, flagFunm2);

  std::cout << "\nThe result of calculating the integral of integralFunm2(m=-0,5) by QUANC8: " << "\nresult = " << resultFunm2 << " errest = " << errestFunm2
    << " nofun = " << nofunm2 << " flag = " << flagFunm2 << "\n";
  std::cout << "nofunm2 * errestFunm2 /resultFunm2 = " << nofunm2 * errestFunm2 / resultFunm2 << "\n";
}

double lagranzh(double x[], double f[], double x0)
{
  double result = 0;
  double prod;
  for (int j = 0; j < n; j++) {
    prod = 1;
    for (int i = 0; i < n; i++) {
      if (i != j) {
        prod = prod * (x0 - x[i]) / (x[j] - x[i]);
      }
    }
    result = result + f[j] * prod;
  }
  return result;
}

double integralFunm1(double t)
{
  double result = 1 / (abs(sin(t) - 0.6));
  return result;
}

double integralFunm2(double t)
{
  double result = 1 / (abs(sin(t) - 0.6));
  return sqrt(result);
}
