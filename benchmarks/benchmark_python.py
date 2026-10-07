import time
import numpy as np

from python.frequency_detector import detect_frequencies


def generate_signal(n, sample_rate):
    t = np.arange(n) / sample_rate

    signal = (
        np.sin(2 * np.pi * 5 * t)
        + 0.5 * np.sin(2 * np.pi * 20 * t)
    )

    return signal


def benchmark(n, sample_rate, runs):
    signal = generate_signal(n, sample_rate)

    times = []

    for _ in range(runs):
        start = time.perf_counter()

        detect_frequencies(
            signal,
            sample_rate,
            num_frequencies=2
        )

        end = time.perf_counter()

        times.append(end - start)

    return min(times), sum(times) / len(times)


sample_rate = 1000
runs = 20

sizes = [1024, 2048, 4096, 8192, 16384]

print("Python frequency detection benchmark")
print()
print("Samples\tMinimum (s)\tAverage (s)")

for n in sizes:
    minimum, average = benchmark(n, sample_rate, runs)

    print(f"{n}\t{minimum:.6f}\t{average:.6f}")