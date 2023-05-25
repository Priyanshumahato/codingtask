#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to compute minimum value
int parallelMin(const vector<int>& data) {
    int min_val = data[0];
    #pragma omp parallel for reduction(min: min_val)
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] < min_val) {
            min_val = data[i];
        }
    }
    return min_val;
}

// Function to compute maximum value
int parallelMax(const vector<int>& data) {
    int max_val = data[0];
    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }
    return max_val;
}

// Function to compute sum
int parallelSum(const vector<int>& data) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    return sum;
}

// Function to compute average
double parallelAvg(const vector<int>& data) {
    int sum = parallelSum(data);
    double avg = static_cast<double>(sum) / data.size();
    return avg;
}

int main() {
    vector<int> data = {5, 10, 3, 8, 12, 6};
    
    int min_val = parallelMin(data);
    cout << "Minimum value: " << min_val << endl;

    int max_val = parallelMax(data);
    cout << "Maximum value: " << max_val << endl;

    int sum = parallelSum(data);
    cout << "Sum: " << sum << endl;

    double avg = parallelAvg(data);
    cout << "Average: " << avg << endl;

    return 0;
}
