import numpy as np
from scipy.signal import dimpulse, lfilter

# Coefficients of the difference equation
b = [1, 1/3]  # Numerator coefficients
a = [1, -3/4, 1/8]  # Denominator coefficients

# Define n as an integer
n = 50  # Number of samples for impulse response

# Compute impulse response
_, h = dimpulse((b, a, 1), n=n)

# Plot the impulse response
import matplotlib.pyplot as plt
plt.stem(range(n), np.squeeze(h))
plt.title("Impulse Response")
plt.xlabel("n")
plt.ylabel("h[n]")
plt.grid()
plt.show()
