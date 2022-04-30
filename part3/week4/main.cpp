#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <utility>
using namespace std;

typedef pair<int, int> Item;
const string FILE_NAME1 = "knapsack1.txt";
const string FILE_NAME2 = "knapsack_big.txt";

void print_items(vector<Item> &items) {
    for (int i=0; i<items.size(); i++) {
        cout << items[i].first << " " << items[i].second << endl;
    }
}



vector<Item> make_items(int &knapsack_size, int &item_num, string string_name) {
    ifstream file;
    file.open(string_name, ios::in);
    string buf;

    if (!file.eof()) {
        getline(file, buf);
        knapsack_size = stoi(buf.substr(0, buf.find(" ")));
        buf = buf.substr(buf.find(" ") + 1);
        item_num = stoi(buf);
    }
    
    vector<Item> items;

    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            int value = stoi(buf.substr(0, buf.find(" ")));
            buf = buf .substr(buf.find(" ") + 1);
            int weight = stoi(buf);
            items.push_back(make_pair(value, weight));
        }
    }

    file.close();
    
    return items;
}

int main() {

    int knapsack_size;
    int item_num;
    vector<Item> items = make_items(knapsack_size, item_num, FILE_NAME1);


   int A[item_num + 1][knapsack_size + 1];

   for (int i = 0; i <= knapsack_size; i++) {
       A[0][i] = 0;
   }

   for (int i = 1; i <= item_num; i++) {
       int value = items[i - 1].first;
       int weight = items[i - 1].second;
       for (int c = 0; c <= knapsack_size; c++) {
           if (weight > c) A[i][c] = A[i - 1][c];
           else A[i][c] = max(A[i - 1][c], A[i - 1][c - weight] + value);
       }
   }

   cout << A[item_num][knapsack_size] << endl;

    // for problem2

    items = make_items(knapsack_size, item_num, FILE_NAME2);


    int B[knapsack_size + 1];

    for (int c = 0; c <= knapsack_size; c++) {
        B[c] = 0;
    }

   for (int i = 1; i <= item_num; i++) {
       int value = items[i - 1].first;
       int weight = items[i - 1].second;
       for (int c = knapsack_size; c > 0; c--) {
           
           if (weight > c) B[c] = B[c];
           else B[c] = max(B[c], B[c - weight] + value);
       }
   }

    cout << B[knapsack_size] << endl;

}
