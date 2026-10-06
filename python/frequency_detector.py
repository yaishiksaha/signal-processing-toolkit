import numpy as np

from python.fft import compute_fft


def detect_frequencies(signal, sample_rate, num_frequencies=2, min_frequency=1):
    frequencies, magnitudes = compute_fft(signal, sample_rate)

    candidates = []

    for i in range(1, len(magnitudes) - 1):
        if frequencies[i] < min_frequency:
            continue

        if magnitudes[i] >= magnitudes[i - 1] and magnitudes[i] >= magnitudes[i + 1]:
            candidates.append((magnitudes[i], frequencies[i]))

    candidates.sort(reverse=True)

    selected = []

    for magnitude, frequency in candidates:
        if all(abs(frequency - selected_frequency) >= 1 for selected_frequency in selected):
            selected.append(frequency)

        if len(selected) == num_frequencies:
            break

    return selected
