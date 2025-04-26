#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <map>
#include "datetime.h"
#include "jsonserializer.h"
#include "jsondeserializer.h"
#include "ticket.h"
#include "user.h"
#include "busroute.h"
#include "administrator.h"
#include "consoleapp.h"
using namespace std;


ConsoleApp app = ConsoleApp("test.data");


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