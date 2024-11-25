from scipy.signal import lfilter, dimpulse
import numpy as np
import matplotlib.pyplot as plt

# Coefficients for the difference equation
a = [1, -3/4, 1/8]  # Denominator (y[n] terms)
b = [1, 1/3]        # Numerator (x[n] terms)

# Impulse response calculation
n = 20  # Number of samples for impulse response
system = (b, a, 1)  # Define the system (b, a, sampling time)
_, h = dimpulse(system, n=n)  # Compute impulse response

# Convert to 1D array
h = np.squeeze(h)

# Plot the impulse response
plt.stem(np.arange(n), h)  # Removed use_line_collection
plt.title("Impulse Response h[n]")
plt.xlabel("n")
plt.ylabel("h[n]")
plt.grid()
plt.show()

# Display impulse response
print("Impulse Response h[n]:", h)
