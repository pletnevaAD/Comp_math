import numpy as np
from scipy.linalg import lu_factor, lu_solve, norm

for j in range(3):
    N = 3 * (j + 1)
    print("Matrix ", N, "*", N)
    B = np.empty([N, N])
    for i in range(N):
        for k in range(N):
            if i < k:
                B[i][k] = 0
            elif i > k:
                B[i][k] = i * (N - k)
            else:
                res = (N - i + k) * (i + 1)
                B[i][k] = 0.01 / res
    for i in range(N):
        for k in range(N):
            print("{0:.3e}".format(B[i][k]).ljust(9), end=' ')
        print(" ")
    E = np.eye(N)
    lu, piv = lu_factor(B)
    X = []
    for i in range(0, N):
        x = lu_solve((lu, piv), E[i])
        X.append(list(x))
    print(" ")
    invB = np.matrix.transpose(np.matrix(X))
    print("Матрица невязки")
    np.set_printoptions(precision=3)
    R = B.dot(invB) - E
    print(R)
    print("Норма матрицы R=B*B^(-1)-E: ", format(norm(R, "fro"), '.4e'))
    print("Число обусловленности матрицы В: ", format(np.linalg.cond(B, "fro"), '.4e'), "\n")