#ifndef DATETIME_H
#define DATETIME_H

class DateTime {
private:
    int year, month, day;
    int hour, minute, second;

public:
    DateTime();
    DateTime(int y, int m, int d, int h = 0, int min = 0, int s = 0);

    void input();

    void print1(); 
    void print2(); 
    void print3(); 

    bool isValid();

    int dayOfWeek();
    int difference(const DateTime& other);

    static DateTime easter(int year);
};

#endif