#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

const string FILE_NAME = "algo1-programming_prob-2sum.txt";

vector<long long int> make_array() {
    vector<long long int> A;

    ifstream file;
    file.open(FILE_NAME, ios::in);
    string buf;
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            A.push_back(stoll(buf));
        }
    }
    file.close();

    return A;

}

int main() {

    vector<long long int> A = make_array();
    vector<long long int> no_duplication_A;

    set<long long int> st = set<long long int>();
    set<long long int> ans_st = set<long long int>();
    for (int i=0; i<A.size(); i++) {
        st.insert(A[i]);
    }

    for (auto itr = st.begin(); itr != st.end(); itr++) {
        no_duplication_A.push_back(*itr);
    }
    

    int min_index = 0;
    int max_index = A.size() - 1;
    while (min_index < max_index) {
        long long x = no_duplication_A[min_index];
        long long y = no_duplication_A[max_index];
        if (x + y < -10000) min_index++;
        else if (x + y > 10000) max_index--;
        
        if (min_index == max_index) break;

        int temp_min_index = min_index;
        while (x + y <= 10000) {
            if (-10000 <= x + y) ans_st.insert(x + y);
            temp_min_index++;
            if (temp_min_index == max_index) break;
            x = no_duplication_A[temp_min_index];
        }
        max_index--;
    }

    cout << ans_st.size() << endl;



}