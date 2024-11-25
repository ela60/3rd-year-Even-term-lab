import numpy as np
import matplotlib.pyplot as plt

# Signal parameters
fs = 32000  # Sampling frequency
t = np.linspace(0, 1, 1000)  # Time array
signal = np.sin(2 * np.pi * 4000 * t) + np.sin(2 * np.pi * 8000 * t) + np.sin(2 * np.pi * 16000 * t)

# Nyquist rate
nyquist_rate = 2 * max(4000, 8000, 16000)

# Standard sampling
if fs >= nyquist_rate:
    standard_samples = signal[::int(fs / nyquist_rate)]
else:
    raise ValueError("Sampling frequency must be at least twice the Nyquist rate.")

# Plot original and sampled signals
plt.subplot(2, 1, 1)
plt.plot(t, signal, label="Original Signal")
plt.legend()

plt.subplot(2, 1, 2)
sampled_t = t[::int(fs / nyquist_rate)]
plt.stem(sampled_t, standard_samples, linefmt='r-', markerfmt='ro', basefmt='g-', label="Sampled Signal")
plt.legend()

plt.show()
