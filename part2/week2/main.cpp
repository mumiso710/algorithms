#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <sstream>

using namespace std;

const string FILE_NAME = "dijkstraData.txt";
const int NODE_NUM = 200;
const int INF = 1000000;

vector<int> len(NODE_NUM+1);

void print_graph(vector<vector<pair<int, int> > > &G) {
    for (int i=0; i<G.size()+1; i++) {
        if(G[i].size() != 0) cout << "G[" << i << "] : ";
        for (int j=0; j<G[i].size(); j++) {
        cout << "(edge : " << G[i][j].first << " cost : " << G[i][j].second << ")";
        if (j != G[i].size()-1) cout << ", ";
        }
        if(G[i].size() != 0) cout << endl;
    }
}

vector<vector<pair<int, int> > > make_graph() {
    vector<vector<pair<int, int> > > G(NODE_NUM);
    ifstream file;
    file.open(FILE_NAME, ios::in);
    string buf;
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            string vertex = buf.substr(0, buf.find("\t"));
            int v = stoi(vertex);
            stringstream edges_and_costs_ss(buf.substr(vertex.length()+1, buf.size() - vertex.length() - 1));
            string edges_and_costs;
            while (getline(edges_and_costs_ss, edges_and_costs, '\t')) {
                if (edges_and_costs.empty() or edges_and_costs.length() == 1) continue;
                string edge = edges_and_costs.substr(0, edges_and_costs.find(","));
                int e = stoi(edge);
                string cost = edges_and_costs.substr(edge.length()+1, edges_and_costs.length() - edge.length());
                int c = stoi(cost);
                G[v].push_back(pair<int, int>(e, c));
            }
        }
    }
    file.close();

    return G;

}

void dijkstra(vector<vector<pair<int, int> > > &G, int destination) {
    set<int> X;
    X.insert(1);
    len[1] = 0;
    for (int i=2; i<=NODE_NUM; i++) len[i] = INF;
    while (X.count(destination) == 0) {
        int min_vertex;
        int min_cost = INF;
        for (int v : X) {
            for (int i=0; i<G[v].size(); i++) {
                int w = G[v][i].first;
                int l = G[v][i].second;
                if (X.count(w) != 0) continue;
                if (min_cost > len[v] + l) {
                    min_cost = len[v] + l;
                    min_vertex = w;
                }
            }
        }
        if (min_cost == INF) continue;
        X.insert(min_vertex);
        len[min_vertex] = min_cost;
    }
    
}

int main() {
    vector<vector<pair<int, int> > > G = make_graph();
    // print_graph(G);
    vector<int> destinations = {7,37,59,82,99,115,133,165,188,197};
    for (int destination: destinations) dijkstra(G, destination); 
    for (int i=0; i<destinations.size(); i++) {
        int destination = destinations[i];
        cout << len[destination];
        if (i != destinations.size()-1) cout << ",";
    }
    cout << endl;
}