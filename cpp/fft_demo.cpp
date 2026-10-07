#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#include "fft.h"

using namespace std;

const double PI = acos(-1.0);

int main() {
    const int n = 1024;
    const double sample_rate = 1000.0;

    vector<complex<double>> signal(n);

    for (int i = 0; i < n; i++) {
        double t = i / sample_rate;

        double value =
            sin(2 * PI * 5 * t) +
            0.5 * sin(2 * PI * 20 * t);

        signal[i] = value;
    }

    fft(signal);

    cout << "FFT completed for " << n << " samples." << endl;
    cout << "First 10 frequency bins:" << endl;

    for (int i = 0; i < 10; i++) {
        double frequency = i * sample_rate / n;
        double magnitude = abs(signal[i]) / n;

        if (i != 0 && i != n / 2) {
            magnitude *= 2;
        }

        cout << frequency << " Hz -> " << magnitude << endl;
    }

    return 0;
}