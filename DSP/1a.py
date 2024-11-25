import numpy as np
import matplotlib.pyplot as plt


fs = 48000  
t = np.linspace(0, 1, 1000, endpoint=False) 
f1, f2, f3 = 4000, 8000, 16000  

# Generating the signals
signal1 = np.sin(2 * np.pi * f1 * t)
signal2 = np.sin(2 * np.pi * f2 * t)
signal3 = np.sin(2 * np.pi * f3 * t)

# Composite Signal
composite_signal = signal1 + signal2 + signal3

# Plot the composite signal
plt.figure()
plt.plot(t, composite_signal)
plt.title("Composite Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid()
plt.show()
