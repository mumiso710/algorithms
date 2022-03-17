#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

const string FILENAME = "IntegerArray.txt";

tuple<vector<long long int>, long long int> mergeAndCountSplitInv(vector<long long int> C, vector<long long int> D) {
    long long int i = 0;
    long long int j = 0;
    long long int splitInv = 0;
    long long int n = C.size() + D.size();
    vector<long long int> B(n);
    for (long long int k = 0; k < n; k++) {
        if (j == D.size() || i < C.size() && C[i] < D[j]) {
            B[k] = C[i];
            i++;
        } else if (j < D.size()) {
            B[k] = D[j];
            j++;
            splitInv += (C.size() - i);
        }
    }
    return {B, splitInv};
}

tuple<vector<long long int>, long long int> sortAndCountInv(vector<long long int> A) {
    long long int n = A.size();
    vector<long long int> v1 (A.begin(), A.begin() + A.size()/2);
    vector<long long int> v2 (A.begin() + A.size()/2, A.end());
    // vector<int> B, C, D;
    // int leftInv, rightInv, splitInv;
    if (n == 0 || n == 1) return {A, 0};
    else {
        auto [C,  leftInv] = sortAndCountInv(v1);
        auto [D, rightInv] = sortAndCountInv(v2);
        auto [B, splitInv] = mergeAndCountSplitInv(C, D);
        return {B, leftInv + rightInv + splitInv};
    }
}

int main() {
    ifstream file;
    file.open(FILENAME, ios::in);

// ファイル読み込み
    string buf;
    vector<long long int> A;
    // vector<int> sortedV;
    // int countInv = 0;
    while (!file.eof()) {
        getline(file, buf);
        // cout << buf << endl;
        if (buf.size() != 0) A.push_back(stoll(buf));
    }
    file.close();
    auto [sortedV, countInv] = sortAndCountInv(A);
    // for (int i=0; i<sortedV.size(); i++) cout << A[i] << endl;
    cout << countInv << endl;
}