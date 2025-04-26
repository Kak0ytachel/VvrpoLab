#include <string>
#include <map>
#include <vector>
#include "datetime.h"
#pragma once


class JsonDeserializer {
public:
    std::string input;
    std::map<std::string, std::string> dict;

    JsonDeserializer(std::string input);

    std::string deserialize_string(std::string key);

    int deserialize_int(std::string key);

    Datetime deserialize_dt(std::string key);

    template<typename T>
    std::vector<T> deserialize_vector(std::string key);
};