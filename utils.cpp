#include <iostream>
#include "utils.h"

int utils::getInt(int min_val, int max_val, string message) {
    cout << message;
    int value;
    cin >> value;
    
    cin.clear();
	cin.ignore(99999, '\n');
    if (min_val > value || value > max_val) {
        cout << "Wrong input. Please provide integer number in range [" << min_val << ", " << max_val << "]" << endl;
    } else {
        return value;
    }
    return utils::getInt(min_val, max_val, message);
    // todo: modify
}

string utils::getString(string message) {
    cout << message << endl;
    string result;
    // cin.ignore(INT_MAX, '\n');
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

string utils::centered(string s, int l) {
    if (s.size() >= l) {
        return s;
    }
    s = string((l - s.size()) / 2, ' ') + s + string((l - s.size()) / 2 + (l - s.size()) % 2, ' ');
    return s;
}

//template <typename T> // делкарация шаблона для использования функции input() как для int, так и для double
//
//void input(T& variable) { // функция ввода с проверкой целочисленных значений
//	bool startFlag = true; // инициализациия переменной начального флага
//	while (true) { // цикл пока не введено подходящее значение
//		cin >> variable; // ввод переменной по ее ссылке
//		if (!cin.fail()) {
//			break; // выход если нет ошибки
//		}
//		cout << "Error: wrong input, please try again" << endl; // вывод сообщения об ошибке
//		cin.clear(); // очистка флага ошибки буфера ввода
//		cin.ignore(99999, '\n'); // очистка буфера ввода
//	}
//}