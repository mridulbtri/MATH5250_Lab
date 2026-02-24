import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv("poly_data.csv")

# Plot
plt.plot(df["x"], df["P(x)"],    color="blue",  label="P(x)")
plt.plot(df["x"], df["Q(x)"],    color="red",   label="Q(x)")
plt.plot(df["x"], df["P+Q(x)"],  color="green", label="P(x) + Q(x)")

# Labels and legend
plt.xlabel("x")
plt.ylabel("y")
plt.title("Polynomial Plot")
plt.legend()
plt.grid(True)

plt.show()