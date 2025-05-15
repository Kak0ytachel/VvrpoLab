#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "utils.h"
#include "ticket.h"
#include "busroute.h"

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

double utils::getDouble(string message, int precision) {
    cout << message;
    double value;
    cin >> value;
    double multiplier = pow(10.0, precision);
    value = ceil(value * multiplier) / multiplier;
    return value;
}

string utils::encrypt(string pass) {
    for (int i = 0; i < pass.size(); i++) {
        if (pass[i] >= '0' && pass[i] <= '9') {
            pass[i] = 105 - pass[i];
        } else {
            if (i % 2 == 0 && pass[i] >= 'a' && pass[i] <= 'z' && pass[i] % 2 == 0) {
                pass[i] = pass[i] - 32;
            } else if (i % 2 == 1 && pass[i] >= 'A' && pass[i] <= 'Z' && pass[i] % 3 != 0) {
                pass[i] = pass[i] + 32;
            }
            pass[i] = pass[i] + 3;
            if (pass[i] == '\\') {
                pass[i] = '^';
            }
            if (pass[i] == '"') {
                pass[i] = 'a';
            }
            if (pass[i] == '{' || pass[i] == '}'  || pass[i] == ']'){
                pass[i] = '&';
            }
            if (pass[i] == '[') {
                pass[i] = '7';
            }
        }
    }
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

void utils::showBuses(vector<BusRoute*> buses) {
    cout << " No. |" << utils::centered("Origin", 12) << "|" << utils::centered("Departure", 12) << "|" << utils::centered("Destination", 12) << "|" << 
        utils::centered("Arrival", 12) << "|" << utils::centered("Tickets", 10) << "|" << utils::centered("Price", 10) << endl;
    for (int i = 0; i < buses.size(); i++) {
        BusRoute *bus = buses[i];
        cout << utils::centered(to_string(i+1) + ".", 5) << "|" << utils::centered(bus->origin, 12) << "|" << utils::centered(bus->departure.format_t(), 12) 
            << "|" << utils::centered(bus->destination, 12) << "|" << utils::centered(bus->arrival.format_t(), 12) << "|" <<
            utils::centered(to_string(bus->ticketsLeft), 10) << "|" << utils::centered(utils::from_double(bus->price, 2), 10) << endl;
    }
}

void utils::showTickets(vector<Ticket*> tickets) {
    cout << " No. |" << utils::centered("Origin", 12) << "|" << utils::centered("Departure", 12) << "|" << utils::centered("Destination", 12) << "|" << 
        utils::centered("Arrival", 12) << "|" << utils::centered("Tickets", 10) << "|" << utils::centered("Price", 10) << endl;
    for (int i = 0; i < tickets.size(); i++) {
        BusRoute *bus = tickets[i]->get_bus();
        cout << utils::centered(to_string(i+1) + ".", 5) << "|" << utils::centered(bus->origin, 12) << "|" << utils::centered(bus->departure.format_t(), 12) 
            << "|" << utils::centered(bus->destination, 12) << "|" << utils::centered(bus->arrival.format_t(), 12) << "|" <<
            utils::centered(to_string(tickets[i]->quantity), 10) << "|" << utils::centered(utils::from_double(bus->price, 2), 10) << endl;
    }
}

string utils::from_double(double value, int precision) {
    ostringstream s;  
    s << setprecision(precision) << value; 
    return s.str(); 
}

string utils::to_lower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}