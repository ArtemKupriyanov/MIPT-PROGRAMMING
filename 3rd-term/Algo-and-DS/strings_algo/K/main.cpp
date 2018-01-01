#include <iostream>
#include <vector>
#include <string>

std::vector<int> Kasai(std::string& str, std::vector<int>& suf_mas) {
	int n = str.length();
	std::vector<int> rank(n, 0);
    std::vector<int> lcp(n, 0);
	for (int i = 0; i < n; ++i) rank[suf_mas[i]] = i;
	for (int i = 0, k = 0; i < n; ++i)
	{
		if (k > 0) k--;
		if (rank[i] == n - 1)
                {
                    lcp[n - 1] = -1, k = 0;
                    continue;
                }
		int j = suf_mas[rank[i] + 1];
		while (std::max(i + k, j + k) < str.length() && str[i + k] == str[j + k]) {
            k++;
        }
		lcp[rank[i]] = k;
	}
    return lcp;
}

int main() {
    int n;
    std::cin >> n;
    ++n;
    std::string str;
    std::cin >> str;
    str += '#';
    std::vector<int> suf_mas(n, 0);
    suf_mas[0] = n-1;
    for (int i = 1; i < n; ++i) {
        std::cin >> suf_mas[i];
        --suf_mas[i];
    }
    std::vector<int> lcp = Kasai(str, suf_mas);
    for (int i = 1; i < n - 1; ++i) {
        std::cout << lcp[i] << " ";
    }
    return 0;
}