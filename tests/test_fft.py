import numpy as np
from python.fft import compute_fft


def test_fft_detects_known_frequencies():
    sample_rate = 1000
    duration = 2

    t = np.arange(0, duration, 1 / sample_rate)

    signal = (
        np.sin(2 * np.pi * 5 * t)
        + 0.5 * np.sin(2 * np.pi * 20 * t)
    )

    frequencies, magnitudes = compute_fft(signal, sample_rate)

    strongest = np.argsort(magnitudes[1:])[-2:] + 1
    detected = sorted(frequencies[strongest])

    assert np.isclose(detected[0], 5)
    assert np.isclose(detected[1], 20)
