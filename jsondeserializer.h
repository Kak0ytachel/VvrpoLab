#include <string>
#include <map>
#include <vector>
#include "datetime.h"
#include "user.h"
using namespace std;
#pragma once


class JsonDeserializer {
public:
    string input;
    map<string, string> dict;

    JsonDeserializer(string input); // конструктор

    string deserialize_string(string key); // десерелизация строки

    int deserialize_int(string key); // десерелизация целого числа

    Datetime deserialize_dt(string key); // десерелизация Datetime

    double deserialize_double(string key); // десерелизация вещественного числа

    template<typename T>
    vector<T*> deserialize_vector(string key); // десерелизация вектора

    vector<User*> deserialize_user_vector(string key); // десерелизация вектора пользователей или админов
};