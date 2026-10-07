#ifndef FREQUENCY_DETECTOR_H
#define FREQUENCY_DETECTOR_H

#include <complex>
#include <vector>

std::vector<double> detect_frequencies(
    const std::vector<std::complex<double>>& signal,
    double sample_rate,
    int num_frequencies = 2,
    double min_frequency = 1.0
);

#endif