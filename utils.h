#include <string>
#include "datetime.h"
#pragma once

using namespace std;

namespace utils{
    int getInt(int min_val, int max_val, string message);

    string getString(string message);

    Datetime getDate(string message);
}

