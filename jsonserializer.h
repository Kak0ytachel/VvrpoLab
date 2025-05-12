#include <string>
#include <vector>
#include "datetime.h"
#pragma once

using namespace std;

class JsonSerializer {
public:
    void serialize_string(string key,  string value); // сериализация строки

    void serialize_int(string key, int value); // сериализация целого числа

    void serialize_dt(string key, Datetime value); // сериализация даты и времени

    void serialize_double(string key, double value); // сериализация вещественного числа

    string get_result(); // получение результата

    template <typename T>
    void serialize_vector(string key, vector<T*> elements); // сериализация вектора

private:
    string result = "{}";
    int insert_index = 1;
    void add_comma(); // проверка и добавление запятой при необходимости

};