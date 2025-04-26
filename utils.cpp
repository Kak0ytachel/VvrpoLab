#include <iostream>
#include <string>
#include "datetime.h"
#include "utils.h"

using namespace std;


int getInt(int min_val, int max_val, string message) {
    cout << message << endl;
    int value;
    cin >> value;
    return value;
    // todo: modify
}

string getString(string message) {
    cout << message << endl;
    string result;
    cin.ignore(INT_MAX, '\n');
    getline(cin, result);
    return result;
    // todo: modify
}

Datetime getDate(string message) {
    cout << message << endl;
    int d = getInt(1, 31, "Enter day: ");
    int m = getInt(1, 12, "Enter month: ");
    int y = getInt(1, 9999, "Enter year: ");
    int h = getInt(0, 23, "Enter hour: ");
    int mm = getInt(0, 59, "Enter minute: ");
    Datetime dt = Datetime(d, m, y, h, mm);
    return dt;
}
