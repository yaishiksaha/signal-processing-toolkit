# Benchmark Results

## Objective

Measure the runtime of frequency detection in the Python and C++ implementations for increasing input sizes.

## Methodology

- Sample rate: 1000 Hz
- Input sizes: 1024, 2048, 4096, 8192, and 16384 samples
- Python: NumPy FFT with custom Python frequency-peak detection
- C++: Custom radix-2 FFT with custom C++ frequency-peak detection
- C++ compiler optimization: `-O2`
- C++ benchmark: 20 runs per input size, with 100 detector calls per timed run

The Python benchmark uses 20 runs per input size. Its reported minimum and average times are retained from the original measurements.

## Average Runtime

| Samples | Python (seconds) | C++ (seconds) |
|---:|---:|---:|
| 1024 | 0.000827 | 0.000197629 |
| 2048 | 0.000681 | 0.000410772 |
| 4096 | 0.001619 | 0.000902073 |
| 8192 | 0.002711 | 0.00180122 |
| 16384 | 0.004019 | 0.0037183 |

## Analysis

The C++ measurements show approximately twofold runtime increases when the input size doubles. This is consistent with the expected O(N log N) complexity of the radix-2 FFT, although the frequency detector also contributes to total runtime.

The Python measurements show more variability. NumPy provides an optimized FFT implementation, while the C++ implementation uses a custom FFT. Consequently, this experiment compares two complete implementations rather than isolating the performance of the programming languages themselves.

At 16384 samples, the measured average runtime was approximately 3.72 ms for C++ and 4.02 ms for Python. These results are preliminary and should not be treated as a universal performance ranking.

## Limitations

- The measurements were collected on one machine.
- Background processes and timing overhead may affect results.
- The Python and C++ implementations use different FFT implementations.
- Further repeated measurements under controlled conditions would improve the comparison.

## Conclusion

The benchmark demonstrates that the custom C++ implementation processes increasing input sizes with scaling consistent with FFT-based frequency detection. It also establishes a reproducible starting point for future optimization and testing.