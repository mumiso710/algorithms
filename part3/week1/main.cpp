#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;


const string FILE_NAME1 = "jobs.txt";
const string FILE_NAME2 = "edges.txt";
const    int START_VERTEX = 1;


void print_jobs(vector<pair<int, int> > &jobs) {
    for (int i=0; i<jobs.size(); i++) {
        cout << "w : " << jobs[i].first << " l : " << jobs[i].second << endl;
    }
}

void print_graph(vector<vector<pair<int, int> > > &G) {
    for (int i=0; i<G.size(); i++) {
        if(G[i].size() != 0) cout << "G[" << i << "] : ";
        for (int j=0; j<G[i].size(); j++) {
        cout << "(edge : " << G[i][j].first << ", cost : " << G[i][j].second << ")";
        if (j != G[i].size()-1) cout << ", ";
        }
        if(G[i].size() != 0) cout << endl;
    }
}
vector<pair<int, int> > make_jobs() {
    vector<pair<int, int> > jobs;
    int jobs_num;
    ifstream file;
    file.open(FILE_NAME1, ios::in);
    string buf;
    if (!file.eof()) {
        getline(file, buf);
        jobs_num = stoi(buf);
    }
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            string weight = buf.substr(0, buf.find(" "));
            int w = stoi(weight);
            string length = buf.substr(weight.length()+1, buf.size() - weight.length() - 1);
            int l = stoi(length);
            pair<int, int> job;
            job.first = w;
            job.second = l;
            jobs.push_back(job);
        }
    }
    file.close();

    return jobs;
}

vector<vector<pair<int, int> > > make_graph() {
    ifstream file;
    file.open(FILE_NAME2, ios::in);
    string buf;

    int node_num;
    if (!file.eof()) {
        // read number of nodes and number of edges
        getline(file, buf);
        node_num = stoi(buf.substr(0, buf.find(" ")));
    }
    vector<vector<pair<int, int> > > G(node_num + 1);
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            string vertex = buf.substr(0, buf.find(" "));
            int v = stoi(vertex);
            buf = buf.substr(vertex.length()+1);
            string edge = buf.substr(0, buf.find(" "));
            int e = stoi(edge);
            string cost = buf.substr(edge.length()+1);
            int c = stoi(cost);
            pair<int, int> edge_and_cost1;
            pair<int, int> edge_and_cost2;
            edge_and_cost1.first = e;
            edge_and_cost1.second = c;
            edge_and_cost2.first = v;
            edge_and_cost2.second = c;
            G[v].push_back(edge_and_cost1);
            G[e].push_back(edge_and_cost2);
        }
    }
    file.close();

    return G;

}

bool compare_jobs_by_diff(pair<int, int> &job1, pair<int, int> &job2) {
    int job1_diff = job1.first - job1.second;
    int job2_diff = job2.first - job2.second;
    if (job1_diff == job2_diff) return job1.first > job2.first;
    else return job1_diff > job2_diff;
}

// job<w, l>
bool compare_jobs_by_ratio(pair<int, int> &job1, pair<int, int> &job2) {
    double job1_ratio = double(job1.first) / job1.second;
    double job2_ratio = double(job2.first) / job2.second;
    if (job1_ratio == job2_ratio) return job1.first > job2.first;
    else return job1_ratio > job2_ratio;
}

long long int calc_ans(vector<pair<int, int> > &jobs) {
    long long int time = 0;
    long long ans = 0;
    for (int i=0; i<jobs.size(); i++) {
        int w = jobs[i].first;
        int l = jobs[i].second;
        time += l;
        ans += time * w;
    }
    return ans;
}

long long int prim(vector<vector<pair<int, int> > > &G) {
    vector<int> X{START_VERTEX};
    vector<int> T = vector<int>();
    long long int cost = 0;
    while (X.size() < G.size() - 1) {
        int minWeight = 100000;
        int minEdge;
        for (int v : X) {
            for (pair<int, int> e : G[v]) {
                if (find(X.begin(), X.end(), e.first) != X.end()) continue;
                if (e.second < minWeight) {
                    minEdge = e.first;
                    minWeight = e.second;
                }
            }
        }
        // cout << "minE : " << minEdge << " minC : " << minWeight << endl;
        X.push_back(minEdge);
        cost += minWeight;
    }
    return cost;
}

int main() {
    // for problem1,2
    vector<pair<int, int> > jobs = make_jobs();
    sort(jobs.begin(), jobs.end(), compare_jobs_by_diff);
    cout << "problem1 : " << calc_ans(jobs) << endl;
    sort(jobs.begin(), jobs.end(), compare_jobs_by_ratio);
    cout << "problem2 : " << calc_ans(jobs) << endl;

    // for problem3
    vector<vector<pair<int, int> > > G = make_graph();
    long long int ans = prim(G);
    cout << "problem3 : " << prim(G) << endl;

}