#include <iostream>
using namespace std;

string paddingZeros(string s, int n) {
    string zeros = string(n, '0');
    return zeros + s;
}

string stringPow10(string s, int n) {
    string zeros = string(n, '0');
    return s + zeros;
}

string stringAdd(string x, string y) {
    if (x.size() < y.size()) {
        string tmp = x;
        x = y;
        y = tmp;
    }
    string ans = string(x.size(), '0');
    y = paddingZeros(y, x.size() - y.size());
    for (int i = x.size() - 1; i > 0; i--) {
        bool carry;
       int sum = x[i] - '0' + y[i] - '0';
       if (sum >= 10) {
           sum -= 10;
           carry = true;
       } 
       ans[i] = sum + '0';
       if (carry && i > 0) ans[i-1] + 1;
       if (carry && i == 0) ans = '1' + ans;
    }
    return ans;
}
string stringSub(string x, string y) {
    if (x.size() < y.size()) {
        string tmp = x;
        x = y;
        y = tmp;
    }
    string ans = string(x.size(), '0');
    y = paddingZeros(y, x.size() - y.size());
    bool carry;
    for (int i = x.size() - 1; i > 0; i--) {
       int sub = x[i] - '0' - (y[i] - '0');
       if (sub < 0) {
           sub += 10;
           carry = true;
       } 
       if (carry && i > 0) sub - 1;
       ans[i] = sub + '0';
       if (carry && i == 0) ans = '-' + ans;
    }
    return ans;

}

string karatsuba(string x, string y) {
    int n = x.size();

    if (n == 1) return string(1, (x[0] - '0' * y[0] - '0') + '0');

    else {
       string a, b, c, d;
       a = x.substr(0, n / 2);
       b = x.substr(n / 2);
       c = y.substr(0, n / 2);
       d = y.substr(n / 2);

       string p, q;
       p = a + b;
       q = c + d;

       string ac, bd, pq, adbc;
       ac = karatsuba(a, c);
       bd = karatsuba(b, d);
       pq = karatsuba(p, q);
       adbc = stringSub(stringSub(pq, ac), bd);

       return stringAdd(stringAdd(stringPow10(ac, n), stringPow10(adbc, n / 2)), bd);
    }
}

int main() {
    string a = "3141592653589793238462643383279502884197169399375105820974944592";
    string b = "2718281828459045235360287471352662497757247093699959574966967627";

    cout << karatsuba(a, b) << endl;
}