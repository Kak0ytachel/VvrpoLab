#include <string>
#include <algorithm>
#include "datetime.h"
using namespace std;

#pragma once

class BusRoute;
class Ticket;

namespace utils{
    int getInt(int min_val, int max_val, string message); // ввод целого числа

    string getString(string message); // ввод строки

    Datetime getDate(string message); // ввод даты и времени 

    double getDouble(string message, int precision); // ввод вещественного числа

    string encrypt(string pass); // шифрования пароля

    string centered(string s, int l); // центрирование строки для таблицы

    void showBuses(vector<BusRoute*> buses); // вывод таблицы маршрутов

    void showTickets(vector<Ticket*> tickets); // вывод таблицы билетов

    string from_double(double value, int precision); // пробразование из вещественного числа в строку с заданной точностью

    string to_lower(string s); // преобразует строку к нижнему регистру
}