#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    #pragma omp parallel shared(arr, n)
    {
        int start = 0;
        int end = n - 1;

        for (int k = 0; k < n; k++) {
            if (k % 2 == 0) {
                #pragma omp for
                for (int i = start; i < end; i += 2) {
                    if (arr[i] > arr[i + 1]) {
                        swap(arr[i], arr[i + 1]);
                    }
                }
            } else {
                #pragma omp for
                for (int i = start + 1; i < end; i += 2) {
                    if (arr[i] > arr[i + 1]) {
                        swap(arr[i], arr[i + 1]);
                    }
                }
            }

            #pragma omp barrier

            if (k % 2 == 0) {
                start = 1;
            } else {
                start = 0;
            }
        }
    }
}

int main() {
    vector<int> arr = {5, 2, 8, 1, 3};

    cout << "Before sorting: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    bubbleSort(arr);

    cout << "After sorting: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

//////Merge

#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr, left, middle);
            }

            #pragma omp section
            {
                mergeSort(arr, middle + 1, right);
            }
        }

        merge(arr, left, middle, right);
    }
}

int main() {
    vector<int> arr = {9, 7, 5, 1, 3, 8, 2, 6, 4};

    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
