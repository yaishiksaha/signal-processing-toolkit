# Signal Processing Toolkit

A CPU-based signal-processing toolkit implemented in Python and C++.

This project was built to understand the core stages of a basic digital
signal-processing pipeline rather than relying entirely on high-level
libraries. The project progresses from synthetic signal generation and
filtering to convolution, Fourier analysis, frequency detection, and
performance benchmarking.

## Pipeline

``` text
Signal Generation
       ↓
Moving-Average Filtering
       ↓
Convolution
       ↓
Fast Fourier Transform (FFT)
       ↓
Frequency Detection
       ↓
C++ Implementation
       ↓
Python/C++ Benchmarking
```

## Features

-   Synthetic sinusoidal signal generation
-   Moving-average filtering
-   Convolution
-   FFT-based frequency analysis
-   Frequency-peak detection
-   Python implementation using NumPy
-   C++ implementation using complex arithmetic
-   Custom radix-2 Cooley--Tukey FFT in C++
-   Automated Python tests
-   Python/C++ performance benchmarks

## Project Structure

``` text
signal-processing-toolkit/
│
├── python/
│   ├── signal_generator.py
│   ├── filters.py
│   ├── fft.py
│   ├── frequency_detector.py
│   └── ...
│
├── cpp/
│   ├── fft.cpp
│   ├── fft.h
│   ├── fft_demo.cpp
│   ├── frequency_detector.cpp
│   ├── frequency_detector.h
│   └── frequency_detection.cpp
│
├── benchmarks/
│   ├── benchmark_python.py
│   ├── benchmark_cpp.cpp
│   └── benchmark_results.md
│
├── tests/
│   ├── test_fft.py
│   ├── test_filters.py
│   └── test_frequency_detector.py
│
├── LICENSE
└── README.md
```

## Signal Generation

The project begins with synthetic signals composed of sinusoidal
components. This provides known input frequencies that can later be
recovered from the signal in the frequency domain.

A typical test signal contains components near:

-   5 Hz
-   20 Hz

with different amplitudes and optional noise.

## Filtering

A moving-average filter is implemented to demonstrate basic time-domain
signal processing.

For a window of length `M`, the moving-average output is:

``` text
y[n] = (1/M) * Σ x[n-k]
```

The filter reduces rapid fluctuations in the signal and provides a
simple example of convolution-based filtering.

## Convolution

Convolution is implemented explicitly to show the relationship between
filtering and convolution.

The project also includes a C++ implementation of convolution.

## Fourier Transform

The Python implementation uses NumPy's FFT functionality.

The C++ implementation contains a radix-2 Cooley--Tukey FFT implemented
from scratch.

The C++ FFT performs:

1.  Bit-reversal permutation
2.  Iterative butterfly operations
3.  Complex twiddle-factor multiplication

The implementation operates in place on a vector of complex numbers.

For a signal containing a 5 Hz and 20 Hz component, the FFT produces
strong spectral peaks near those frequencies.

Because the benchmark uses 1024 samples at a 1000 Hz sampling rate, the
frequency-bin spacing is:

``` text
1000 / 1024 ≈ 0.977 Hz
```

Therefore, a 5 Hz component is represented by a nearby FFT bin rather
than exactly 5 Hz.

## Frequency Detection

The frequency detector:

1.  Computes the FFT.
2.  Converts FFT coefficients to magnitudes.
3.  Converts FFT indices into frequencies.
4.  Searches for local magnitude peaks.
5.  Ignores frequencies below a configurable minimum.
6.  Selects the strongest separated peaks.

For the demonstration signal, the C++ detector identifies approximately:

``` text
4.88281 Hz
19.5312 Hz
```

These values are expected because of the finite frequency resolution of
the FFT.

## Python vs C++

Both implementations perform the same overall frequency-detection task,
but they do not use identical FFT implementations.

### Python

-   NumPy FFT
-   Custom Python peak-detection logic

### C++

-   Custom radix-2 Cooley--Tukey FFT
-   Custom C++ peak-detection logic

Therefore, the benchmark should **not** be interpreted as a general
Python-versus-C++ language comparison. In particular, NumPy's FFT is a
highly optimized numerical implementation, while the C++ FFT was
implemented from scratch as part of this project.

## Benchmark

The benchmark measures frequency-detection runtime for increasing signal
sizes.

### Methodology

-   Sampling rate: 1000 Hz
-   Input sizes: 1024, 2048, 4096, 8192, 16384 samples
-   Python: 20 benchmark runs per input size
-   C++: 20 benchmark runs per input size
-   C++: 100 detector iterations inside each timed run to improve timing
    resolution
-   C++ compilation: `g++ -O2`

### Average Runtime

    Samples   Python (ms)   C++ (ms)
  --------- ------------- ----------
      1,024         0.827      0.198
      2,048         0.681      0.411
      4,096         1.619      0.902
      8,192         2.711      1.801
     16,384         4.019      3.718

![Benchmark runtime](benchmark_runtime.png)

### Interpretation

The C++ implementation shows approximately twofold runtime increases as
the input size doubles. This is consistent with the expected
`O(N log N)` scaling of an FFT-based implementation, although the
complete frequency detector also includes peak-detection work and other
overhead.

The Python measurements are somewhat noisier because the benchmark is
affected by system timing variability and because NumPy uses an
optimized FFT implementation.

At 16,384 samples, the measured average runtime was approximately:

``` text
Python: 4.02 ms
C++:    3.72 ms
```

These measurements describe this specific implementation and machine;
they should not be treated as a universal performance comparison between
Python and C++.

## Testing

The project includes tests for:

-   FFT behavior
-   Filtering
-   Frequency detection

Run the Python tests with:

``` bash
python -m pytest
```

## Running the Examples

### Python

From the project root:

``` bash
python -m benchmarks.benchmark_python
```

### C++

Compile the frequency-detection demonstration:

``` bash
g++ cpp\fft.cpp cpp\frequency_detector.cpp cpp\frequency_detection.cpp -o frequency_detection.exe
```

Run:

``` bash
frequency_detection.exe
```

Compile the benchmark:

``` bash
g++ -O2 benchmarks\benchmark_cpp.cpp cpp\frequency_detector.cpp cpp\fft.cpp -o benchmark_cpp.exe
```

Run:

``` bash
benchmark_cpp.exe
```

## What I Learned

This project was primarily an exercise in understanding how
signal-processing algorithms work internally.

Key areas explored include:

-   Discrete-time signal representation
-   Moving-average filtering
-   Convolution
-   Frequency-domain analysis
-   FFT frequency resolution
-   Radix-2 FFT structure
-   Complex-number arithmetic
-   Local spectral peak detection
-   Algorithmic scaling
-   Benchmark design and measurement limitations
-   Translating an algorithm from Python to C++

A particularly important lesson was that benchmark results depend on
what is actually being compared. A custom C++ FFT and NumPy's optimized
FFT are useful to compare as implementations, but the result should not
be presented as a simple statement that one programming language is
faster than another.

## Future Work

Possible extensions include:

-   More robust spectral peak interpolation
-   Additional filtering methods
-   More extensive automated testing
-   Additional signal types and noise models
-   Profiling and targeted C++ optimization
-   Application to real-world biomedical or sensor signals

## License

This project is released under the MIT License.
