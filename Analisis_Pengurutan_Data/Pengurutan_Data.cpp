#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void BubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void InsertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void SelectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}


void Merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void MergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}


int Partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void QuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}


vector<int> generateRandomVector(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}


void measureExecutionTime(void (*sortFunc)(vector<int>&), vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();
    cout << fixed << setprecision(6) << duration / 1000000.0 << " seconds" << endl;
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 10000,};

    for (int size : sizes) {
        vector<int> randomVec = generateRandomVector(size);
        vector<int> reversedVec = randomVec;
        sort(reversedVec.begin(), reversedVec.end(), greater<int>());
        vector<int> sortedVec = randomVec;
        sort(sortedVec.begin(), sortedVec.end());

        cout << "Array size: " << size << endl;

        cout << "Bubble Sort (Random): ";
        measureExecutionTime(BubbleSort, randomVec);

        cout << "Bubble Sort (Reversed): ";
        measureExecutionTime(BubbleSort, reversedVec);

        cout << "Bubble Sort (Sorted): ";
        measureExecutionTime(BubbleSort, sortedVec);

        cout << "Insertion Sort (Random): ";
        measureExecutionTime(InsertionSort, randomVec);

        cout << "Insertion Sort (Reversed): ";
        measureExecutionTime(InsertionSort, reversedVec);

        cout << "Insertion Sort (Sorted): ";
        measureExecutionTime(InsertionSort, sortedVec);

        cout << "Selection Sort (Random): ";
        measureExecutionTime(SelectionSort, randomVec);

        cout << "Selection Sort (Reversed): ";
        measureExecutionTime(SelectionSort, reversedVec);

        cout << "Selection Sort (Sorted): ";
        measureExecutionTime(SelectionSort, sortedVec);

        cout << "Merge Sort (Random): ";
        measureExecutionTime([](vector<int>& arr) { MergeSort(arr, 0, arr.size() - 1); }, randomVec);

        cout << "Merge Sort (Reversed): ";
        measureExecutionTime([](vector<int>& arr) { MergeSort(arr, 0, arr.size() - 1); }, reversedVec);

        cout << "Merge Sort (Sorted): ";
        measureExecutionTime([](vector<int>& arr) { MergeSort(arr, 0, arr.size() - 1); }, sortedVec);

        cout << "Quick Sort (Random): ";
        measureExecutionTime([](vector<int>& arr) { QuickSort(arr, 0, arr.size() - 1); }, randomVec);

        cout << "Quick Sort (Reversed): ";
        measureExecutionTime([](vector<int>& arr) { QuickSort(arr, 0, arr.size() - 1); }, reversedVec);

        cout << "Quick Sort (Sorted): ";
        measureExecutionTime([](vector<int>& arr) { QuickSort(arr, 0, arr.size() - 1); }, sortedVec);

        cout << "-----------------------------------" << endl;
    }

    return 0;
}
