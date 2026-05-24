#include <iostream>
#include <chrono>
#include "Array.h"

// Reshenie zadachi Iosifa-Flaviya:
// Iz konteyneра s N elementami (1..N) poocheredno udalyaetsya
// kazhdyy k-y element (schet s 1).
// Vozvraschaetsya znachenie poslednego ostavshegosya elementa.
int josephus(int n, int k) {
    Array arr(n);

    // Nachal'naya poziciya: schitaem s 0-go indeksa
    int current = 0;

    while (arr.getSize() > 1) {
        // Vychislyaem indeks elementa, kotoryy nado udalit'
        // (k shagow vpered ot tekushchey pozicii, -1 t.k. schet s 1)
        current = (current + k - 1) % arr.getSize();

        arr.removeAt(current);

        // Posle udaleniya current ukazyvaet na sleduyushchiy element;
        // esli eto za graniceiy — vozvraschaemesya v nachalo
        if (current >= arr.getSize())
            current = 0;
    }

    return arr.get(0);
}

int main() {
    int n, k;

    std::cout << "Enter N (number of elements): ";
    std::cin >> n;
    std::cout << "Enter k (step): ";
    std::cin >> k;

    if (n <= 0 || k <= 0) {
        std::cerr << "Error: N and k must be positive integers." << std::endl;
        return 1;
    }

    // Zameryaem vremya vypolneniya
    auto start  = std::chrono::high_resolution_clock::now();
    int  result = josephus(n, k);
    auto end    = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Answer: " << result << std::endl;
    std::cout << "Time:   " << elapsed.count() << " sec" << std::endl;

    return 0;
}
