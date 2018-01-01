#include <iostream>
#include <string>
#include <vector>

const long long p = 33;
const long long mod_2 = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::string str;
    std::cin >> str;
    long long M;
    std::cin >> M;
    long long a, b, c, d;
    long long * p_pow = new long long[str.length()];
    long long * prefix_hash = new long long[str.length()];
//    std::vector < long long> p_pow(str.length());
//    std::vector < long long> prefix_hash(str.length());
    p_pow[0] = 1;

    for (long long i = 1; i < str.length(); ++i) {
        p_pow[i] = (p_pow[i-1] * p) % mod_2;
    }
    prefix_hash[0] = str[0] - 'a' + 1;
    for (long long i = 1; i < str.length(); ++i) {
        prefix_hash[i] = (prefix_hash[i-1] + (str[i] - 'a' + 1) * p_pow[i]) % mod_2;
    }
    for (long long i = 0; i < M; ++i) {
        std::cin >> a >> b >> c >> d;
        if (a > c) {
            std::swap(a, c);
            std::swap(b, d);
        }
        long long hash_1, hash_2;
        hash_1 = (prefix_hash[b - 1] - (a == 1 ? 0 : prefix_hash[a - 2])) % mod_2;
        hash_2 = (prefix_hash[d - 1] - (c == 1 ? 0 : prefix_hash[c - 2])) % mod_2;
        if (hash_1 < 0) {
            hash_1 = mod_2 + hash_1;
        }
        if (hash_2 < 0) {
            hash_2 = mod_2 + hash_2;
        }
        std::cout << ((hash_1 * p_pow[c - a]) % mod_2 == hash_2 ? "Yes\n" : "No\n");
    }
    delete[] p_pow;
    delete[] prefix_hash;
    return 0;
}