import matplotlib.pyplot as plt
import numpy as np

# Computing Factorial
def compute_factorial(x): 
        S = 1
        for i in range(x, 0, -1):
                S = S * i
        return S

# compute exponent
def compute_exponent(x):
        e = 2.7182818284590451
        x0 = int(round(x))
        z = x - x0

        exp = e ** x0 * ( 1 + z + (z ** 2)/ compute_factorial(2) + (z ** 3)/compute_factorial(3) + (z ** 4)/compute_factorial(4) + (z ** 5)/compute_factorial(5) + (z ** 6 ) / compute_factorial(6) + (z**7)/compute_factorial(7) + (z**8)/compute_factorial(8) + (z**9)/compute_factorial(9) + (z**10)/compute_factorial(10) + (z**11)/compute_factorial(11) + (z**12)/compute_factorial(12) + (z**13)/compute_factorial(13) + (z**14)/compute_factorial(14) + (z**15)/compute_factorial(15))
        return exp

# copmpute natural logarithm
def compute_natural_log(x):
        s = x
        i = 0
        diff = 1
        f =  lambda s, x: compute_exponent(s) - x
        f_prime = lambda s: compute_exponent(s)

        s_1 = s #inital guess
        while i < 200  and  diff> 10e-14:
                s_2 = s_1 - f(s_1, x)/f_prime(s_1)
                diff = abs(s_2 - s_1)
                s_1 = s_2
                i = i + 1
        return s_2

# compute absolute value
def compute_absolute_value(x):
        if x < 0:
                x = -x
                return x
        else:
                return x

# let f(t) = dP/dt = rP(1 - P/K)
def function(r, P, K, t):
        dP_dt = r * P * (1 - P/K)
        return dP_dt

# Closed form solution
def solution(K, P0, r, t):
        sol = K/(1 + ((K - P0)/P0) * compute_exponent(-r * t))
        return sol

# Question No. 1: Evaluate P(t) for a list of time values
def evaluate_P(r, K, P0, t):
        # here t is an array
        for i in range(len(t)):
            print(f"For t = {t[i]}, P(t) = {solution(K, P0, r, t[i])}")

# Question No.2 : Implement Forward Euler Method
def forward_euler(r, K, P0, t):
    N = 50 # Number of steps
    h = t / N  
    y_old = P0  
    t_current = 0  
    
    # Loop through N steps
    for i in range(N):
        y_new = y_old + h * function(r, y_old, K, t_current)
        y_old = y_new
        t_current += h

    return y_new

# Question No.2, Print numerical versus closed form solution
def numerical_versus_closed_form(r, K, P0, t):
        for i in range(len(t)):
                numerical_solution = forward_euler(r, K, P0, t[i])
                analytical_solution = solution(K, P0, r, t[i])
                print(f"At time {t[i]}, closed-form solution : {analytical_solution}, numerical solution: {numerical_solution}")

# Question No. 3: To find the time when population hits K/2

# From Closed Form Solution(cfs)
def find_time_from_cfs(r, K, P, P0): #time to reach population P
       return compute_natural_log(((K/P)-1)*(P0/(K-P0))) / (-r)

# Using Forward Euler
def find_time(r, K, P0, t_end):
    N = 10000
    h = t_end/N
    c = 4

    P_old = P0
    t_current = 0

    for i in range(N):
            P_new = P_old + h * function(r, P_old, K, t_current)
            t_current = t_current + h

            if compute_absolute_value(P_new - (K/2)) <= c*h:
                    return P_new, t_current
            P_old = P_new

    # If not reached within time
    print("Warning: P did not reach K/2 in given time.")
    return 0, 0

# Print results for q.No.3
def print_results_problem_3(r, K, P0, t):
       half = K/2
       closed_form_solution = find_time_from_cfs(r, K, half, P0) # closed form solution for time to reach half of the population
       pop_numerical, time_numerical = find_time(r,K,P0,t) # Numerical solution

       print(f"Time to reach population K/2({K/2}), closed form solution:{closed_form_solution}, Numerical Solution : {time_numerical} ") 

# Plot Numerical Solution Versus Closed Form Solution (versus time)

def plot_numerical_versus_cfs(r,K,P0):
    t = np.linspace(0,20,200) # creates 200 time points from 0 to 20 for plotting
    numerical_solution = np.zeros(len(t)) # makes array of size as array t
    analytical_solution = np.zeros(len(t)) 

    for i in range(len(t)):
            numerical_solution[i] = forward_euler(r, K, P0, t[i])
            analytical_solution[i] = solution(K, P0, r, t[i])
    
    plt.plot(t, numerical_solution, color = 'blue', label = 'numerical')
    plt.plot(t, analytical_solution, color = 'red', label = 'analytical', linestyle = "--")

    plt.title("Numerical Solution Versus Closed Form Solution")
    plt.xlabel("time   (t)")
    plt.ylabel("Population  (P(t))")

    plt.legend()
    plt.show()

# Plot Error versus timestep (to demostrate how error accumulates over time)
def plot_error_versus_timestep(r,K,P0,t): # Here t is the time at we we want to evaluate our solution
    time_steps = np.linspace(0, t, 200)
    error = np.zeros(len(time_steps))
    for i in range(len(time_steps)):
            analytical_solution = solution(K, P0, r, time_steps[i])
            numerical_solution = forward_euler(r, K, P0, time_steps[i])
            error[i] = compute_absolute_value(analytical_solution - numerical_solution)
    plt.plot(time_steps, error, color = 'Green')
    plt.title("Global Error Versus Time")
    plt.xlabel("time  (t)")
    plt.ylabel("Error  |P_analytical - y_n_numerical|")
    plt.show()
        
              

r = 0.5
K = 100
P0 = 10
t0 = 0
t_end = 20
t = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20]

print("\n Question No. 1\n")
evaluate_P(r, K, P0, t)

print("\n Question No. 2 \n")
numerical_versus_closed_form(r, K, P0, t)

print("\n Question No. 3 \n")
print_results_problem_3(r, K, P0, t_end)
print("\n")

plot_numerical_versus_cfs(r, K, P0)
plot_error_versus_timestep(r,K,P0,t_end)



        
        