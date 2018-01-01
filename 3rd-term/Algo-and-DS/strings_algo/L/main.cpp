#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <ctype.h>
#include <algorithm>

using namespace std;

const int nmax = 400000;

int s[nmax];
int n, m;

bool cmp(pair<int, int> a, pair<int, int> b) {
    return (a.second > b.second);
}

class SuffixAuto {
public:
    void sa_extend(char c);
    void count_cnts();
    void build();


    void find_refrain();

private:
    struct state {
        int len;
        int suf_link;
        int firstpos;
        bool cloned;
        map<int, int> next;

        state(int _len);
    };

    std::vector<state> states;
    int cnt[nmax], p[nmax], letter[nmax];
    bool used[nmax];
    long long int max_;
    int argmax;
    int last;
};

SuffixAuto::state::state(int _len)
        : len(_len),
          suf_link(-1),
          cloned(false) {}

void SuffixAuto::find_refrain() {
    max_ = 0;
    for (int i = 0; i < states.size(); i++)
        if ((long long int)(states[i].len) * (long long int)(cnt[i]) > max_)
        {
            max_ = (long long int)(states[i].len) * (long long int)(cnt[i]);
            argmax = i;
        }
    cout << max_ << endl;
    cout << states[argmax].len << endl;
    for (int i = states[argmax].firstpos - states[argmax].len + 1; i <= states[argmax].firstpos; i++)
        cout << s[i] << ' ';
    cout << endl;
}

void SuffixAuto::build() {
    for (int i = 0; i < n; ++i)
        sa_extend(s[i]);
}

void SuffixAuto::count_cnts() {
    int N = states.size();
    pair<int, int> *lens = new pair<int, int>[N];
    for (int i = 0; i < N; ++i)
    {
        lens[i].first = i;
        lens[i].second = states[i].len;
    }
    for (int i = 0; i < N; ++i)
        if (states[i].cloned)
            cnt[i] = 0;
        else
            cnt[i] = 1;
    sort(lens, lens + N, cmp);
    for (int i = 0; i < N; ++i) {
        int k = lens[i].first;
        cnt[states[k].suf_link] += cnt[k];
    }
}

void SuffixAuto::sa_extend(char c) {
    int cur = states.size();
    states.push_back(state(states[last].len + 1));
    states[cur].firstpos = states[cur].len - 1;
    int p;
    for (p = last; ((p != -1) && !states[p].next.count(c)); p = states[p].suf_link) {
        states[p].next[c] = cur;
    }
    if (p == -1) {
        states[cur].suf_link = 0;
    }
    else {
        int q = states[p].next[c];
        if (states[p].len + 1 == states[q].len) {
            states[cur].suf_link = q;
        } else {
            int clone = states.size();
            states.push_back(states[q]);
            states[clone].len = states[p].len + 1;
            states[clone].firstpos = states[q].firstpos;
            states[clone].cloned = true;
            for (; ((p != -1) && (states[p].next.find(c) != states[p].next.end()) && (states[p].next[c] == q)); p = states[p].suf_link)
                states[p].next[c] = clone;
            states[cur].suf_link = clone;
            states[q].suf_link = clone;
        }
    }
    last = cur;
}

int main() {
    SuffixAuto aut;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    aut.build();
    aut.count_cnts();
    aut.find_refrain();
    return 0;
}
