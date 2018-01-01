#include <iostream>
#include <vector>
#include <string>

const int bor_size = 30;
int ans;

class Bor {
public:
    Bor();
    bool is_terminal;
    int n_tree;
    std::vector<Bor*> tree_;
};

Bor::Bor()
        : is_terminal(false),
          n_tree(0) {
    tree_.resize(bor_size, nullptr);
}

Bor* root;

std::vector<int> z_func_algo(std::string &str) {
    int n_size = str.length();
    std::vector<int> z_function(n_size, 0);
    for (int i = 1, l = 0, r = 0; i < n_size; ++i) {
        if (i <= r) {
            z_function[i] = std::min(r - i + 1, z_function[i - l]);
        }
        while (i+z_function[i] < n_size && str[z_function[i]] == str[i+z_function[i]]) {
            ++z_function[i];
        }
        if (i+z_function[i]-1 > r) {
            l = i;
            r = i + z_function[i] - 1;
        }
    }
    return z_function;
}

void add_str(Bor* node, const std::string &str, int position) {
    if(position == str.size()) {
        node->is_terminal = true;
        node->n_tree = 1;
        return;
    }
    if (node->tree_[str[position] - 'a'] != nullptr) {
        add_str(node->tree_[str[position] - 'a'], str, position + 1);
        ++node->n_tree;
    } else {
        node->tree_[str[position] - 'a'] = new Bor();
        add_str(node->tree_[str[position] - 'a'], str, position + 1);
        ++node->n_tree;
    }
}

void detour_bor(Bor* node) {
    if(node == nullptr) {
        return;
    }
    if(node != root) {
        ++ans;
    }
    for(int i = 0; i < bor_size; ++i) {
        detour_bor(node->tree_[i]);
    }
}

int main() {
    std::string str;
    std::cin >> str;
    root = new Bor();
    for(int i = 1; i < str.size(); ++i) {
        std::string pattern, text;
        pattern = str.substr(0, i);
        text = str.substr(i, str.size());
        std::string parse  = text + "#" + pattern;
        std::vector<int> z_function = z_func_algo(parse);
        int max = 0;
        for(int j = text.size(); j <= str.size(); ++j) {
            if (z_function[j] > max) {
                max = z_function[j];
            }
        }
        add_str(root,
                text.substr(0, max),
                0);
    }
    detour_bor(root);
    std::cout << ans << std::endl;
    return 0;
}