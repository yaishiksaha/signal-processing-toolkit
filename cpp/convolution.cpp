#include <iostream>
#include <vector>

using namespace std;

vector<double> convolve(const vector<double>& signal, const vector<double>& kernel) {
    vector<double> result;

    for (int i = 0; i <= signal.size() - kernel.size(); i++) {
        double total = 0;

        for (int j = 0; j < kernel.size(); j++) {
            total += signal[i + j] * kernel[j];
        }

        result.push_back(total);
    }

    return result;
}

int main() {
    vector<double> signal = {1, 2, 3, 4, 5};
    vector<double> kernel = {1, 1, 1};

    vector<double> result = convolve(signal, kernel);

    for (double value : result) {
        cout << value << " ";
    }

    cout << endl;

    return 0;
}
