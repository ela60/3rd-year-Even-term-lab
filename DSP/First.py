import numpy as np
import matplotlib.pyplot as plt

# Parameters
fs = 64000  # Sampling frequency (64 kHz)
signal_length = 1000  # Number of samples
t = np.arange(signal_length) / fs  # Time array

# Frequencies and amplitudes
frequencies = [4000, 8000, 16000]  # Hz
amplitudes_db = [10, 20, 40]  # Decibels
amplitudes = [10**(amp_db / 20) for amp_db in amplitudes_db]  # Convert dB to linear scale

# Generate composite signal
signal = sum(amp * np.sin(2 * np.pi * f * t) for amp, f in zip(amplitudes, frequencies))

# Under-sampling
under_fs = 16000  # Under-sampling frequency
under_sampled_signal = signal[::int(fs / under_fs)]
under_sampled_time = t[::int(fs / under_fs)]

# Over-sampling
over_fs = 128000  # Over-sampling frequency
over_t = np.arange(0, signal_length / fs, 1 / over_fs)  # Over-sampling time array
over_sampled_signal = sum(amp * np.sin(2 * np.pi * f * over_t) for amp, f in zip(amplitudes, frequencies))

# Plot signals
plt.figure(figsize=(12, 8))

# Original signal
plt.subplot(3, 1, 1)
plt.plot(t[:200], signal[:200], label="Original Signal")
plt.title("Original Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid()
plt.legend()

# Under-sampled signal
plt.subplot(3, 1, 2)
plt.stem(under_sampled_time[:50], under_sampled_signal[:50], linefmt='r-', markerfmt='ro', basefmt=" ")
plt.title("Under-Sampled Signal (Aliasing Effect)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid()

# Over-sampled signal
plt.subplot(3, 1, 3)
plt.plot(over_t[:200], over_sampled_signal[:200], label="Over-Sampled Signal", color='g')
plt.title("Over-Sampled Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid()
plt.legend()

plt.tight_layout()
plt.show()
