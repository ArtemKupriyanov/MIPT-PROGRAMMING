#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> prefix_function (std::string str) {
    std::vector<int> prefix (str.length());
    for (int i = 1; i < str.length(); ++i) {
        int j = prefix[i-1];
        while (j > 0 && str[i] != str[j]) {
            j = prefix[j-1];
        }
        if (str[i] == str[j])  {
            ++j;
        }
        prefix[i] = j;
    }
    return prefix;
}

std::vector<int> z_function(std::string str) {
    int n_size = str.length();
    std::vector<int> zet(n_size, 0);
    for (int i = 1, l = 0, r = 0; i < n_size; ++i) {
        if (i <= r) {
            zet[i] = std::min(r - i + 1, zet[i - l]);
        }
        while (i+zet[i] < n_size && str[zet[i]] == str[i+zet[i]]) {
            ++zet[i];
        }
        if (i+zet[i]-1 > r) {
            l = i;
            r = i + zet[i] - 1;
        }
    }
    return zet;
}

std::vector<int> kmp(std::string text, std::string pattern) {
    std::vector<int> responce_array;
    int text_length = text.length(), pattern_length = pattern.length();
    std::vector<int> prefix_vect = prefix_function(pattern + "#" + text);
    int cnt = 0;
    for (int i = 0; i < text_length; ++i) {
        if (prefix_vect[pattern_length + i + 1] == pattern_length) {
            responce_array.push_back(i);
            cnt++;
        }
    }
    return responce_array;
}

int main () {
    std::string str;
    std::cin >> str;

    std::string tie_reverse = str.substr(2, str.size() - 2);
    std::reverse(tie_reverse.begin(), tie_reverse.end());
    std::string for_all = str.substr(0, 2);

    std::vector<int> zet = z_function(tie_reverse);
    std::vector<int> prefix = prefix_function(tie_reverse);

    int length_period = 0;
    int min_length = tie_reverse.size();

    for (int i = 1; i < tie_reverse.size(); ++i) {
        int k = i - prefix[i] + 1;
        int j = i;

        if (i < tie_reverse.size() - 1) {
            j += zet[i + 1];
        }

        if ( (i + 1) % k == 0 && k + tie_reverse.size() - j - 1 < min_length) {
            min_length = k + tie_reverse.size() - j - 1;
            length_period = j;
        }

        else if (i + tie_reverse.size() - j < min_length) {
            min_length = i + tie_reverse.size() - j;
            length_period = j;
        }
    }
    std::cout << for_all;
    length_period = str.size() - 1 - length_period;
    min_length += 2;
    for (int i = 2; i < length_period; ++i) {
        std::cout << str[i];
    }
    std::cout << "(";
    for (int i = length_period; i < min_length; ++i) {
        std::cout << str[i];
    }
    std::cout << ")\n";
    return 0;
}