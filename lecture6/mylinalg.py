import numpy as np
import matplotlib.pyplot as plt


def gauss_elimination(A, b):

    for j in range(len(A)):
        # Find maximum absolute value in column j (from row j onwards)
        max_abs_index = j + np.argmax(np.abs(A[j:, j]))
        
        # Swap only if the max is not already at position j
        if max_abs_index != j:
            temp_storage_A = A[j, :].copy()
            temp_storage_b = b[j]
            A[j, :], b[j] = A[max_abs_index, :], b[max_abs_index]
            A[max_abs_index, :], b[max_abs_index] = temp_storage_A, temp_storage_b
        
        for i in range(j+1, len(A)):
            factor = A[i, j]/A[j, j]
            A[i, :] = A[i, :] - factor * A[j, :]
            b[i] = b[i] - factor * b[j]
    
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

def LeastSquareApprox(x, f, n):

    """
    Finds the least square approximation of data {x, f} by a polynomial 
    of degree <= n.
    
    The least squares problem minimizes ||Xa - f||^2 where X is the 
    Vandermonde matrix with columns [1, x, x^2, ..., x^n] and a are 
    the polynomial coefficients.
    
    This is solved by solving the normal equations: X^T X a = X^T f
    This can be written as : Aa = b ( where A = X^T X; b = X^T f)
    """
    # Build the Vandermonde matrix A with columns [1, x, x^2, ..., x^n]
    X = np.column_stack([x**i for i in range(n+1)])
    
    # Compute Product of X and f with transpose of X 
    A = X.T @ X
    b = X.T @ f
    
    # Solve using Gaussian elimination and backward substitution
    A_upper, b_modified = gauss_elimination(A, b) # Upper triangular matrix
    coeff = backward_substitution(A_upper, b_modified)
    
    return coeff

def analytical_solution(x):
    return np.cos(x)

def evaluate_polynomial(coeff, x_i):

    result = np.zeros_like(x_i, dtype = np.float64)

    for i in range(len(coeff)):
        result = result + coeff[i] * (x_i ** i)
    
    return result 


def plot_solution_and_error(x_i, n):

    # create data points to plot
    x_i = np.linspace(-np.pi, np.pi, 51)
    # Compute analytical solution at these data points 
    f_i = analytical_solution(x_i)

    # coefficients of the fitted polynomial
    coeff = LeastSquareApprox(x_i, f_i, n)

    # print results 
    print("\n============================================\n")
    print(f"FITTING {n}-DEGREE POLYNOMIAL\n")
    print(f"c_0, c_1, c_2, ... ..., c_{n}:", coeff, "\n")

    # Evaluate polynomial at the data points
    p_i = evaluate_polynomial(coeff, x_i)
    
    # Compute errors
    errors = np.abs(p_i - f_i)
    
    print(f"\n" + "=" * 20, "\n")
    print("ERROR")
    print(f"Maximum error: {np.max(errors):.6e}")
    print(f"Min error:     {np.min(errors):.6e}")
    print(f"Mean error:    {np.mean(errors):.6e}")
    
    
    # Visualize the approximation 

    plt.figure(figsize=(12, 5))
    
    # Numerical versus analytical solution
    plt.subplot(1, 2, 1)
    plt.plot(x_i, f_i, 'b-', linewidth=2, label='cos(x) (analytical)')
    plt.plot(x_i, p_i, 'r--', linewidth=2, label=f'Degree-{n} polynomial')
    plt.scatter(x_i, f_i, alpha=0.5, s=20, label='Data points', color='blue')
    plt.scatter(x_i, p_i, alpha=0.5, s=20, label='Data points', color='red')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title(f'Least Square Approximation using degree-{n} polynomial')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xlim(-np.pi, np.pi)
    
    # Error
    plt.subplot(1, 2, 2)
    plt.plot(x_i, f_i - p_i, 'purple', linewidth=2, label='Error')
    plt.axhline(y=0, color='k', linestyle='-', linewidth=0.5)
    plt.scatter(x_i, f_i - p_i, alpha=0.5, s=20, color='orange')
    plt.xlabel('x')
    plt.ylabel('Error: cos(x) - p(x)')
    plt.title('Approximation Error')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xlim(-np.pi, np.pi)
    plt.tight_layout()
    plt.show()

# Run
def main():
    x_i = np.linspace(-np.pi, np.pi, 51)
    n = 2
    plot_solution_and_error(x_i, n)

if __name__ == main():
    main()