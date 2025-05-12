#include <string>
#pragma once

class Datetime{
public:
    int hour;
    int minute;
    int day;
    int month;
    int year;

    Datetime(int d, int mo, int y, int h, int mi);  // стандартная инициализация

    Datetime(int ts); // инициализация при дересериализации

    Datetime(); // инициализация без аргументов

    int timestamp(); // преобразование в UTC timestamp

    bool is_leap_year(); // является ли год високосным

    static bool is_leap_year(int year) { // является ли год високосным (статическая)
        if (year % 400 == 0) {
            return true;
        }
        if (year % 100 == 0) {
            return false;
        }
        if (year % 4 == 0) {
            return true;
        }
        return false;
    }

    std::string format_dt(); // форматирование даты и времени

    std::string format_d(); // форматирование даты и времени

    std::string format_t(); // форматирование даты и времени
};
