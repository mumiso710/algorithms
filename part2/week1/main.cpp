#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;


const string FILE_NAME = "SCC.txt";
// const string FILE_NAME = "test.txt";
const int NODE_NUM = 875715;
vector<bool> explored = vector<bool>(NODE_NUM, false);
vector<int> f = vector<int>(NODE_NUM);
vector<int> scc = vector<int>(NODE_NUM);
stack<int> s;
int num_scc = 0;
int cur_label = NODE_NUM - 1;


void print_graph(vector<vector<int> > &G) {
    for (int i=0; i<G.size(); i++) {
        if(G[i].size() != 0) cout << "G[" << i << "] : ";
        for (int j=0; j<G[i].size(); j++) {
        cout << G[i][j];
        if (j != G[i].size()-1) cout << " ";
        }
        if(G[i].size() != 0) cout << endl;
    }
}

vector<vector<int> > make_graph() {
    vector<vector<int> > G(NODE_NUM);
    ifstream file;
    file.open(FILE_NAME, ios::in);
    string buf;
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            string vertex = buf.substr(0, buf.find(" "));
            int v = stoi(vertex);
            string edge = buf.substr(vertex.length(), buf.size() - vertex.length() - 1);
            int e = stoi(edge);
            G[v].push_back(e);
            // stringstream edges(buf.substr(vertex.length(), buf.size() - vertex.length() - 1));
        }
    }
    file.close();

    return G;

}
vector<vector<int> > make_reverse_graph(vector<vector<int> > &G) {
    vector<vector<int> > G_rev(NODE_NUM);
    for (int i=0; i<NODE_NUM; i++) {
        for (int j=0; j<G[i].size(); j++) {
            int vertex = G[i][j];
            int edge = i;
            G_rev[vertex].push_back(edge);
        }
    }
    return G_rev;
}



void dfs_scc(vector<vector<int> > &G, int v) {
    explored[v] = true;
    scc[v] = num_scc;

    for (int i=0; i<G[v].size(); i++) {
        int next_v = G[v][i];
        if (!explored[next_v]) dfs_scc(G, next_v);
    }


}

void dfs_topo(vector<vector<int> > &G, int v) {
    explored[v] = true;
    for (int i=0; i<G[v].size(); i++) {
        int next_v = G[v][i];
        if (!explored[next_v]) dfs_topo(G, next_v);
    }
    f[cur_label] = v;
    cur_label--;
}

void topo_sort(vector<vector<int> > &G) {
    for (int i=1; i<NODE_NUM; i++) explored[i] = false;
    for (int i=1; i<NODE_NUM; i++) {
        if (!explored[i]) dfs_topo(G, i);
    }
}

void kosaraju(vector<vector<int> > &G) {

    vector<vector<int> > G_rev = make_reverse_graph(G);
    for (int i=1; i<NODE_NUM; i++) explored[i] = false;
    topo_sort(G_rev);

    num_scc = 0;

    for (int i=1; i<NODE_NUM; i++) explored[i] = false;

    for (int i=1; i<NODE_NUM; i++) {
        int v = f[i];
        if (!explored[v]) {
            num_scc++;
            dfs_scc(G, v);
        }
    }

}


int main() {

    vector<vector<int> > G = make_graph();
    // vector<vector<int> > G_rev = make_reverse_graph(G);
    kosaraju(G);
    // print_graph(G);
    // print_graph(G_rev);

    vector<int> scc_size = vector<int>(NODE_NUM, 0);
    for (int i=1; i<NODE_NUM; i++) scc_size[scc[i]]++;
    sort(scc_size.begin(), scc_size.end());
    reverse(scc_size.begin(), scc_size.end());
    for (int i=0; i<5; i++) {
        cout << scc_size[i];
        if (i != 5) cout << ",";
    }
    cout << endl;




} 

