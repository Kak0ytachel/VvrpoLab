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
#include "user.cpp"
#include "busroute.cpp"
#include "administrator.cpp"

using namespace std;

extern ConsoleApp *app;

int main() {
    // Administrator *a = new Administrator("Name", "Login", "Passw0rd");
    // cout << "a" << a->serialize() << endl;
    // vector<User*> users;
    // users.push_back(a);
    // cout << "us" << users[0]->serialize() << endl;

    // User *u = new User("Idk", "lol", "pw");
    // cout << u->serialize();
    // cout << "end" << endl;
    app = new ConsoleApp("data.json");
    // int po = utils::getInt(0, 5, "Idk: ");
    // JsonSerializer serializer = JsonSerializer();
    // serializer.serialize_int("age", 10);
    // serializer.serialize_string("name", "Mike");
    // string result = serializer.get_result();
    // cout << result << endl;
    // JsonDeserializer deserializer = JsonDeserializer(result);
    // cout << deserializer.deserialize_int("age") << endl;
    // cout << deserializer.deserialize_string("name") << endl;
    // int a = deserializer.deserialize_vector<int>();
    // cout << a;
    
    // BusRoute route = BusRoute("Minsk", "Grodno1", Datetime(0), Datetime(60), 25);
    // BusRoute route2 = BusRoute("Minsk", "Grodno2", Datetime(3600), Datetime(3660), 15);
    // cout << "Hi";
    // cout << route2.routeId;
    // cout << app->get_bus(1002)->origin << endl;
    // Ticket *t = route2.buy_ticket(2);
    // cout << t->get_bus()->destination;
    // app->users.push_back(a);
    // app->users.push_back(u);
    app->run();
    // Administrator admin = Administrator();
    // admin.main();
    // vector<User*> v;
    // v.push_back(new User("", "", ""));
    // v.push_back(new Administrator());
    // for (int i = 0; i < v.size(); i++) {
    //     v[i]->main();
    // }
}