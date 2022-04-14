#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_NODE_NUM = 10000;
const int DIVISIOR = 10000;
// const int MAX_NODE_NUM = 10;
const string FILE_NAME = "Median.txt";
// const string FILE_NAME = "test.txt";

vector<int> make_nodes() {
    vector<int> H;

    ifstream file;
    file.open(FILE_NAME, ios::in);
    string buf;
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) {
            H.push_back(stoi(buf));
        }
    }
    file.close();

    return H;

}

void insert_to_min_heap(vector<int> &H, int node) {
    H.push_back(node);
    int child_index = H.size() - 1;
    int parent_index = (child_index - 1) / 2;
    if (child_index == parent_index) return;
    while (H[child_index] < H[parent_index]) {
        swap(H[child_index], H[parent_index]);
        child_index = parent_index;
        parent_index = (child_index - 1) / 2;
        if (child_index == parent_index) break;
    }
}

void insert_to_max_heap(vector<int> &H, int node) {
    H.push_back(node);
    int child_index = H.size() - 1;
    int parent_index = (child_index - 1) / 2;
    if (child_index == parent_index) return;
    while (H[child_index] > H[parent_index]) {
        swap(H[child_index], H[parent_index]);
        child_index = parent_index;
        parent_index = (child_index - 1) / 2;
        if (child_index == parent_index) break;
    }
}

int extract_min(vector<int> &H) {
    int min_node = H[0];
    if (H.size() == 1) {
        H.pop_back();
        return min_node;
    }

    if (H.size() == 2) {
        swap(H[0], H[H.size()-1]);
        H.pop_back();
        return min_node;
    }

    if (H.size() == 3) {
        swap(H[0], H[H.size()-1]);
        H.pop_back();
        if (H[0] > H[1]) swap(H[0], H[1]);
        return min_node;
    }
    
    swap(H[0], H[H.size()-1]);
    H.pop_back();

    int parent_index = 0;
    int left_child_index = 1;
    int right_chile_index = 2;
    while (H[parent_index] > H[left_child_index] || H[parent_index] > H[right_chile_index]) {
        int min_child_index = H[left_child_index] < H[right_chile_index] ? left_child_index : right_chile_index;
        swap(H[parent_index], H[min_child_index]);
        parent_index = min_child_index;
        left_child_index = parent_index * 2 + 1;
        right_chile_index = parent_index * 2 + 2;
        if (left_child_index == H.size() - 1 && H[parent_index] > H[left_child_index]) {
            swap(H[parent_index], H[left_child_index]);
            break;
        }
        // if (right_chile_index == H.size() - 1 && H[parent_index] > H[right_chile_index]) {
        //     swap(H[parent_index], H[right_chile_index]);
        //     break;
        // }
        if (right_chile_index > H.size() - 1 || left_child_index > H.size() - 1) break;
    }

    return min_node;
}

int extract_max(vector<int> &H) {
    int max_node = H[0];
    if (H.size() == 1) {
        H.pop_back();
        return max_node;
    }
    if (H.size() == 2) {
        swap(H[0], H[H.size()-1]);
        H.pop_back();
        return max_node;
    }

    if (H.size() == 3) {
        swap(H[0], H[H.size()-1]);
        H.pop_back();
        if (H[0] < H[1]) swap(H[0], H[1]);
        return max_node;
    }

    swap(H[0], H[H.size()-1]);
    H.pop_back();
    
    int parent_index = 0;
    int left_child_index = 1;
    int right_chile_index = 2;
    while (H[parent_index] < H[left_child_index] || H[parent_index] < H[right_chile_index]) {
        int max_child_index = H[left_child_index] > H[right_chile_index] ? left_child_index : right_chile_index;
        swap(H[parent_index], H[max_child_index]);
        parent_index = max_child_index;
        left_child_index = parent_index * 2 + 1;
        right_chile_index = parent_index * 2 + 2;
        if (left_child_index == H.size() - 1 && H[parent_index] < H[left_child_index]) {
            swap(H[parent_index], H[left_child_index]);
            break;
        }
        if (left_child_index > H.size() -1 || right_chile_index > H.size() - 1) break;
    }

    return max_node;
}

int main() {
    vector<int> nodes, H_min, H_max;

    // read nodes from file.
    nodes = make_nodes();


    reverse(nodes.begin(), nodes.end());
    int node = nodes[nodes.size() - 1];
    nodes.pop_back();
    insert_to_max_heap(H_max, node);
    int ans = node;

    int max_value_in_H_max = node;
    for (int i = 1; i < MAX_NODE_NUM; i++) {
        node = nodes[nodes.size() - 1];
        nodes.pop_back();
        if (max_value_in_H_max < node) {
            insert_to_min_heap(H_min, node);
        } else {
            insert_to_max_heap(H_max, node);
            max_value_in_H_max = H_max[0];
        }
        if (H_max.size() > H_min.size() + 1) {
            insert_to_min_heap(H_min, extract_max(H_max));
            max_value_in_H_max = H_max[0];
        }
        else if (H_max.size() + 1 < H_min.size()) {
            insert_to_max_heap(H_max, extract_min(H_min));
            max_value_in_H_max = H_max[0];
        }
        
        int ith = H_max.size() + H_min.size();
        int med_index = (ith + 1) / 2;
        // cout << "m_i : " << med_index << " H_max.size() : " << H_max.size() << endl;
        if (ith % 2 == 0) ans += H_max[0];
        else {
            if (H_max.size() > H_min.size()) ans += H_max[0];
            else ans += H_min[0];
        }
        ans %= DIVISIOR;
    }

    cout << ans << endl;


}

