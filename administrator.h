#include <string>
#include <iostream>
#include "user.h"
#pragma once

class Administrator: public User {
public: 
    Administrator(string name, string login, string password);

    void manage_users();

    void manage_buses();

    virtual void main() {
        cout << "Admin" << endl;
    }

    virtual bool is_admin() {
        return true;
    }

    string serialize();

    Administrator(string json);
};
