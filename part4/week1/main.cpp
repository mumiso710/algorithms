#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

const string FILE_NAME1 = "g1.txt";
const string FILE_NAME2 = "g2.txt";
const string FILE_NAME3 = "g3.txt";

// Edge(to, cost)
typedef pair<int, int> Edge;
typedef vector<vector<Edge> > Graph;


void print_graph(Graph &G) {
    for (int i = 0; i < G.size(); i++) {
        for (int j = 0; j < G[i].size(); j++) {
            cout << "from : " << i << " to : " << G[i][j].first << " cost : " << G[i][j].second << endl;
        }
    }
}

Graph make_graph(string file_name) {
    ifstream file;
    file.open(file_name, ios::in);
    string buf;

    int node_num;
    int edge_num;
    if (!file.eof()) {
        getline(file, buf);
        node_num = stoi(buf.substr(0, buf.find(" ")));
        buf = buf.substr(0, buf.find(" "));
        edge_num = stoi(buf);
    }
    Graph G(node_num);
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            int from = stoi(buf.substr(0, buf.find(" "))) - 1;
            buf = buf.substr(buf.find(" ") + 1);
            int to = stoi(buf.substr(0, buf.find(" "))) - 1;
            buf = buf.substr(buf.find(" ") + 1);
            int cost = stoi(buf);
            G[from].push_back(make_pair(to, cost));
        }
    }
    file.close();

    return G;

}

void floyd_warshall(Graph &G) {
    return;
}

int main() {
    Graph G1, G2, G3;
    G1 = make_graph(FILE_NAME1);
    G2 = make_graph(FILE_NAME2);
    G3 = make_graph(FILE_NAME3);

    floyd_warshall(G1);
}
