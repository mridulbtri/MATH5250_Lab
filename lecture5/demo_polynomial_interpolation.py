import numpy as np

def analytical_solution(x):
    return (np.cos(x))

def numerical_solution(coeff,x):
    a,b,c,d = coeff[0], coeff[1], coeff[2], coeff[3]
    return a*(x**3) + b*(x**2) + c*x + d

def setup_linear_system(x):
    
    # Define function
    f = lambda x: analytical_solution(x)

    ones = np.ones_like(x)
    A = np.column_stack((x**3, x**2, x, ones))
    b = f(x)
    return A, b

def gauss_elimination(A, b):

    for j in range(len(A)):
        for i in range(j+1, len(A)):
            factor = A[i, j]/A[j, j]
            A[i, :] = A[i, :] - factor * A[j, :]
            b[i] = b[i] -  factor * b[j]

    return A, b 

def backward_substitution(A, b):
    n = len(b)
    x = np.zeros(n, dtype = np.float64)  # Initialize solution array
    
    # Starting from the last equation and working backwards
    for i in range(n-1, -1, -1):
        x[i] = b[i]
        for j in range(i+1, n):
            x[i] -= A[i, j] * x[j]
        x[i] /= A[i, i]
    
    return x

def compute_max_error(numerical_solution, analytical_solution):
    error = np.abs(numerical_solution - analytical_solution)
    max_error = np.max(error)

    print("\n\nThe analytical solution is ", analytical_solution)
    print("\n\nThe numerical solution is ", numerical_solution)
    print("\n\nThe errors at four points are ", error)
    print("\n\nThe maximum error is", max_error)


# RUN
x = np.array([-0.1, -0.02, 0.02, 0.1], dtype = np.float64)
A, b = setup_linear_system(x)

# Gauss elimination
A_gauss, b_gauss = gauss_elimination(A,b)
coefficients = backward_substitution(A_gauss, b_gauss)
print("\n\nThe values of a, b, c, d are ", coefficients)


# Compute maximum error
analytical_soln = analytical_solution(x)
numerical_soln = numerical_solution(coefficients, x)
compute_max_error(numerical_soln, analytical_soln)


    

