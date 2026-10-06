import numpy as np

from python.frequency_detector import detect_frequencies


def test_frequency_detector():
    sample_rate = 1000
    duration = 2

    t = np.arange(0, duration, 1 / sample_rate)

    signal = (
        np.sin(2 * np.pi * 5 * t)
        + 0.5 * np.sin(2 * np.pi * 20 * t)
    )

    detected = detect_frequencies(
        signal,
        sample_rate,
        num_frequencies=2
    )

    detected = sorted(detected)

    assert np.isclose(detected[0], 5)
    assert np.isclose(detected[1], 20)
