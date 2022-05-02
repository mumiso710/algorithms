#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <utility> 

using namespace std;

const string    FILE_NAME1 = "g1.txt";
const string    FILE_NAME2 = "g2.txt";
const string    FILE_NAME3 = "g3.txt";
//const string    FILE_NAME1 = "test1.txt";
//const string    FILE_NAME2 = "test2.txt";
//const string    FILE_NAME3 = "test2.txt";
const int       INF        = 1000000;

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
        // add 1 for Jhonson's algorithm start vertex;
        node_num = stoi(buf.substr(0, buf.find(" "))) + 1;
        buf = buf.substr(0, buf.find(" "));
        edge_num = stoi(buf);
    }
    Graph G(node_num);
    // add start vertex for Johonson's algorithm
    for (int i = 1; i < node_num; i++) {
        G[0].push_back(make_pair(i, 0));
    }

    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            int from = stoi(buf.substr(0, buf.find(" ")));
            buf = buf.substr(buf.find(" ") + 1);
            int to = stoi(buf.substr(0, buf.find(" ")));
            buf = buf.substr(buf.find(" ") + 1);
            int cost = stoi(buf);
            G[from].push_back(make_pair(to, cost));
        }
    }
    file.close();

    return G;

}

bool bellman_ford(Graph &G, int start, vector<int> &P) {
    int n = G.size();
    vector<vector<int> > A(n + 1, vector<int>(n, INF));



    for (int i=0; i<=n; i++) {
        A[i][start] = 0;
    }


    for (int i = 1; i <= n; i++) {
        for (int from = 0; from < n; from++) {
            for (int j = 0; j < G[from].size(); j++) {
                int dist   = G[from][j].first;
                int length = G[from][j].second;
                if (A[i][dist] > A[i-1][from] + length and A[i-1][from] != INF) {
                    A[i][dist] = min(A[i-1][dist], A[i-1][from] + length);
                } 
            }
        }
    }

    int flag = true;
    for (int i = 0; i < n; i++) {
        if (A[n][i] != A[n-1][i]) flag = false;
    }


    for (int i = 0; i < n; i++) {
        P[i] = A[n][i];
    }

    return flag;
}
//
void update_graph(Graph &G, vector<int> &P) {
    int n= G.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<G[i].size(); j++) {
            int to = G[i][j].first;
            int cost = G[i][j].second;
            G[i][j].second = cost + P[i] - P[to];
        }
    }
}

void dijkstra(Graph &G, int from, vector<vector<int> > &dist, vector<int> &P) {
    int n = G.size();
    set<int> X;
    vector<int> key(n+1);
    vector<int> len(n+1, INF);
    // pair = (key[v], v)
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    key[from] = 0;
    for (int i=0; i<n; i++) {
        if (i != from) key[i] = INF;
    }
    for (int i=0; i<n; i++) {
        pq.push(make_pair(key[i], i));
    }
    while (!pq.empty()) {
        int w = pq.top().second;
        pq.pop();
        if (X.find(w) != X.end()) continue;
        X.insert(w);
        len[w] = key[w];
        for (pair<int, int> y : G[w]) {
            int to = y.first;
            int cost = y.second;
            key[to] = min(key[to], len[w] + cost);
            pq.push(make_pair(key[to], to));
        }
    }
    for (int i=0; i<G.size(); i++) {
        dist[from][i] = len[i];
    }
    for (int i=0; i<G.size(); i++) {
        dist[from][i] = dist[from][i] - P[from] + P[i];
    }
}

void jhonson(Graph G) {
    vector<int> P(G.size());
    vector<vector<int> > dist(G.size(), vector<int>(G.size(), INF));

    if (bellman_ford(G, 0, P)) {
        cout << "There is no cycle!" << endl;
        update_graph(G, P);
        cout << "Please wait calculateing min path" << endl;
        for (int i=0; i<G.size(); i++) {
            dijkstra(G, i, dist, P);
        }
    } else {
        cout << "This graph has cycle!" << endl;
        return;
    }

    int min_path = INF;
    for (int i=1; i<G.size(); i++) {
        for (int j=1; j<G.size(); j++) {
            min_path = min(min_path, dist[i][j]);
        }
    }
    cout << min_path << endl;
}

int main() {
    Graph G1, G2, G3;
    G1 = make_graph(FILE_NAME1);
    G2 = make_graph(FILE_NAME2);
    G3 = make_graph(FILE_NAME3);

    jhonson(G1);
    jhonson(G2);
    jhonson(G3);

}
