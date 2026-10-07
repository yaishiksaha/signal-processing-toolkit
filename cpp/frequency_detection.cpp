#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#include "frequency_detector.h"

using namespace std;

const double PI = acos(-1.0);

int main() {
    const int n = 1024;
    const double sample_rate = 1000.0;

    vector<complex<double>> signal(n);

    for (int i = 0; i < n; i++) {
        double t = i / sample_rate;

        signal[i] =
            sin(2 * PI * 5 * t) +
            0.5 * sin(2 * PI * 20 * t);
    }

    vector<double> detected = detect_frequencies(
        signal,
        sample_rate,
        2
    );

    cout << "Detected frequencies:" << endl;

    for (double frequency : detected) {
        cout << frequency << " Hz" << endl;
    }

    return 0;
}