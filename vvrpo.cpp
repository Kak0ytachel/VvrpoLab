#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <map>
#include "datetime.cpp"
#include "jsonserializer.cpp"
#include "jsondeserializer.cpp"
#include "ticket.cpp"
#include "utils.cpp"
#include "consoleapp.cpp"

using namespace std;

class User;
class BusRoute;
class ConsoleApp;


ConsoleApp app = ConsoleApp("test.data");

class User {
    string login;
    string salted_password;
    string name;
    vector<Ticket> tickets;
public:
    User(string name, string login, string password) {
    // TODO encrypt password
        this->login = login;
        this->name = name;
        this->salted_password = app.encrypt(password);
    }

    virtual void main() {
        cout << "Logged in as user " << this->login << endl;
        cout << "Menu: \n1. View all tickets\n2. Buy ticket\n3. View booked tickets\n4. Cancel ticket\n5. Log out" << endl;
        int e = utils::getInt(1, 3, "Choose menu option");
        bool exitFlag = false;
        while (!exitFlag) {
            switch (e) {
                case 1: {
                    this->see_tickets();
                    break;
                }
                case 2: {
                    this->buy_ticket();
                    break;
                }
                case 3: {
                    this->check_booked_tickets();
                    break;
                }
                case 4: {
                    this->cancel_ticket();
                    break;
                }
                case 5: {
                    cout << "Logging out..." << endl;
                    exitFlag = true;
                    break;
                }
            }
        }
    }

    void see_tickets() {

    }

    void buy_ticket() {

    }

    void check_booked_tickets() {

    }

    void cancel_ticket() {

    }

    string serialize() {
        string s = "{\"login\": \"" + this->login + "\", \"salted_password\": \"" + this->salted_password + "\", \"name\": \n" + this->name + "\n}";
        // todo: add tickets
        return s;
    }

    User(string data) {
        int start = data.find_first_of('{');
        for (int i = start; i < data.size(); i++) {
            int code = data[i];
            
        }
    }

    virtual bool is_admin() {
        return false;
    }

    bool check_credentials(string login, string salted_password) {
        return (login == this->login && salted_password == this->salted_password);
    } 
};


class Administrator: public User {
public: 
    Administrator(string name, string login, string password): User(name, login, password){

    }

    void create_user() {

    }

    virtual void main() {
        cout << "Admin" << endl;
    }

    virtual bool is_admin() {
        return true;
    }
};



int main() {
    JsonSerializer serializer = JsonSerializer();
    serializer.serialize_int("age", 10);
    serializer.serialize_string("name", "Mike");
    string result = serializer.get_result();
    cout << result << endl;
    JsonDeserializer deserializer = JsonDeserializer(result);
    cout << deserializer.deserialize_int("age") << endl;
    cout << deserializer.deserialize_string("name") << endl;
    // int a = deserializer.deserialize_vector<int>();
    cout << "Hi";
    // cout << a;


    // Administrator admin = Administrator();
    // admin.main();
    // vector<User*> v;
    // v.push_back(new User("", "", ""));
    // v.push_back(new Administrator());
    // for (int i = 0; i < v.size(); i++) {
    //     v[i]->main();
    // }
}