import matplotlib.pyplot as plt

# Read the data
x = []
y = []

with open('out1.txt', 'r') as file:
    for line in file:
        values = line.split()
        x.append(float(values[0]))
        y.append(float(values[1]))

# Plot
plt.plot(x, y, label='Line plot')
plt.scatter(x, y, label='Scatter plot', color='red', s = 10)
plt.xlabel('x')
plt.ylabel('e^x')
plt.title('f(x) = e^x')
plt.grid()
plt.legend()
plt.show()