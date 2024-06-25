#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long FibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
}

long long FibonacciDynamic(int n) {
    long long* fib = new long long[n + 1];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    long long result = fib[n];
    delete[] fib;
    return result;
}

void measureExecutionTime(int n) {
    high_resolution_clock::time_point time1, time2;

    time1 = high_resolution_clock::now();
    cout << "Hasil Fibonacci (rekursif) untuk n = " << n << " adalah " << FibonacciRecursive(n) << endl;
    time2 = high_resolution_clock::now();
    auto durationRecursive = duration_cast<microseconds>(time2 - time1).count();
    cout << "Waktu eksekusi (rekursif): " << durationRecursive << " mikrodetik" << endl;

    time1 = high_resolution_clock::now();
    cout << "Hasil Fibonacci (dynamic programming) untuk n = " << n << " adalah " << FibonacciDynamic(n) << endl;
    time2 = high_resolution_clock::now();
    auto durationDynamic = duration_cast<microseconds>(time2 - time1).count();
    cout << "Waktu eksekusi (dynamic programming): " << durationDynamic << " mikrodetik" << endl;

    cout << "==========================================================================" << "\n";
}

int main() {
    cout << "==========================================================================" << endl;
    int Nilai[] = {10, 25, 30, 40, 50};
    for (int n : Nilai) {
        measureExecutionTime(n);
    }
    return 0;
}