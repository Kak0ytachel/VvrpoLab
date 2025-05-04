#include <iostream>
#include "jsondeserializer.h"
#include "administrator.h"
#pragma once
using namespace std;

JsonDeserializer::JsonDeserializer(string input): input(input) {
    // cout << "New deserializer" << endl;
    // cout << "input string is " << input << endl;
    int start = input.find_first_of('{');
    int i = start;
    while (i < input.size() - 1) {
        // cout << "cycle 1, i = " << i << endl;
        int a = input.find('"', i);
        int b = input.find('"', a + 1);
        string key = input.substr(a+1, b-a-1);
        string value;
        // cout << "key = " << key << endl;
        // "bcde"
        // 012345
        // ^    ^
        // 0+1, 5-0-1
        int c = input.find(':', b + 1);
        i = c;
        int d;
        int e;
        while (true) {
            // cout << "cycle 2, s[i] = " << input[i] << ", i=" << i << endl;
            if (i == -1) {
                return;
            }
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
                    // cout << "cycle 3, input[i] = " << input[i] << endl;
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
                    i++;
                    if (square_braces == 0 && curly_bracets == 0 && quotes == 0) {
                        break;
                    }
                }
                e = i;
                value = input.substr(d, e - d);
                break;
            } else {
                i++;
            }
        }
        // cout << "value = " << value << endl;
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

    // cout << "Done deserializing" << endl;
    // for(auto const &ent : dict) {
    //     cout << ent.first << ": " << ent.second << endl;
    // }
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

double JsonDeserializer::deserialize_double(string key) {
    double d = stod(deserialize_string(key));
    return d;
}

vector<User*> JsonDeserializer::deserialize_user_vector(string key) {
    string s = this->dict[key];
    vector<User*> values;
    int start = s.find_first_of('[');
    int finish = s.find_last_of(']');
    int i = start + 1;
    while (i < finish) {
        // cout << "des_u_v | i = " << i << ", s[i] = " << s[i] << endl; 
        while (s[i] == ' ') {
            i++;
        }
        if (s[i] == ',') {
            i++;
            continue;
        }
        int a = i;
        int square_braces = 0;
        int curly_bracets = 0;
        int quotes = 0;
        while (true) {
            if (s[i] == '[') {
                square_braces++;
            } else if (s[i] == ']') {
                square_braces--;
            } else if (s[i] == '{') {
                curly_bracets++;
            } else if (s[i] == '}') {
                curly_bracets--;
            } else if (s[i] == '"') {
                quotes = 1 - quotes;
            }
            if (square_braces == 0 && curly_bracets == 0 && quotes == 0) {
                // cout << "des_u_v breaking at i = " << i << ", s[i] = " << s[i] << endl;
                break;
            }
            i++;
        }
        int b = i;
        string element = s.substr(a, b - a + 1);

        JsonDeserializer deserializer = JsonDeserializer(element);
        int is_admin = deserializer.deserialize_int("is_admin");
        if (is_admin == 1) {
            Administrator *t = new Administrator(element);
            values.push_back(t);
        } else {
            User *t = new User(element);
            values.push_back(t);
        }
        
        i++;
    }
    return values;
}

template<typename T>
vector<T*> JsonDeserializer::deserialize_vector(string key) {
    string s = this->dict[key];
    vector<T*> values;
    int start = s.find_first_of('[');
    int finish = s.find_last_of(']');
    int i = start + 1;
    while (i < finish) {
        while (s[i] == ' ') {
            i++;
        }
        if (s[i] == ',') {
            i++;
            continue;
        }
        int a = i;
        int square_braces = 0;
        int curly_bracets = 0;
        int quotes = 0;
        while (true) {
            if (s[i] == '[') {
                square_braces++;
            } else if (s[i] == ']') {
                square_braces--;
            } else if (s[i] == '{') {
                curly_bracets++;
            } else if (s[i] == '}') {
                curly_bracets--;
            } else if (s[i] == '"') {
                quotes = 1 - quotes;
            }
            if (square_braces == 0 && curly_bracets == 0 && quotes == 0) {
                break;
            }
            i++;
        }
        int b = i;
        string element = s.substr(a, b - a + 1);
        // cout << "Vector element json string: " << element << endl;
        T *t = new T(element);
        values.push_back(t);
        i++;
    }
    return values;
}