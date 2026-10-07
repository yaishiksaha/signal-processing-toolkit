# Benchmark Results

## Objective

Measure the runtime of frequency detection in the Python and C++
implementations for increasing input sizes.

## Methodology

-   Sampling rate: 1000 Hz
-   Input sizes: 1024, 2048, 4096, 8192, and 16384 samples
-   Python: NumPy FFT with custom Python frequency-peak detection
-   C++: custom radix-2 FFT with custom C++ frequency-peak detection
-   C++ compiler optimization: `-O2`
-   Python: 20 runs per input size
-   C++: 20 runs per input size, with 100 detector calls inside each
    timed run

## Average Runtime

    Samples   Python (s)       C++ (s)
  --------- ------------ -------------
       1024     0.000827   0.000197629
       2048     0.000681   0.000410772
       4096     0.001619   0.000902073
       8192     0.002711    0.00180122
      16384     0.004019     0.0037183

## Scaling

The C++ runtime approximately doubles as the input size doubles:

  Input change     C++ average-time factor
  -------------- -------------------------
  1024 → 2048                        2.08×
  2048 → 4096                        2.20×
  4096 → 8192                        2.00×
  8192 → 16384                       2.06×

This is consistent with the expected `O(N log N)` scaling of an
FFT-based implementation.

## Important Comparison Note

The benchmark is not a pure Python-versus-C++ language comparison.

The Python implementation uses NumPy's optimized FFT, while the C++
implementation uses a custom radix-2 Cooley--Tukey FFT written as part
of this project.

Therefore, the results are best interpreted as a comparison between
these two implementations on the same workload.

## Limitations

-   Measurements were collected on one machine.
-   Background processes can affect timing.
-   Python and C++ use different FFT implementations.
-   The benchmark measures the complete frequency-detection pipeline
    rather than the FFT alone.
-   The results should not be generalized to all Python and C++
    programs.

## Conclusion

The benchmark provides empirical evidence that the custom C++
frequency-detection pipeline scales approximately as expected for an
FFT-based algorithm. It also provides a reproducible baseline for future
optimization or algorithmic changes.
