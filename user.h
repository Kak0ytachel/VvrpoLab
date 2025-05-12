#include <string>
#include <iostream>
#include <vector>
#include "utils.h"
#pragma once

using namespace std;

class Ticket;

class User {
public:
    string login;
    string salted_password;
    string name;
    vector<Ticket*> tickets;

    User(string name, string login, string password); // стандартная инициализация

    virtual void main() { // главное меню администратора
        cout << "Logged in as user " << this->name << endl;
        bool exitFlag = false;
        while (!exitFlag) {
            cout << "Menu: \n1. Browse bus routes\n2. View booked tickets\n3. Log out" << endl;
            int e = utils::getInt(1, 3, "Choose menu option: ");
            switch (e) {
                case 1: {
                    this->see_tickets();
                    break;
                }
                case 2: {
                    this->check_booked_tickets();
                    break;
                }
                case 3: {
                    cout << "Logging out..." << endl;
                    exitFlag = true;
                    break;
                }
            }
        }
    }

    void see_tickets(); // просмотреть билеты

    void check_booked_tickets(); // просмотреть заказанные билеты

    void buy_ticket(BusRoute *bus); // заказать билет

    string serialize(); // сериализовация

    User(string json); // инициализация при дересериализации

    virtual bool is_admin() { // проверка на класс администратора
        return false;
    }

    bool check_credentials(string login, string salted_password); // проверка логина и пароля
};