#include <iostream>
#include <fstream>

using namespace std;

const string FILE_NAME = "tsp.txt";

// the position of the city <x, y>
typedef pair<double double> city;


vector<city> make_cities() {

    vector<city> cities;

    ifstream file;
    file.open(file_name, ios::in);
    string buf;

    int city_num;
    if (!file.eof()) {
        getline(file, buf);
        city_num = stoi(buf);
    }

    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            double x = stod(buf.substr(0, buf.find(" ")));
            buf = buf.substr(buf.find(" ") + 1);
            double y = stod(buf.substr(0, buf.find(" ")));
    }

}

int main() {

}


