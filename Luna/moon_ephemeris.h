#pragma once
#include <string>
#include <vector>

// One record from the .dat file
struct MoonRecord {
    int    ymd;    // date YYYYMMDD
    int    hms;    // time HHMMSS
    double t;      // time in fractional hours
    double r;      // range to Moon in km
    double el;     // elevation angle (degrees)
    double az;     // azimuth (degrees)
    double fi;     // Moon latitude (degrees)
    double lg;     // Moon longitude (degrees)
};

// Result of computation for one date
struct MoonEvents {
    bool   riseFound;
    bool   culminFound;
    bool   setFound;
    int    riseHMS;
    int    culminHMS;
    int    setHMS;
};

// Build the path to the .dat file for the given year
std::string buildFilePath(const std::string& dataDir, int year);

// Parse a date string "dd.mm.yyyy" into day, month, year
bool parseDate(const std::string& input, int& day, int& month, int& year);

// Load all records for the given date (YYYYMMDD) from the file
// Returns false if file not found or no records for that date
bool loadDayRecords(const std::string& filePath, int ymd,
                    std::vector<MoonRecord>& records);

// Find rise, culmination, and set from a list of records
MoonEvents findEvents(const std::vector<MoonRecord>& records);

// Format an HMS integer (HHMMSS) as "hh:mm:ss"
std::string formatHMS(int hms);
