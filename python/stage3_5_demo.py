from python.signal_generator import generate_signal
from python.fft import compute_fft
from python.frequency_detector import detect_frequencies


t, noisy_signal = generate_signal(
    duration=2,
    sample_rate=1000,
    frequencies=[5, 20],
    amplitudes=[1, 0.5],
    noise_level=0.2
)

frequencies, magnitudes = compute_fft(noisy_signal, 1000)

detected = detect_frequencies(
    noisy_signal,
    1000,
    num_frequencies=2
)

print("Detected frequencies:")
for frequency in detected:
    print(f"{frequency:.1f} Hz")

strongest = sorted(
    range(1, len(magnitudes)),
    key=lambda i: magnitudes[i],
    reverse=True
)[:5]

print("\nStrongest frequency components:")
for i in strongest:
    print(f"{frequencies[i]:.1f} Hz -> magnitude {magnitudes[i]:.4f}")
