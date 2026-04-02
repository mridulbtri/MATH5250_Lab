import numpy as np
import matplotlib.pyplot as plt

def plotV():
    # First, figure out how many points there are
    fid = open('potential.data', 'r')
    NumPts = 0
    while True:
        line = fid.readline()
        if not line: break
        NumPts = NumPts + 1
    fid.close()

    # Second, read in all the floats
    x0 = np.zeros(NumPts, dtype=float)
    V  = np.zeros(NumPts, dtype=float)
    fid = open('potential.data', 'r')
    for k in range(0, NumPts):
        linestring = fid.readline()
        linelist   = linestring.split()
        x0[k] = float(linelist[0])
        V[k]  = float(linelist[1])
    fid.close()

    # Third, plot the result
    plt.rc("font", size=16)
    plt.figure(1)
    plt.plot(x0, V, color='b', linewidth=2)
    plt.xlabel('$x_0$')
    plt.ylabel('$V(x_0)$')
    plt.title('Electrostatic Potential, $\\rho(x)=e^{-x^2}$, $[a,b]=[-1,1]$')
    plt.grid(True)
    plt.savefig('potential.png', dpi=400, bbox_inches='tight')

def plotJ0():
    # First, figure out how many points there are
    fid = open('bessel.data', 'r')
    NumPts = 0
    while True:
        line = fid.readline()
        if not line: break
        NumPts = NumPts + 1
    fid.close()

    # Second, read in all the floats
    x  = np.zeros(NumPts, dtype=float)
    J0 = np.zeros(NumPts, dtype=float)
    fid = open('bessel.data', 'r')
    for k in range(0, NumPts):
        linestring = fid.readline()
        linelist   = linestring.split()
        x[k]  = float(linelist[0])
        J0[k] = float(linelist[1])
    fid.close()

    # Third, plot the result
    plt.rc("font", size=16)
    plt.figure(2)
    plt.plot(x, J0, color='b', linewidth=2)
    plt.axhline(0, color='k', linewidth=0.8, linestyle='--')
    plt.xlabel('$x$')
    plt.ylabel('$J_0(x)$')
    plt.title('Bessel Function $J_0(x)$, $x \\in [0,50]$')
    plt.grid(True)
    plt.savefig('bessel.png', dpi=400, bbox_inches='tight')

if __name__ == "__main__":
    plotV()
    plotJ0()
    plt.show()