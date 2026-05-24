#define _CRT_SECURE_NO_WARNINGS
#include "moon_ephemeris.h"

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

int main(int argc, char* argv[]) {
    std::string dateStr;
    std::string dataDir;

    // If arguments provided - use them, otherwise ask interactively
    if (argc >= 2) {
        dateStr = argv[1];
        dataDir = (argc >= 3) ? argv[2] : ".";
    }
    else {
        std::cout << "Enter date (dd.mm.yyyy): ";
        std::cin >> dateStr;

        std::cout << "Enter path to data folder (or press Enter for current folder): ";
        std::cin.ignore();
        std::getline(std::cin, dataDir);
        if (dataDir.empty()) dataDir = ".";
    }

    int day, month, year;
    if (!parseDate(dateStr, day, month, year)) {
        std::cerr << "Error: invalid date format. Expected dd.mm.yyyy\n";
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    int ymd = year * 10000 + month * 100 + day;
    std::string filePath = buildFilePath(dataDir, year);

    std::vector<MoonRecord> records;
    if (!loadDayRecords(filePath, ymd, records)) {
        std::cerr << "Error: no data for " << dateStr
            << " in file " << filePath << "\n";
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    MoonEvents ev = findEvents(records);

    std::printf("\nDate:         %s\n", dateStr.c_str());

    if (ev.riseFound)
        std::printf("Moonrise:     %s\n", formatHMS(ev.riseHMS).c_str());
    else
        std::printf("Moonrise:     not found (Moon above horizon all day)\n");

    if (ev.culminFound)
        std::printf("Culmination:  %s\n", formatHMS(ev.culminHMS).c_str());
    else
        std::printf("Culmination:  not found\n");

    if (ev.setFound)
        std::printf("Moonset:      %s\n", formatHMS(ev.setHMS).c_str());
    else
        std::printf("Moonset:      not found (Moon below horizon all day)\n");

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}