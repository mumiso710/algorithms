#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <bitset>
#include <unordered_map>

using namespace std;

const string FILE_NAME1      = "clustering1.txt";
const string FILE_NAME2      = "clustering_big.txt";
const int    MAX_CLUSTER_NUM = 4;
const int    MAX_NODE_NUM    = 500;


struct UnionFind {
    vector<int> par, siz;

    UnionFind(int n) {
        par = vector<int>(n);
        siz = vector<int>(n);
        for (int i = 0; i < n; i++) {
            par[i] = i;
            siz[i] = 1;
        }
    }

    int root(int x) {
        if (par[x] == x) return x;
        else return par[x] = root(par[x]);
    }

    bool issame(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y) {
        int rx = root(x), ry = root(y);
        if (rx == ry) return false;
        if (siz[rx] >= siz[ry]) {
            par[ry] = rx;
            siz[rx] += siz[ry];
        } else {
            par[rx] = ry;
            siz[ry] += siz[rx];
        }
        return true;
    }



};

struct Edge {
    int n1, n2, c;
    Edge(int node1, int node2, int cost) {
        n1 = node1;
        n2 = node2;
        c  = cost;
    }

};

void print_edges(vector<Edge> &edges) {
    for (int i=0; i<edges.size(); i++) {
        cout << "n1 : " << edges[i].n1 << " n2 : " << edges[i].n2 << " c : " << edges[i].c << endl;
    }
}

bool compare_with_c(const struct Edge &e1, const struct Edge &e2) {
    return e1.c > e2.c;
}

vector<Edge> make_edges() {
    ifstream file;
    file.open(FILE_NAME1, ios::in);
    string buf;

    int node_num;
    if (!file.eof()) {
        // read number of nodes and number of edges
        getline(file, buf);
        node_num = stoi(buf);
        // node_num = stoi(buf.substr(0, buf.find(" ")));
    }
    vector<Edge> E = vector<Edge>();
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            string vertex = buf.substr(0, buf.find(" "));
            int n1 = stoi(vertex);
            buf = buf.substr(vertex.length()+1);
            string edge = buf.substr(0, buf.find(" "));
            int n2 = stoi(edge);
            string cost = buf.substr(edge.length()+1);
            int c = stoi(cost);
            Edge e = Edge(n1, n2, c);
            E.push_back(e);
        }
    }
    file.close();

    return E;

}

unordered_map<bitset<24>, vector<int> > make_nodes() {
    unordered_map<bitset<24>, vector<int> > nodes;
    int node_num = 0;

    ifstream file;
    file.open(FILE_NAME2, ios::in);
    string buf;

    if (!file.eof()) {
        getline(file, buf);
    }

    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            string bit = buf;
            bit.erase(std::remove(bit.begin(), bit.end(), ' '), bit.end());
            if (nodes.contains(bitset<24>(bit))) {
                nodes[bitset<24>(bit)].push_back(node_num);
            } else {
                nodes.emplace(bitset<24>(bit), vector<int>(1, node_num));
            }
            node_num++;
        }
    }
    file.close();


    return nodes;

}

int main () {
    vector<Edge> edges = make_edges();
    sort(edges.begin(), edges.end(), compare_with_c);

    int cluster_num = MAX_NODE_NUM;

    UnionFind uf1(MAX_NODE_NUM);

    while (cluster_num > MAX_CLUSTER_NUM) {
        Edge min_edge = edges[edges.size()-1];
        edges.pop_back();
        int n1 = min_edge.n1 - 1;
        int n2 = min_edge.n2 - 1;
        int c  = min_edge.c;

        if (uf1.unite(n1, n2)) cluster_num--;

    }

    while (cluster_num == MAX_CLUSTER_NUM) {
        Edge min_edge = edges[edges.size()-1];
        edges.pop_back();
        int n1 = min_edge.n1 - 1;
        int n2 = min_edge.n2 - 1;
        int c  = min_edge.c;

        if (uf1.unite(n1, n2)) cluster_num--;

        if (cluster_num != MAX_CLUSTER_NUM) {
            cout << c << endl;
        }
    }

    // problem2
    vector<bitset<24> > bitmasks = vector<bitset<24> >();

    for (int i=0; i<24; i++) {
        bitset<24> bitmask{};
        bitmask.set(i);
        bitmasks.push_back(bitmask);
    }

    for (int i=0; i<23; i++) {
        for (int j=i+1; j<24; j++) {
            bitset<24> bitmask{};
            bitmask.set(i);
            bitmask.set(j);
            bitmasks.push_back(bitmask);
        }
    }
    bitmasks.push_back(bitset<24>());

    UnionFind uf2(200000);
    int k = 200000;

    unordered_map<bitset<24>, vector<int> > nodes;
    nodes = make_nodes();

    for (auto pair : nodes) {
        for (int i=0; i<pair.second.size(); i++) {
            if(uf2.unite(pair.second[0], pair.second[i])) k--;
        }
    }

    for (auto pair : nodes) {
        for (int i=0; i<pair.second.size(); i++) {
            for (auto bitmask : bitmasks) {
                bitset<24> bit = pair.first ^ bitmask;
                if (nodes.find(bit) != nodes.end()) {
                    for (int j=0; j<nodes[bit].size(); j++) {
                        if(uf2.unite(pair.second[i], nodes[bit][j])) {
                            k--;
                        }
                    }
                }
            }
        }
    }
    cout << k << endl;
}
