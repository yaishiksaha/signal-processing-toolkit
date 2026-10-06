import numpy as np


def generate_signal(duration, sample_rate, frequencies, amplitudes, noise_level):
    t = np.arange(0, duration, 1 / sample_rate)

    signal = np.zeros(len(t))

    for frequency, amplitude in zip(frequencies, amplitudes):
        signal += amplitude * np.sin(2 * np.pi * frequency * t)

    noise = noise_level * np.random.randn(len(t))

    return t, signal + noise


if __name__ == "__main__":
    t, signal = generate_signal(
        duration=2,
        sample_rate=1000,
        frequencies=[5, 20],
        amplitudes=[1, 0.5],
        noise_level=0.2
    )

    print("Number of samples:", len(signal))
    print("First 10 samples:")
    print(signal[:10])