#include <string>
#include "datetime.h"
using namespace std;

namespace utils{
    int getInt(int min_val, int max_val, string message);

    string getString(string message);

    Datetime getDate(string message);

    string encrypt(string pass);
}