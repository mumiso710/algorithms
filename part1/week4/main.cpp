#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
using namespace std;

const string FILENAME = "kargerMinCut.txt";
// const string FILENAME = "test.txt";
const int SIMULATION_NUM = 100;


void print_graph(vector<vector<int> > &G) {
    for (int i=0; i<G.size()+1; i++) {
        if(G[i].size() != 0) cout << "G[" << i << "] : ";
        for (int j=0; j<G[i].size(); j++) {
        cout << G[i][j];
        if (j != G[i].size()-1) cout << " ";
        }
        if(G[i].size() != 0) cout << endl;
    }
}


vector<vector<int> > make_graph() {
    ifstream file;
    file.open(FILENAME, ios::in);
    vector<vector<int> > G(201);
    string buf;
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            string vertex = buf.substr(0, buf.find("\t"));
            int v = stoi(vertex);
            stringstream edges(buf.substr(vertex.length(), buf.size() - vertex.length() - 1));
            string edge;
            while (getline(edges, edge, '\t')) {
                // if (!edge.empty()) {
                    // cout << edge;
                    // cout << " stoi : " << stoi(edge);
                    if (!edge.empty()) G[v].push_back(stoi(edge)); 
                    
                // }
            }
        }
    }
    file.close();

    return G;
} 

int find_min_cut(vector<vector<int> > &G) {

    int merged_vertex_num = 0;
    int last_v1 = -1;
    int last_v2 = -1;

    int vertex_num = 0;
    for (int i=0; i<201; i++) {
        if (G[i].size() != 0) vertex_num++;
    }

    while (merged_vertex_num != vertex_num - 2) {
        random_device rd;
        default_random_engine eng(rd());
        uniform_int_distribution<int> distr_for_v1(1, 200);
        int v1 = distr_for_v1(eng);
        if (G[v1].size() == 0) continue;

        uniform_int_distribution<int> distr_for_v2(0, G[v1].size() - 1);
        int v2 = G[v1][distr_for_v2(eng)];
        if (G[v2].size() == 0) continue;

        if (v1 == v2) continue;

        G[v1].erase(remove(G[v1].begin(), G[v1].end(), v2), G[v1].end());
        G[v2].erase(remove(G[v2].begin(), G[v2].end(), v1), G[v2].end());

        

        // cout << v1 << " " << v2 << endl;
        // print_graph(G);



        for (int i=0; i<G[v2].size(); i++) {
            if (G[v2][i] != v1) G[v1].push_back(G[v2][i]);
            // bool isDuplicate = false;
            // for (int j=0; j<G[v1].size(); j++) {
            //     if (G[v1][j] == G[v2][i]) isDuplicate = true;

            // }
            // if (!isDuplicate && G[v2][i] != v1) G[v1].push_back(G[v2][i]);
        }
        // v1 + v2 -> v1
        // G[i] {..., v2, ...} -> G[i] {..., v1, ...}
        for (int i=0; i<201; i++) {
            for (int j=0; j<G[i].size(); j++) {
                if (G[i][j] == v2) G[i][j] = v1;
            }
        }

        G[v2] = vector<int>();
        merged_vertex_num++;
    }
    int ans = 0;
    for (int i=0; i<201; i++) {
        ans += G[i].size();
    }
    return ans / 2;
}

int main() {

    int min_cut = 100000;
    for (int i=0; i<100; i++) {
        vector<vector<int> > G = make_graph();
        // print_graph(G);
        int cut_num = find_min_cut(G);
        if (min_cut > cut_num) min_cut = cut_num;
        cout << "now : " << i + 1 << "th simulation and min_cut is " << min_cut << endl;
    }

    cout << min_cut << endl;


}