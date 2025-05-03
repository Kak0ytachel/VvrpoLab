#include "jsonserializer.h"
#pragma once

void JsonSerializer::serialize_string(string key,  string value) {
        this->add_comma();
        string s = "\"" + key + "\": \"" + value + "\"";
        this->result.insert(this->insert_index, s);
        this->insert_index += s.size();
    } 

void JsonSerializer::add_comma() {
    if (this->insert_index != 1) {
        this->result.insert(this->insert_index, ", ");
        this->insert_index += 2;
    }
}

void JsonSerializer::serialize_int(string key, int value) {
    this->serialize_string(key, to_string(value));
}

void JsonSerializer::serialize_dt(string key, Datetime value) {
    this->serialize_int(key, value.timestamp());
}

string JsonSerializer::get_result() {
    return this->result;
}

template <typename T>
void JsonSerializer::serialize_vector(string key, vector<T*> elements) {
    string s = "[";
    for (int i = 0; i < elements.size(); i++) {
        s += elements[i]->serialize();
        if (i != elements.size() - 1) {
            s += ", ";
        }
    }
    s += "]";
    this->add_comma();
    string s2 = "\"" + key + "\": " + s;
    this->result.insert(this->insert_index, s2);
    this->insert_index += s2.size();
}


