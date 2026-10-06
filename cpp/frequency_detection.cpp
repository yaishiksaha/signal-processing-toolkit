#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);

void fft(vector<complex<double>>& a) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;

        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }

        j ^= bit;

        if (i < j) {
            swap(a[i], a[j]);
        }
    }

    for (int length = 2; length <= n; length <<= 1) {
        double angle = -2 * PI / length;
        complex<double> root(cos(angle), sin(angle));

        for (int i = 0; i < n; i += length) {
            complex<double> current_root(1, 0);

            for (int j = 0; j < length / 2; j++) {
                complex<double> even = a[i + j];
                complex<double> odd = a[i + j + length / 2] * current_root;

                a[i + j] = even + odd;
                a[i + j + length / 2] = even - odd;

                current_root *= root;
            }
        }
    }
}

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

    fft(signal);

    vector<pair<double, double>> peaks;

    for (int i = 1; i < n / 2; i++) {
        double magnitude = abs(signal[i]) / n;
        magnitude *= 2;

        if (magnitude >= abs(signal[i - 1]) / n &&
            magnitude >= abs(signal[i + 1]) / n) {
            double frequency = i * sample_rate / n;
            peaks.push_back({magnitude, frequency});
        }
    }

    sort(peaks.rbegin(), peaks.rend());

    cout << "Detected frequencies:" << endl;

    int count = min(2, static_cast<int>(peaks.size()));

    for (int i = 0; i < count; i++) {
        cout << peaks[i].second << " Hz" << endl;
    }

    return 0;
}
