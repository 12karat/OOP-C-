#define _CRT_SECURE_NO_WARNINGS
#include "moon_ephemeris.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdio>

// Build path:  <dataDir>/moonYYYY.dat
std::string buildFilePath(const std::string& dataDir, int year) {
    char buf[64];
    if (dataDir.empty() || dataDir == ".") {
        std::snprintf(buf, sizeof(buf), "moon%d.dat", year);
    } else {
        std::snprintf(buf, sizeof(buf), "%s/moon%d.dat",
                      dataDir.c_str(), year);
    }
    return std::string(buf);
}

// Parse "dd.mm.yyyy"
bool parseDate(const std::string& input, int& day, int& month, int& year) {
    if (input.size() < 10) return false;
    // expect exactly dd.mm.yyyy
    char sep1, sep2;
    if (std::sscanf(input.c_str(), "%d%c%d%c%d",
                    &day, &sep1, &month, &sep2, &year) != 5) return false;
    if (sep1 != '.' || sep2 != '.') return false;
    if (day < 1 || day > 31)   return false;
    if (month < 1 || month > 12) return false;
    if (year < 1)               return false;
    return true;
}

// Read all records matching ymd from filePath.
// The file has a header line then whitespace-separated columns:
//   YMD  HMS  T  R  El  Az  FI  LG
bool loadDayRecords(const std::string& filePath, int ymd,
                    std::vector<MoonRecord>& records) {
    std::ifstream fin(filePath);
    if (!fin.is_open()) return false;

    std::string line;
    // skip header
    if (!std::getline(fin, line)) return false;

    while (std::getline(fin, line)) {
        // strip trailing \r
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty()) continue;

        MoonRecord rec;
        std::istringstream iss(line);
        if (!(iss >> rec.ymd >> rec.hms >> rec.t
                  >> rec.r >> rec.el >> rec.az
                  >> rec.fi >> rec.lg)) continue;

        if (rec.ymd == ymd)
            records.push_back(rec);
        else if (!records.empty())
            break; // dates are sorted, no need to read further
    }
    return !records.empty();
}

// Detect rise, culmination, set from sorted elevation data.
// Rise  : El crosses from negative to positive
// Culm  : maximum El
// Set   : El crosses from positive to negative
MoonEvents findEvents(const std::vector<MoonRecord>& records) {
    MoonEvents ev{};

    if (records.empty()) return ev;

    // --- culmination: record with maximum elevation ---
    auto maxIt = std::max_element(records.begin(), records.end(),
        [](const MoonRecord& a, const MoonRecord& b){
            return a.el < b.el;
        });
    ev.culminFound = true;
    ev.culminHMS   = maxIt->hms;

    // --- rise and set by sign change ---
    for (size_t i = 1; i < records.size(); ++i) {
        double prev = records[i-1].el;
        double curr = records[i].el;

        if (prev < 0.0 && curr >= 0.0 && !ev.riseFound) {
            // pick the record closer to zero
            ev.riseFound = true;
            ev.riseHMS   = (std::abs(curr) < std::abs(prev))
                            ? records[i].hms
                            : records[i-1].hms;
        }

        if (prev >= 0.0 && curr < 0.0 && !ev.setFound) {
            ev.setFound = true;
            ev.setHMS   = (std::abs(prev) < std::abs(curr))
                            ? records[i-1].hms
                            : records[i].hms;
        }
    }

    return ev;
}

// HHMMSS -> "hh:mm:ss"
std::string formatHMS(int hms) {
    int h = hms / 10000;
    int m = (hms / 100) % 100;
    int s = hms % 100;
    char buf[16];
    std::snprintf(buf, sizeof(buf), "%02d:%02d:%02d", h, m, s);
    return std::string(buf);
}
