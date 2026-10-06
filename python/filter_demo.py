from signal_generator import generate_signal
from filters import moving_average


t, noisy_signal = generate_signal(
    duration=2,
    sample_rate=1000,
    frequencies=[5, 20],
    amplitudes=[1, 0.5],
    noise_level=0.2
)

filtered_signal = moving_average(noisy_signal, 5)

print("Number of samples:", len(noisy_signal))
print("Number of filtered samples:", len(filtered_signal))
print("First 10 noisy samples:")
print(noisy_signal[:10])
print("First 10 filtered samples:")
print(filtered_signal[:10])