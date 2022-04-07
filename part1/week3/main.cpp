#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const string FILENAME = "quickSort.txt";
long long ans = 0;

long long choosePivot(vector<long long> &A, int l, int r) {
    long long first = A[l];
    long long mid = A[(l + r) / 2];
    long long last = A[r];
    vector<long long> candidates = {first, mid, last};
    sort(candidates.begin(), candidates.end());
    auto result = find(A.begin() + l, A.begin() + r, candidates[1]);
    return distance(A.begin(), result);
}

int partition(vector<long long> &A, int l, int r) {
    int p = A[l];
    int i = l + 1;
    ans += r - l + 1 - 1;
    for (int j = l + 1; j <= r; j++) {
        if (A[j] < p) {
            swap(A[j], A[i]);
            i++;
        }
    }
    swap(A[l], A[i-1]);
    return i - 1;
}

void quickSort(vector<long long> &A, int l, int r) {
    if (l >= r) return;

    int i = choosePivot(A, l, r);
    swap(A[l], A[i]);
    int j = partition(A, l, r);
    quickSort(A, l, j - 1);
    quickSort(A, j + 1, r);

}

int main() {
    ifstream file;
    file.open(FILENAME, ios::in);

    string buf;
    vector<long long> A;
    while (!file.eof()) {
        getline(file, buf);
        if (buf.size() != 0) A.push_back(stoll(buf));
    }
    file.close();

    quickSort(A, 0, A.size()-1);

    cout << ans << endl;
}