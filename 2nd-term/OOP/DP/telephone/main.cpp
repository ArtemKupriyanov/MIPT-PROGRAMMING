#include <iostream>
#include <vector>

using namespace std;

unsigned long long int dp (unsigned long long int n) {
    vector <unsigned long long int> vect(n + 1);
    vect[0] = 1;
    vect[1] = 8;
    vect[2] = (vect[0] + vect[1]) * 8;
    vect[3] = (vect[0] + vect[1] + vect[2])*8;
    for (unsigned long long int i = 3; i < n; ++i) {
        vect[i + 1] = (vect[i] + vect[i - 1] + vect[i - 2])*8 + vect[i - 3]*2;
    }
    return vect[n];
}

int main(int argc, char *argv[]) {
    unsigned long long int n;
    cin >> n;
    cout << dp(n);
    return 0;
}
