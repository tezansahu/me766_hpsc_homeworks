import matplotlib.pyplot as plt

# Trapezoidal Rule

## Convergence
divs = [2, 4, 8, 16, 50, 100, 200, 500, 1000, 2000, 5000, 10000]
integral = [1.5708, 1.89612, 1.9742, 1.99357, 1.99934, 1.99984, 1.99996, 1.99999, 2, 2, 2, 2]

fig = plt.figure()
plt.plot(divs, integral, "o-", label="Trapezoidal Integral")
plt.plot([2, 10000], [2,2], "--", label="Analytical Integral")
plt.legend()
plt.xlabel("Number of Divisions")
plt.ylabel("Integral Value")
plt.title("Convergence Study of Trapezoidal Rule")
plt.xscale("log")
plt.savefig("trapzoidal_convergence.png", bbox_inches="tight")

## Timing

fig = plt.figure()
plt.plot([2,4,6,8], [0.14, 0.093, 0.055, 0.044], "o-")
plt.xlabel("No. of OpenMP Threads")
plt.ylabel("Average Time Taken (s)")
plt.title("Timing Study of Trapezoidal Rule (1,00,00,000 Divisions)")
plt.savefig("trapzoidal_timing.png", bbox_inches="tight")
####################################################################################################


# Montecarlo Method

## Convergence
pts = [2, 4, 8, 16, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 50000, 100000, 500000, 1000000]
integral = [3.14159, 2.35619, 1.9635, 2.15984, 2.07345, 2.26195, 2.26195, 2.0923, 2.03261, 1.98706, 1.98234, 1.98831, 1.99271, 1.99959, 2.00344, 2.00167]

fig = plt.figure()
plt.plot(pts, integral, "o-", label="Montecarlo Integral")
plt.plot([2, 1000000], [2,2], "--", label="Analytical Integral")
plt.legend()
plt.xlabel("Number of Divisions")
plt.ylabel("Integral Value")
plt.title("Convergence Study of Montecarlo Method")
plt.xscale("log")
plt.savefig("montecarlo_convergence.png", bbox_inches="tight")

## Timing
fig = plt.figure()
plt.plot([2,4,6,8], [4.113, 2.758, 2.783, 3.387], "o-")
plt.ylim([2, 4.5])
plt.xlabel("No. of OpenMP Threads")
plt.ylabel("Average Time Taken (s)")
plt.title("Timing Study of Montecarlo Method (1,00,00,000 Sample Points)")
plt.savefig("montecarlo_timing.png", bbox_inches="tight")