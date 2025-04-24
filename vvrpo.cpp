#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <map>
#include "datetime.cpp"
#include "jsonserializer.cpp"
#include "jsondeserializer.cpp"
using namespace std;

class User;
class BusRoute;
class ConsoleApp;
class Ticket;

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

class ConsoleApp {
    vector<User*> users;
    vector<BusRoute*> buses;
    int next_route_id = 1001;
    string filename;
public:    
    ConsoleApp(string filename): filename(filename) {
        bool flag = this->get_data();
        if (!flag) {
            cout << "Unable to read data file" << endl;
            this->filename = "data.dat";
        }
    }

    string encrypt(string pass) {
        return pass;
        // TODO replace
    }

    // BusRoute* get_bus(int route_id) {
    //     // for (int i = 0; i < this->buses.size(); i++) {
    //     //     if (this->buses[i]->routeId == route_id) {
    //     //         return this->buses[i];
    //     //     }
    //     // }
    // }
    
    void load_file() {
        
    }

    bool get_data() {
        ifstream fin;
        fin.open(this->filename);
        if (fin.is_open()) {
            string line;
            getline(fin, line);
            // TODO

            return true;
        } else {
            return false;
        }

    }

    void save_data() {
        ofstream fout;
        fout.open(this->filename);
        
    }

    void run() {
        string login = getString("Enter login");
        string password = getString("Enter password");
        string salted_password = this->encrypt(password);
        // User *user = nullptr;
        // for (int i = 0; i < this->users.size(); i++) {
        //     if (this->users[i]->check_credentials(login, salted_password)) {
        //         user = this->users[i];
        //     }
        // }
        // user->main();
    }


    int create_unique_route_id() {
        return this->next_route_id++;
    }

    void add_route(BusRoute *bus) {
        this->buses.push_back(bus);
    }

    // string serialize() {
    //     // JsonSerializer serializer = JsonSerializer();
    //     // serializer.serialize_vector<User>("users", users);
    //     // serializer.serialize_vector
    // }
};
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
        int e = getInt(1, 3, "Choose menu option");
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


class Ticket{
public:
    int routeId;
    int quantity;
    int is_canceled = 0;

    Ticket(int routeId, int quantity): routeId(routeId), quantity(quantity) {}

    void cancel() {
        // this->get_bus();
        this->is_canceled = 1;
    }

    // BusRoute* get_bus() {
    //     return app.get_bus(this->routeId);
    // }

    string serialize() {
        JsonSerializer serializer = JsonSerializer();
        serializer.serialize_int("routeId", this->routeId);
        serializer.serialize_int("quantity", this->quantity);
        serializer.serialize_int("is_canceled", this->is_canceled);
        return serializer.get_result();
    }

    Ticket(string json) {
        JsonDeserializer deserializer = JsonDeserializer(json);
        this->routeId = deserializer.deserialize_int("routeId");
        this->quantity = deserializer.deserialize_int("quantity");
        this->is_canceled = deserializer.deserialize_int("is_canceled");
    }

};

class BusRoute{
public:
    string origin;
    string destination;
    Datetime departure;
    Datetime arrival;
    int seatsTotal;
    int ticketsLeft;
    int routeId;

    BusRoute(string origin, string destination, Datetime departure, Datetime arrival, int tickets): 
        origin(origin), destination(destination), departure(departure), arrival(arrival), seatsTotal(tickets), ticketsLeft(tickets)  {
        
        this->routeId = app.create_unique_route_id();
        app.add_route(this);
    }

    Ticket buy_ticket(int quantity) {
        if (quantity >= this->ticketsLeft) {
            this->ticketsLeft -= quantity;
            return Ticket(this->routeId, quantity);
        } else {
            return Ticket(this->routeId, 0);
        }
    }

    void cancel_ticket(Ticket t) {
        if (t.routeId == this->routeId) {
            if (t.is_canceled == 0) {
                this->ticketsLeft += t.quantity;
            }
        }
    }

    string serialize() {
        JsonSerializer serializer = JsonSerializer();
        serializer.serialize_string("origin", this->origin);
        serializer.serialize_string("destination", this->destination);
        serializer.serialize_dt("departure", this->departure);
        serializer.serialize_dt("arrival", this->arrival);
        serializer.serialize_int("seatsTotal", this->seatsTotal);
        serializer.serialize_int("ticketsLeft", this->ticketsLeft);
        serializer.serialize_int("routeId", this->routeId);
        return serializer.get_result();
    }

    BusRoute(string json) {
        JsonDeserializer deserializer = JsonDeserializer(json);
        this->origin = deserializer.deserialize_string("origin");
        this->destination = deserializer.deserialize_string("destination");
        this->departure = deserializer.deserialize_dt("departure");
        this->arrival = deserializer.deserialize_dt("arrival");
        this->seatsTotal = deserializer.deserialize_int("seatsTotal");
        this->ticketsLeft = deserializer.deserialize_int("ticketsLeft");
        this->routeId = deserializer.deserialize_int("routeId");
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