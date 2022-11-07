import math
from scipy import integrate
from scipy.optimize import brentq
import numpy
import matplotlib.pyplot as plt


def a(x):
    return 0.8476479 * math.exp(-5 * x ** 3 + x + 0.5)


def fun_for_b(x):
    return x - 1.4 ** x


def b(x):
    return (x - 4.4102905) ** 4


def fun(t, u, e, delta):
    return [u[1], (-1) * (delta + e * math.cos(2 * t)) * u[0]]


A, err = integrate.quad(a, 0, 1)
print("Коэффициент А (U(0)=A): ", A)
print("Погрешность вычисления А: ", err)
xForB = brentq(fun_for_b, 4.4, 4.5, xtol=1.e-8, rtol=1.e-8)
print("x* = ", xForB)
print("Погрешность вычисления х*: 0.00000001")
B = b(xForB)
print("Коэффициент B (U'(0)=B): ", B)
t_val = numpy.linspace(0, 20, 41)
t_val2 = numpy.linspace(0, 80, 161)

solve = integrate.solve_ivp(fun, [0, 20], [A, B], t_eval=t_val, rtol=1.e-8, atol=1.e-8, args=(0.5, 1))
solve_2 = integrate.solve_ivp(fun, [0, 80], [A, B], t_eval=t_val2, rtol=1.e-8, atol=1.e-8, args=(0.1, 0.1))
solve_5 = integrate.solve_ivp(fun, [0, 80], [A * 1.05, B * 1.05], t_eval=t_val2, rtol=1.e-8, atol=1.e-8, args=(0.1, 0.1))
print("Значения U при Т от 0 до 20 с шагом 0,5: ", solve.y[0])
print("Значения U при Т от 0 до 80 с тем же шагом с е=0.1 и delta=0.1: ", solve_2.y[0])
print("Погрешность RKF45: 0.00000001")

solve_3 = integrate.solve_ivp(fun, [0, 20], [A * 1.1, B], t_eval=t_val, rtol=1.e-8, atol=1.e-8, args=(0.5, 1))
print("Погрешность при увеличении А на 10%", solve_3.y[0] - solve.y[0])

solve_4 = integrate.solve_ivp(fun, [0, 20], [A, B * 1.1], t_eval=t_val, rtol=1.e-8, atol=1.e-8, args=(0.5, 1))
print("Погрешность при увеличении В на 10%", solve_4.y[0] - solve.y[0])

fig, axes = plt.subplots(2, 2, figsize=(20, 15))
axes[0, 0].plot(solve.t, solve.y[0])
axes[0, 0].set_title("U(t)")
axes[0, 0].set_xlabel('t')
axes[0, 0].legend('U', shadow=True)
axes[0, 1].plot(solve_2.t, solve_2.y[0], solve_5.t, solve_5.y[0])
axes[0, 1].set_title("Влияние изменения н.у. на решение")
axes[0, 1].set_xlabel('t')
axes[0, 1].legend(['solve2', 'solve3'], shadow=True)

axes[1, 0].plot(solve.t, solve.y[0], solve_3.t, solve_3.y[0])
axes[1, 0].set_title("Влияние изменения А на решение")
axes[1, 0].set_xlabel('t')
axes[1, 0].legend(['solve', 'solve3'], shadow=True)

axes[1, 1].plot(solve.t, solve.y[0], solve_4.t, solve_4.y[0])
axes[1, 1].set_title("Влияние изменения В на решение")
axes[1, 1].set_xlabel('t')
axes[1, 1].legend(['solve', 'solve4'], shadow=True)
plt.show()
