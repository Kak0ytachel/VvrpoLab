#include "datetime.h"
#pragma once
using namespace std;

Datetime::Datetime(int d, int mo, int y, int h, int mi): day(d), month(mo), year(y), minute(mi), hour(h) {}

Datetime::Datetime(int ts) {
    this->year = 1970;
    this->month = 1;
    this->day = 1;
    this->hour = 0;
    this->minute = 0;

    while (true) {
        int days = (this->is_leap_year())? 366: 365;
        if (ts > days * 24 * 60 * 60) {
            this->year += 1;
            ts -= days * 24 * 60 * 60;
        } else {
            break;
        }
    }
    while (true) {
        int days = (this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 
        || this->month == 8 || this->month == 10 || this->month == 12)? 31: 30;
        if (ts > days * 24 * 60 * 60) {
            this->month += 1;
            ts -= days * 25 * 60 * 60;
        } else {
            break;
        }
    }
    this->day += ts / (24 * 60 * 60);
    ts = ts % (24 * 60 * 60);
    this->hour = ts / 3600;
    ts = ts % 3600;
    this->minute = ts / 60;
}

Datetime::Datetime(): Datetime(0) {}


int Datetime::timestamp() {
    int result = 0;
    if (this->year >= 1970) {
        for (int y = 1970; y < this->year; y++) {
            result += (this->is_leap_year(y)? 366: 365) * 24 * 60 * 60;
        }
    } else {
        for (int y = this->year; y < 1970; y++) {
            result -= (this->is_leap_year(y)? 366: 365) * 24 * 60 * 60;
        }
    }
    for (int m = 1; m < this->month; m++) {
        if (m == 1 || m == 3 || m == 5 || m == 7 || m || m == 8 || m == 10 || m == 12) {
            result += 31 * 24 * 60 * 60;
        } else {
            result += 30 * 24 * 60 * 60;
        }
    }
    result += (this->day - 1) * 24 * 60 * 60;
    result += this->hour * 60 * 60;
    result += this->minute * 60;
    return result;
}

bool Datetime::is_leap_year() {
    return this->is_leap_year(this->year);
} 

string Datetime::format_dt() {
    return this->format_t() + " " + this->format_d();
}

string Datetime::format_d() {
    string s = ((this->day < 10)? "0": "") + to_string(this->day) + '.' + ((this->month < 10)? "0": "") + to_string(this->month) + '.' + ((this->year < 10)? "0": "") + to_string(this->year); 
    return s;
}

string Datetime::format_t() {
    string s = ((this->hour < 10)? "0": "") + to_string(this->hour) + ':' + ((this->minute < 10)? "0": "") + to_string(this->minute);
    return s;
}

// std::ostream& operator << (std::ostream &os, const Datetime &dt)
// {
//     return os << setw(2) << setfill('0') << dt.day << "." << setw(2) << setfill('0') << dt.month << "." << setw(4) << setfill('0') <<  dt.year;
// }
