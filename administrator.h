#include <string>
#include <iostream>
#include "user.h"
#pragma once

class Administrator: public User {
public: 
    Administrator(string name, string login, string password);

    void create_user();

    virtual void main() {
        cout << "Admin" << endl;
    }

    virtual bool is_admin() {
        return true;
    }
};
