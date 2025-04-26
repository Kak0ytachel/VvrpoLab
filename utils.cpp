#include <iostream>
#include "utils.h"

int utils::getInt(int min_val, int max_val, string message) {
    cout << message << endl;
    int value;
    cin >> value;
    return value;
    // todo: modify
}

string utils::getString(string message) {
    cout << message << endl;
    string result;
    cin.ignore(INT_MAX, '\n');
    getline(cin, result);
    return result;
    // todo: modify
}

Datetime utils::getDate(string message) {
    cout << message << endl;
    int d = utils::getInt(1, 31, "Enter day: ");
    int m = utils::getInt(1, 12, "Enter month: ");
    int y = utils::getInt(1, 9999, "Enter year: ");
    int h = utils::getInt(0, 23, "Enter hour: ");
    int mm = utils::getInt(0, 59, "Enter minute: ");
    Datetime dt = Datetime(d, m, y, h, mm);
    return dt;
}

string utils::encrypt(string pass) {
    return pass;
}