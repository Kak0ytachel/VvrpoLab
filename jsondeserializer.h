#include <string>
#include <map>
#include <vector>
#include "datetime.cpp"

using namespace std;

class JsonDeserializer {
public:
    string input;
    map<string, string> dict;

    JsonDeserializer(string input);

    string deserialize_string(string key);

    int deserialize_int(string key);

    Datetime deserialize_dt(string key);

    template<typename T>
    vector<T> deserialize_vector(string key);
};