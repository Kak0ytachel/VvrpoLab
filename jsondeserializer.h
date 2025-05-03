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

    JsonDeserializer(string input);

    string deserialize_string(string key);

    int deserialize_int(string key);

    Datetime deserialize_dt(string key);

    double deserialize_double(string key);

    template<typename T>
    vector<T*> deserialize_vector(string key);

    vector<User*> deserialize_user_vector(string key);
};