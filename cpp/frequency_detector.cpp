#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

#include "fft.h"
#include "frequency_detector.h"

using namespace std;

vector<double> detect_frequencies(
    const vector<complex<double>>& signal,
    double sample_rate,
    int num_frequencies,
    double min_frequency
) {
    vector<complex<double>> spectrum = signal;

    int n = spectrum.size();

    fft(spectrum);

    vector<pair<double, double>> candidates;

    for (int i = 1; i < n / 2; i++) {
        double magnitude = abs(spectrum[i]) / n;
        magnitude *= 2;

        double frequency = i * sample_rate / n;

        if (frequency < min_frequency) {
            continue;
        }

        double previous_magnitude = abs(spectrum[i - 1]) / n;
        double next_magnitude = abs(spectrum[i + 1]) / n;

        if (magnitude >= previous_magnitude &&
            magnitude >= next_magnitude) {
            candidates.push_back({magnitude, frequency});
        }
    }

    sort(candidates.rbegin(), candidates.rend());

    vector<double> selected;

    for (auto candidate : candidates) {
        double frequency = candidate.second;

        bool far_enough = true;

        for (double selected_frequency : selected) {
            if (abs(frequency - selected_frequency) < 1.0) {
                far_enough = false;
                break;
            }
        }

        if (far_enough) {
            selected.push_back(frequency);
        }

        if (selected.size() == num_frequencies) {
            break;
        }
    }

    return selected;
}