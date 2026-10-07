#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>

#include "fft.h"

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
                complex<double> odd =
                    a[i + j + length / 2] * current_root;

                a[i + j] = even + odd;
                a[i + j + length / 2] = even - odd;

                current_root *= root;
            }
        }
    }
}
