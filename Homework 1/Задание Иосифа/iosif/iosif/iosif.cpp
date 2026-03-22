#include <iostream>
#include <vector>
#include <ctime>

int josephus(int n, int k) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        res = (res + k) % i;
    }
    return res + 1;
}

int main() {
	setlocale(LC_ALL, "Russian");
    std::vector<int> test_n = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int k = 3;

    for (int n : test_n) {
        clock_t start = clock();
        int result = josephus(n, k);
        clock_t end = clock();

        double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;

        std::cout << "N: " << n << " | Ответ: " << result << " | Время: " << duration << " сек" << std::endl;
    }

    return 0;
}
