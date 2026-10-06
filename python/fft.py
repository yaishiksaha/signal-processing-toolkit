import numpy as np


def compute_fft(signal, sample_rate):
    signal = np.asarray(signal)

    spectrum = np.fft.rfft(signal)
    frequencies = np.fft.rfftfreq(len(signal), 1 / sample_rate)
    magnitudes = np.abs(spectrum) / len(signal)

    if len(signal) > 1:
        magnitudes[1:-1] *= 2

    return frequencies, magnitudes
