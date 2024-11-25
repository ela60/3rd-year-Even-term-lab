import numpy as np
import matplotlib.pyplot as plt

# Signal parameters
fs = 8000  
N = 1000 
t = np.arange(N) / fs  

# Frequencies and amplitudes in dB
frequencies = [4000, 8000, 16000]  # Hz
amplitudes_dB = [10, 20, 40]  # dB


amplitudes = [10**(amp / 20) for amp in amplitudes_dB]

# Generate the composite signal
composite_signal = (amplitudes[0] * np.sin(2 * np.pi * frequencies[0] * t) +
                    amplitudes[1] * np.sin(2 * np.pi * frequencies[1] * t) +
                    amplitudes[2] * np.sin(2 * np.pi * frequencies[2] * t))

# Perform 8-point DFT
dft_points = 8
dft_result = np.fft.fft(composite_signal[:dft_points], n=dft_points)
frequencies_dft = np.fft.fftfreq(dft_points, 1/fs)  # Frequency bins

# Calculate Amplitude Spectrum and Phase Spectrum
amplitude_spectrum = np.abs(dft_result)
phase_spectrum = np.angle(dft_result)

# Plotting
plt.figure(figsize=(12, 8))

# Composite Signal
plt.subplot(3, 1, 1)
plt.plot(t[:100], composite_signal[:100])  
plt.title("Composite Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid()

# Amplitude Spectrum
plt.subplot(3, 1, 2)
plt.stem(frequencies_dft[:dft_points // 2], amplitude_spectrum[:dft_points // 2])  # Removed use_line_collection
plt.title("Amplitude Spectrum")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Amplitude")
plt.grid()

# Phase Spectrum
plt.subplot(3, 1, 3)
plt.stem(frequencies_dft[:dft_points // 2], phase_spectrum[:dft_points // 2])  # Removed use_line_collection
plt.title("Phase Spectrum")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Phase (radians)")
plt.grid()

plt.tight_layout()
plt.show()