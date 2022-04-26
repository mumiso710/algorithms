#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

const string FILE_NAME1      = "huffman.txt";
const string FILE_NAME2      = "mwis.txt";
const int    MAX_NODE_NUM    = 1000;

priority_queue<pair<long long , long long>, vector<pair<long long, long long> >, greater<pair<long long, long long> > > make_queue() {
    ifstream file;
    file.open(FILE_NAME1, ios::in);
    string buf;

    priority_queue<pair<long long, long long>, vector<pair<long long, long long> >, greater<pair<long long, long long> > > Q;

    int node_num;
    if (!file.eof()) {
        // read number of nodes and number of edges
        getline(file, buf);
        node_num = stoi(buf);
        // node_num = stoi(buf.substr(0, buf.find(" ")));
    }
    for (int i=1; i<=node_num; i++) {
        getline(file, buf);
        if (buf.size() != 0) {
            Q.push(make_pair(stoi(buf), 0));
        }
    }
    file.close();

    return Q;

}

vector<int> make_nodes() {
    ifstream file;
    file.open(FILE_NAME2, ios::in);
    string buf;

    vector<int> nodes;

    int node_num;
    if (!file.eof()) {
        // read number of nodes and number of edges
        getline(file, buf);
        node_num = stoi(buf);
        // node_num = stoi(buf.substr(0, buf.find(" ")));
    }
    for (int i=1; i<=node_num; i++) {
        getline(file, buf);
        if (buf.size() != 0) {
            nodes.push_back(stoi(buf));
        }
    }
    file.close();

    return nodes;

}

int main() {
    priority_queue<pair<long long, long long>, vector<pair<long long, long long> >, greater<pair<long long ,long long> > > Q;

    // problem1
    Q = make_queue();
    while(!Q.empty()) {
        pair<long long, long long> p1, p2;
        p1 = Q.top();
        Q.pop();
        p2 = Q.top();
        Q.pop();
        Q.push(make_pair((p1.first + p2.first), max(p1.second, p2.second) + 1));
        if (Q.size() == 1) {
            cout << Q.top().second << endl;
        }
    }

    // problem2
    Q = make_queue();
    while(!Q.empty()) {
        pair<long long, long long> p1, p2;
        p1 = Q.top();
        Q.pop();
        p2 = Q.top();
        Q.pop();
        Q.push(make_pair((p1.first + p2.first), min(p1.second, p2.second) + 1));
        if (Q.size() == 1) {
            cout << Q.top().second << endl;
        }
    }

    //problem3
    vector<int> target_nodes = {1, 2, 3, 4, 17, 117, 517, 997};
    vector<int> nodes;
    nodes = make_nodes();
    vector<long long> A(nodes.size()+1);
    A[0] = 0;
    A[1] = nodes[0];
    for (int i = 2; i <= A.size(); i++) {
        A[i] = max(A[i - 1], A[i - 2] + nodes[i - 1]);
    }

    vector<int> node_nums;
    int i = A.size()-1;
    while (i >= 2) {
        if (A[i - 1] >= A[i - 2] + nodes[i - 1]) {
            i--;
        } else {
            node_nums.push_back(i);
            i = i - 2;
        }
    }
    if (i == 1) node_nums.push_back(i);

    string ans = "";
    for (int i=0; i<target_nodes.size(); i++) {
        if (find(node_nums.begin(), node_nums.end(), target_nodes[i]) != node_nums.end()) {
            ans += "1";
        } else {
            ans += "0";
        }
    }
    cout << ans << endl;


}