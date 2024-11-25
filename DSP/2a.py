import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import freqz

# Define coefficients of the transfer function
numerator_coeffs = [1, 1/3]  # Coefficients of x[n] and x[n-1]
denominator_coeffs = [1, -3/4, 1/8]  # Coefficients of y[n], y[n-1], and y[n-2]

# Compute the frequency response
w, h = freqz(numerator_coeffs, denominator_coeffs, worN=8000)

# Convert frequency to normalized values (0 to π)
normalized_frequency = w / np.pi

# Plot the frequency response
plt.figure(figsize=(12, 6))

# Magnitude Response
plt.subplot(2, 1, 1)
plt.plot(normalized_frequency, 20 * np.log10(abs(h)), 'b')  # Magnitude in dB
plt.title("Frequency Response of the System")
plt.ylabel("Magnitude (dB)")
plt.xlabel("Normalized Frequency (x π rad/sample)")
plt.grid()

# Phase Response
plt.subplot(2, 1, 2)
plt.plot(normalized_frequency, np.angle(h), 'g')  # Phase in radians
plt.ylabel("Phase (radians)")
plt.xlabel("Normalized Frequency (x π rad/sample)")
plt.grid()

plt.tight_layout()
plt.show()
