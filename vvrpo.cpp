#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <map>
using namespace std;

class User;
class BusRoute;
class ConsoleApp;
class Ticket;
class Datetime;
class JsonSerializer;
class JsonDeserializer;

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

class Datetime {
public:
    int hour;
    int minute;
    int day;
    int month;
    int year;

    Datetime(int d, int mo, int y, int h, int mi) {
        this->day = d;
        this->month = mo;
        this->year = y;
        this->minute = mi;
        this->hour = h;
    }

    Datetime (int ts) {
        this->year = 1970;
        this->month = 1;
        this->day = 1;
        this->hour = 0;
        this->minute = 0;

        while (true) {
            int days = (this->is_leap_year())? 366: 365;
            if (ts > days * 24 * 60 * 60) {
                this->year += 1;
                ts -= days * 24 * 60 * 60;
            } else {
                break;
            }
        }
        while (true) {
            int days = (this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 
            || this->month == 8 || this->month == 10 || this->month == 12)? 31: 30;
            if (ts > days * 24 * 60 * 60) {
                this->month += 1;
                ts -= days * 25 * 60 * 60;
            } else {
                break;
            }
        }
        this->day += ts / (24 * 60 * 60);
        ts = ts % (24 * 60 * 60);
        this->hour = ts / 3600;
        ts = ts % 3600;
        this->minute = ts / 60;
    }

    Datetime(): Datetime(0) {}

    int timestamp() {
        int result = 0;
        if (this->year >= 1970) {
            for (int y = 1970; y < this->year; y++) {
                result += (this->is_leap_year(y)? 366: 365) * 24 * 60 * 60;
            }
        } else {
            for (int y = this->year; y < 1970; y++) {
                result -= (this->is_leap_year(y)? 366: 365) * 24 * 60 * 60;
            }
        }
        for (int m = 1; m < this->month; m++) {
            if (m == 1 || m == 3 || m == 5 || m == 7 || m || m == 8 || m == 10 || m == 12) {
                result += 31 * 24 * 60 * 60;
            } else {
                result += 30 * 24 * 60 * 60;
            }
        }
        result += (this->day - 1) * 24 * 60 * 60;
        result += this->hour * 60 * 60;
        result += this->minute * 60;
        return result;
    }

    bool is_leap_year() {
        return this->is_leap_year(this->year);
    } 

    static bool is_leap_year(int year) {
        if (year % 400 == 0) {
            return true;
        }
        if (year % 100 == 0) {
            return false;
        }
        if (year % 4 == 0) {
            return true;
        }
        return false;
    }
};

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

    BusRoute* get_bus(int route_id) {
        // for (int i = 0; i < this->buses.size(); i++) {
        //     if (this->buses[i]->routeId == route_id) {
        //         return this->buses[i];
        //     }
        // }
    }
    
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

    string serialize() {
        // JsonSerializer serializer = JsonSerializer();
        // serializer.serialize_vector<User>("users", users);
        // serializer.serialize_vector
    }
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

class JsonSerializer {
public:
    string result = "{}";
    int insert_index = 1;

    void add_comma() {
        if (this->insert_index != 1) {
            this->result.insert(this->insert_index, ", ");
            this->insert_index += 2;
        }
    }

    void serialize_string(string key,  string value) {
        this->add_comma();
        string s = "\"" + key + "\": \"" + value + "\"";
        this->result.insert(this->insert_index, s);
        this->insert_index += s.size();
    } 

    void serialize_int(string key, int value) {
        this->serialize_string(key, to_string(value));
    }

    void serialize_dt(string key, Datetime value) {
        this->serialize_int(key, value.timestamp());
    }

    string get_result() {
        return this->result;
    }

    template <typename T>
    void serialize_vector(string key, vector<T*> elements) {
        string s = "[";
        for (int i = 0; i < elements.size(); i++) {
            s += elements[i]->serialize();
            if (i == elements.size() - 1) {
                s += ", ";
            }
        }
        s += "]";
        this->serialize_string(key, s);
    }
};

class JsonDeserializer {
public:
    string input;
    map<string, string> dict;
    

    JsonDeserializer(string input): input(input) {
        int start = input.find_first_of('{');
        int i = start;
        while (true) {
            cout << "cycle 1, i = " << i << endl;
            int a = input.find('"', i);
            int b = input.find('"', a + 1);
            string key = input.substr(a+1, b-a-1);
            string value;
            cout << "key = " << key << endl;
            // "bcde"
            // 012345
            // ^    ^
            // 0+1, 5-0-1
            int c = input.find(':', b + 1);
            i = c;
            int d;
            int e;
            while (true) {
                cout << "cycle 2, s[i] = " << input[i] << endl;
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
                        cout << "cycle 3, input[i] = " << input[i] << endl;
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
                        if (square_braces == 0 && curly_bracets == 0 && quotes == 0) {
                            break;
                        }
                        i++;
                    }
                    e = i;
                    value = input.substr(d, e - d);
                    break;
                } else {
                    i++;
                }
            }
            cout << "value = " << value << endl;
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
    }

    string deserialize_string(string key) {
        return this->dict[key];
    }

    int deserialize_int(string key) {
        int a = stoi(deserialize_string(key));
        return a;
    }

    Datetime deserialize_dt(string key) {
        Datetime dt = Datetime(deserialize_int(key));
        return dt;
    }

    template<typename T>
    vector<T> deserialize_vector(string key) {
        string s = this->dict[key];
        vector<T> values;
        int start = s.find_first_of('[');
        int finish = s.find_last_of(']');
        int i = start;
        while (true) {
            if (s[i] == ' ') {
                i++;
                continue;
            }
            int a = 0;
            int square_braces = 0;
            int curly_bracets = 0;
            int quotes = 0;
            while (true) {
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
                if (square_braces == 0 && curly_bracets == 0 && quotes == 0) {
                    break;
                }
                i++;
            }
            int b = i;
            string element = s.substr(a, b - a + 1);
            T t = T(element);
            i++;
            while (s[i] == ' ') {
                i++;
            }
            if (s[i] == ',') {
                continue;
            }
            if (s[i] == ']') {
                break;
            }
        }
        return values;
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
        this->get_bus();
        this->is_canceled = 1;
    }

    BusRoute* get_bus() {
        return app.get_bus(this->routeId);
    }

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