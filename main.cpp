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
    app = new ConsoleApp("data.json");
    app->run();
}