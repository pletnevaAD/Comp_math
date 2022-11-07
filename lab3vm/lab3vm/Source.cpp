#include "C:\Users\dimed\Downloads\software\FORSYTHE.H"
#include <iostream>
#include <iomanip>

void fun(REAL T, REAL* X, REAL* dX);
void rkf2(void(F)(REAL T, REAL* Y, REAL* YP), REAL* Y, REAL& T, REAL H);

int main() {
  REAL t = 0.0;
  REAL tout = 0.0;
  REAL x[2] = { 1, 0 };
  REAL relerr = 1.E-8;
  REAL abserr = 0.0001;
  double work[3 + 6 * 2];
  int flag = 1;
  REAL X_0[21];
  REAL X_1[21];
  std::cout << "RKF45" << "\n";
  for (int i = 0; i < 21; i++) {
    RKF45(fun, 2, x, t, tout, relerr, abserr, work, flag);
    std::cout << std::left << "tout = " << std::setw(6) << tout << " x[0] = " << std::setw(12) << x[0] << " x[1] = " << std::setw(10) << x[1] << "\n";
    tout += 0.1;
    X_0[i] = x[0];
    X_1[i] = x[1];
    flag = 1;
  }
  t = 0.0;
  REAL x2[2] = { 1, 0 };
  REAL H = 0.1;
  std::cout << "RKF2: h=0.1" << "\n";
  for (int i = 0; i <= (2 / H); i++) {
    std::cout << std::left << "T = " << std::setw(6) << t;
    rkf2(fun, x2, t, H);
    std::cout << std::left << " x[0] = " << std::setw(12) << x2[0] << " x[1] = " << std::setw(12) << x2[1] << "result rkf45 - result rkf2:   " << "dx[0] = "
      << std::setw(12) << std::setprecision(4) << X_0[i] - x2[0] << "dx[1] = " << std::setw(12) << std::setprecision(4) << X_1[i] - x2[1] << "\n";
  }
  t = 0.0;
  REAL x1[2] = { 1, 0 };
  H = 0.01;
  std::cout << "RKF2: h=0.01" << "\n";
  for (int i = 0; i <= (2 / H); i++) {
    if (i % 10 == 0)
      std::cout << std::left << "T = " << std::setw(6) << t;
    rkf2(fun, x1, t, H);
    if (i % 10 == 0)
      std::cout << std::left << " x[0] = " << std::setw(12) << x1[0] << " x[1] = " << std::setw(12) << x1[1] << "result rkf45 - result rkf2:   " << "dx[0] = "
      << std::setw(12) << std::setprecision(4) << X_0[i / 10] - x1[0] << "dx[1] = " << std::setw(12) << std::setprecision(4) << X_1[i / 10] - x1[1] << "\n";
  }
}

void fun(REAL T, REAL* X, REAL* dX)
{
  dX[0] = -4 * X[0] + 23 * X[1] + exp(-T);
  dX[1] = 4 * X[0] - 48 * X[1] + sin(T);
}

void rkf2(void(F)(REAL T, REAL* Y, REAL* YP), REAL* Y, REAL& T, REAL H)
{
  REAL result1[2];
  fun(T, Y, result1);
  REAL Z23[2];
  Z23[0] = Y[0] + (2 * H / 3) * result1[0];
  Z23[1] = Y[1] + (2 * H / 3) * result1[1];
  REAL result2[2];
  T += H;
  fun(T, Z23, result2);
  REAL Z1[2];
  Z1[0] = Y[0] + H / 4 * (result1[0] + 3 * result2[0]);
  Z1[1] = Y[1] + H / 4 * (result1[1] + 3 * result2[1]);
  Y[0] = Z1[0];
  Y[1] = Z1[1];
}
