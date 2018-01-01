#include <iostream>
#include <vector>
#include <string>
#include <map>

const int bor_size = 27;

class HurdBor {
public:
    HurdBor() {}
    HurdBor(HurdBor* parent_, char to_parent_);

    HurdBor* parent;
    HurdBor* suff_link;

    char to_parent;
    bool was_counted;
    long long int n_term;
    bool is_terminal;

    std::vector<HurdBor*> children;
    std::vector<HurdBor*> next;

    std::vector<int> pattern_num;

    ~HurdBor();
};

HurdBor::~HurdBor() {
    delete suff_link;
    delete parent;
}

HurdBor::HurdBor(HurdBor *parent_, char to_parent_)
        : parent(parent_),
          to_parent(to_parent_),
          suff_link(NULL),
          n_term(0),
          is_terminal(false),
          was_counted(false)
{
    children.assign(bor_size, NULL);
    next.assign(bor_size, NULL);
}

HurdBor* root;

HurdBor* set_links(HurdBor *vertex, char c);
HurdBor* set_suffix_links(HurdBor *vertex);
void add_string(const std::string &str, int pattern_number);
long long int get_string_cnt(HurdBor *vertex);
bool dfs(HurdBor* vertex);
std::map<HurdBor*, int> colors;

int main() {
    int n;
    std::cin >> n;
    root = new HurdBor(NULL, '0');
    for(int i = 0; i < n; ++i) {
        std::string str;
        std::cin >> str;
        add_string(str, i);
    }
    if ( dfs(root) == true ) {
        std::cout << "TAK" << std::endl;
    } else {
        std::cout << "NIE" << std::endl;
    }
    return 0;
}

bool dfs(HurdBor* vertex) {
    colors[vertex] = 1;
    for (int i = 0; i < 2; ++i) {
        HurdBor* next = set_links(vertex, (char)(i + '0'));
        if(colors.count(next) == 0 && get_string_cnt(next) == 0) {
            if(dfs(next) == true) {
                return true;
            }
        } else if(get_string_cnt(next) == 0 && colors[next] == 1) {
            return true;
        }
    }
    colors[vertex] = 2;
    return false;
}

HurdBor* set_links(HurdBor *vertex, char c) {
    int step = c - '0';
    if(vertex->next[step] == NULL) {
        if(vertex->children[step] != NULL) {
            vertex->next[step] = vertex->children[step];
        } else if (vertex == root) {
            vertex->next[step] = root;
        } else {
            vertex->next[step] = set_links(set_suffix_links(vertex), c);
        }
    }
    return vertex->next[step];
}


HurdBor* set_suffix_links(HurdBor *vertex) {
    if(vertex == NULL) {
        return NULL;
    }
    if(vertex->suff_link == NULL) {
        if(vertex == root || vertex->parent == root) {
            vertex->suff_link = root;
        } else {
            vertex->suff_link = set_links(set_suffix_links(vertex->parent),
                                         vertex->to_parent);
        }
    }
    return vertex->suff_link;
}


void add_string(const std::string &str, int pattern_number) {
    HurdBor* cur = root;
    for(int i = 0; i < str.size(); ++i) {
        char c = str[i];
        int step = c - '0';
        if (cur->children[step] == NULL) {
            cur->children[step] = new HurdBor(cur, c);
        }
        cur = cur->children[step];
    }
    cur->is_terminal = true;
    cur->pattern_num.push_back(pattern_number);
}


long long int get_string_cnt(HurdBor *vertex) {
    if(vertex == NULL) {
        return 0;
    }

    if (vertex->was_counted == false) {
        vertex->was_counted = true;
        if (vertex == root) {
            vertex->n_term = 0;
        } else {
            if(vertex->is_terminal == true) {
                vertex->n_term += vertex->pattern_num.size();
            }
            vertex->n_term += get_string_cnt(set_suffix_links(vertex));
        }
    }
    return vertex->n_term;
}