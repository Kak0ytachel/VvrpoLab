#include <iostream>
#include "jsondeserializer.h"
#pragma once
using namespace std;

JsonDeserializer::JsonDeserializer(string input): input(input) {
    int start = input.find_first_of('{');
    int i = start;
    while (true) {
        cout << "cycle 1, i = " << i << endl;
        int a = input.find('"', i);
        int b = input.find('"', a + 1);
        string key = input.substr(a+1, b-a-1);
        string value;
        cout << "key = " << key << endl;
        // "bcde"
        // 012345
        // ^    ^
        // 0+1, 5-0-1
        int c = input.find(':', b + 1);
        i = c;
        int d;
        int e;
        while (true) {
            cout << "cycle 2, s[i] = " << input[i] << endl;
            if (input[i] == '"') {
                d = i;
                e = input.find('"', i + 1);
                i = e + 1;
                value = input.substr(d + 1, e - d - 1);
                break;
            } else if (input[i] == '[' || input[i] == '{') {
                d = i;
                int square_braces = 0;
                int curly_bracets = 0;
                int quotes = 0;
                while (true) {
                    cout << "cycle 3, input[i] = " << input[i] << endl;
                    if (input[i] == '[') {
                        square_braces++;
                    } else if (input[i] == ']') {
                        square_braces--;
                    } else if (input[i] == '{') {
                        curly_bracets++;
                    } else if (input[i] == '}') {
                        curly_bracets--;
                    } else if (input[i] == '"') {
                        quotes = 1 - quotes;
                    }
                    if (square_braces == 0 && curly_bracets == 0 && quotes == 0) {
                        break;
                    }
                    i++;
                }
                e = i;
                value = input.substr(d, e - d);
                break;
            } else {
                i++;
            }
        }
        cout << "value = " << value << endl;
        this->dict[key] = value;
        while (input[i] == ' ') {
            i++;
        }
        if (input[i] == '}') {
            break;
        }
        if (input[i] == ',') {
            i++;
            continue;
        }
    }
}

string JsonDeserializer::deserialize_string(string key) {
    return this->dict[key];
}

int JsonDeserializer::deserialize_int(string key) {
    int a = stoi(deserialize_string(key));
    return a;
}

Datetime JsonDeserializer::deserialize_dt(string key) {
    Datetime dt = Datetime(deserialize_int(key));
    return dt;
}

template<typename T>
vector<T*> JsonDeserializer::deserialize_vector(string key) {
    string s = this->dict[key];
    vector<T*> values;
    int start = s.find_first_of('[');
    int finish = s.find_last_of(']');
    int i = start;
    while (true) {
        if (s[i] == ' ') {
            i++;
            continue;
        }
        int a = 0;
        int square_braces = 0;
        int curly_bracets = 0;
        int quotes = 0;
        while (true) {
            if (input[i] == '[') {
                square_braces++;
            } else if (input[i] == ']') {
                square_braces--;
            } else if (input[i] == '{') {
                curly_bracets++;
            } else if (input[i] == '}') {
                curly_bracets--;
            } else if (input[i] == '"') {
                quotes = 1 - quotes;
            }
            if (square_braces == 0 && curly_bracets == 0 && quotes == 0) {
                break;
            }
            i++;
        }
        int b = i;
        string element = s.substr(a, b - a + 1);
        T *t = new T(element);
        values.push_back(t);
        i++;
        while (s[i] == ' ') {
            i++;
        }
        if (s[i] == ',') {
            continue;
        }
        if (s[i] == ']') {
            break;
        }
    }
    return values;
}