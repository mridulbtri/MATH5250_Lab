import numpy as np
import matplotlib.pyplot as plt

def PlotPoly():
    # --- First: count how many points ---
    with open("/Users/mridul/Lecture03/lecture9/poly_data.txt", "r") as fid:
        NumPts = sum(1 for _ in fid)

    # --- Second: read the data ---
    x = np.zeros(NumPts, dtype=float)
    y = np.zeros(NumPts, dtype=float)

    with open("poly_data.txt", "r") as fid:
        for k in range(NumPts):
            line = fid.readline()
            vals = line.split()
            x[k] = float(vals[0])
            y[k] = float(vals[1])

    # --- Third: plot ---
    plt.rc("font", size=16)
    plt.figure(1)

    plt.plot(x, y,
             linestyle="dashed",
             linewidth=2,
             marker="o",
             color="red",
             markersize=8)

    plt.xlim(-1.0, 1.0)
    plt.xticks([-1.0, -0.5, 0.0, 0.5, 1.0])

    ax = plt.gca()
    ax.grid(True)

    plt.xlabel("x", size=20)
    plt.ylabel("y(x))", size=20)
    plt.title("Chebyshev Polynomial Plot", size=20)

    plt.savefig("chebyshev.png", dpi=400, bbox_inches="tight")
    plt.show()

if __name__ == "__main__":
    PlotPoly()
