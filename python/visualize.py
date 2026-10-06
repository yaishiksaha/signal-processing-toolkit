import matplotlib.pyplot as plt
from signal_generator import generate_signal


t, signal = generate_signal(
    duration=2,
    sample_rate=1000,
    frequencies=[5, 20],
    amplitudes=[1, 0.5],
    noise_level=0.2
)

plt.plot(t, signal)
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.title("Noisy Signal")
plt.grid()
plt.show()