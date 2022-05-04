#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;
const int INF = 1000000;

const string FILE_NAME = "tsp.txt";

// the position of the city <x, y>
typedef pair<double, double> city;

int count_num_of_1bit(int n) {
    bitset<100> bs(n);
    return bs.count();
}

vector<int> make_1bit_indices(int n) {
    bitset<100> bs(n);
    vector<int> indices;
    for (int i=0; i<100; i++) {
        if (bs[i]) indices.push_back(i);
    }
    return indices;
}

vector<city> make_cities() {

    vector<city> cities;

    ifstream file;
    file.open(FILE_NAME, ios::in);
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
            cities.push_back(make_pair(x, y));
        }
    }

    file.close();

    return cities;

}

int main() {
    vector<city> cities = make_cities();
    int n = cities.size();

    vector<vector<double> > A((1 << n), vector<double>(n, INF));
    vector<vector<double> > c(n, vector<double>(n));

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i == j) c[i][j] = 0;
            else {
                c[i][j] = sqrt(pow(cities[i].first - cities[j].first, 2) + pow(cities[i].second - cities[j].second, 2));
            }
        }
    }

    
    A[1][0] = 0;

    for (int i = 0; i < (1 << n); i++) {
        if (!(i & 1)) continue;
        for (int v = 0; v < n; v++) {
            if (!(i & (1 << v))) continue;
            double min_value = INF;
            for (int prev_v = 0; prev_v < n; prev_v++) {
                int prev_bit = i & ~(1 << v);
                if (!(prev_bit & (1 << prev_v))) continue;
                if (A[prev_bit][prev_v] == INF) continue;
                min_value = min(min_value, A[prev_bit][prev_v] + c[prev_v][v]);
            }
            if (min_value == INF) continue;
            A[i][v] = min_value;
        }
    }

    double ans = INF;
    for (int i=1; i<n; i++) {
        ans = min(ans, A[(1 << n)-1][i]+c[i][0]);
    }
    cout << floor(ans) << endl;


}


