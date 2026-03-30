#include "DateTime.h"
#include <iostream>
#include <cmath>
using namespace std;

DateTime::DateTime() {
    year = 2000;
    month = 1;
    day = 1;
    hour = minute = second = 0;
}

DateTime::DateTime(int y, int m, int d, int h, int min, int s) {
    year = y;
    month = m;
    day = d;
    hour = h;
    minute = min;
    second = s;
}

void DateTime::input() {
    cin >> year >> month >> day >> hour >> minute >> second;
}

void DateTime::print1() {
    cout << day << "." << month << "." << year << endl;
}

void DateTime::print2() {
    const char* months[] = {
        "", "€нвар€","феврал€","марта","апрел€","ма€","июн€",
        "июл€","августа","сент€бр€","окт€бр€","но€бр€","декабр€"
    };

    cout << day << " " << months[month] << " " << year << endl;
}

void DateTime::print3() {
    cout << day << "." << month << "." << (year % 100) << endl;
}

bool DateTime::isValid() {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    return true;
}

int DateTime::dayOfWeek() {
    int y = year;
    int m = month;

    if (m < 3) {
        m += 12;
        y--;
    }

    int k = y % 100;
    int j = y / 100;

    int h = (day + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return h;
}

int DateTime::difference(const DateTime& other) {
    int days1 = year * 365 + month * 30 + day;
    int days2 = other.year * 365 + other.month * 30 + other.day;
    return abs(days1 - days2);
}

DateTime DateTime::easter(int Y) {
    int a = Y % 19;
    int b = Y / 100;
    int c = Y % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;

    int month = (h + l - 7 * m + 114) / 31;
    int day = ((h + l - 7 * m + 114) % 31) + 1;

    return DateTime(Y, month, day);
}