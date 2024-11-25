import numpy as np
import matplotlib.pyplot as plt


fs = 64000  
signal_length = 1000  
t = np.arange(signal_length) / fs  

# Frequencies and amplitudes
frequencies = [4000, 8000, 16000]
amplitudes_db = [10, 20, 40]  
amplitudes = [10**(amp_db / 20) for amp_db in amplitudes_db]  

# Generate composite signal
signal = sum(amp * np.sin(2 * np.pi * f * t) for amp, f in zip(amplitudes, frequencies))

# Nyquist rate sampling
nyquist_fs = 32000  
sampled_signal = signal[::int(fs / nyquist_fs)]  
sampled_time = t[::int(fs / nyquist_fs)]

# Plot sampled signal
plt.figure(figsize=(10, 4))
plt.stem(sampled_time[:50], sampled_signal[:50], linefmt='r-', markerfmt='ro', basefmt=" ")
plt.title("Sampled Signal at Nyquist Rate")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid()
plt.show()
