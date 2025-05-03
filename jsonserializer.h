#include <string>
#include <vector>
#include "datetime.h"
#pragma once

using namespace std;

class JsonSerializer {
public:
    void serialize_string(string key,  string value);

    void serialize_int(string key, int value);

    void serialize_dt(string key, Datetime value);

    void serialize_double(string key, double value);

    string get_result();

    template <typename T>
    void serialize_vector(string key, vector<T*> elements);

private:
    string result = "{}";
    int insert_index = 1;
    void add_comma();

};