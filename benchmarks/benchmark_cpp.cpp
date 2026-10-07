#include <chrono>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#include "../cpp/frequency_detector.h"

using namespace std;

const double PI = acos(-1.0);

vector<complex<double>> generate_signal(
    int n,
    double sample_rate
) {
    vector<complex<double>> signal(n);

    for (int i = 0; i < n; i++) {
        double t = i / sample_rate;

        double value =
            sin(2 * PI * 5 * t) +
            0.5 * sin(2 * PI * 20 * t);

        signal[i] = value;
    }

    return signal;
}

void benchmark(
    int n,
    double sample_rate,
    int runs,
    int iterations
) {
    vector<complex<double>> signal =
        generate_signal(n, sample_rate);

    double minimum = 1e100;
    double total = 0;

    for (int i = 0; i < runs; i++) {
        auto start = chrono::high_resolution_clock::now();

        for (int j = 0; j < iterations; j++) {
            vector<double> detected =
                detect_frequencies(
                    signal,
                    sample_rate,
                    runs,
                    iterations
                );
        }

        auto end = chrono::high_resolution_clock::now();

        double elapsed =
            chrono::duration<double>(end - start).count();

        double time_per_run = elapsed / iterations;

        total += time_per_run;

        if (time_per_run < minimum) {
            minimum = time_per_run;
        }
    }

    double average = total / runs;

    cout << n << "\t"
         << minimum << "\t"
         << average << endl;
}

int main() {
    const double sample_rate = 1000.0;
    const int runs = 20;
    const int iterations = 100;

    vector<int> sizes = {
        1024,
        2048,
        4096,
        8192,
        16384
    };

    cout << "C++ frequency detection benchmark" << endl;
    cout << endl;
    cout << "Samples\tMinimum (s)\tAverage (s)" << endl;

    for (int n : sizes) {
        benchmark(
            n,
            sample_rate,
            runs,
            iterations
        );
    }

    return 0;
}