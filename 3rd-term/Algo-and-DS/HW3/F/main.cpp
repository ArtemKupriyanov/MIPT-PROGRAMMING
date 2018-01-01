#include <algorithm>
#include <vector>
#include <iostream>
#include <memory.h>

using namespace std;

const int N_MAX = 30000, M_MAX = 2000, K_MAX = 100000;

int n, m, k, girls_likes[K_MAX], girls_likes_2[K_MAX];
int pa[M_MAX], push_back[N_MAX];
vector<int> girs_vect[M_MAX], boys_vect[N_MAX];
int parosoch, array_parosoch[N_MAX];
int left_b = 0, right_b = 0, size = 0;

int have_new_parosoch(int vertex) {
    array_parosoch[vertex] = parosoch;
    for (int i = 0; i < girs_vect[vertex].size(); ++i) {
        if (left_b < girs_vect[vertex][i] && girs_vect[vertex][i] < right_b) {
            bool new_parosoch = (array_parosoch[push_back[girs_vect[vertex][i]]] != parosoch &&
                    have_new_parosoch(push_back[girs_vect[vertex][i]]));
            if (push_back[girs_vect[vertex][i]] == -1 || new_parosoch) {
                pa[vertex] = girs_vect[vertex][i];
                push_back[girs_vect[vertex][i]] = vertex;
                return 1;
            }
        }
    }
    return 0;
}

int dfs(int vertex) {
    array_parosoch[vertex] = parosoch;
    for (int i = 0; i < boys_vect[vertex].size(); ++i) {
        if (pa[boys_vect[vertex][i]] == -1 || (array_parosoch[pa[boys_vect[vertex][i]]] != parosoch &&
                dfs(pa[boys_vect[vertex][i]]))) {
            pa[boys_vect[vertex][i]] = vertex;
            push_back[vertex] = boys_vect[vertex][i];
            return 1;
        }
    }
    return 0;
}

int main() {
    cin >> n >> m >> k;
    memset(pa, -1, sizeof(pa));
    memset(push_back, -1, sizeof(push_back));
    for (int i = 0; i < k; ++i) {
        cin >> girls_likes[i] >> girls_likes_2[i];
        --girls_likes[i];
        --girls_likes_2[i];
        girs_vect[girls_likes_2[i]].push_back(girls_likes[i]);
        boys_vect[girls_likes[i]].push_back(girls_likes_2[i]);
    }

    int answer = 0;
    ++parosoch;
    while (right_b < n && size < m) {
        if (dfs(right_b++) == 1) {
            ++parosoch;
            ++size;
        }
    }
    while (size == m && left_b < n) {
        answer += n - right_b + 1;
        if (push_back[left_b] != -1) {
            pa[push_back[left_b]] = -1;
            ++parosoch;
            if (have_new_parosoch(push_back[left_b]) == 0) {
                --size;
                ++parosoch;
                while (right_b < n && size < m) {
                    if (dfs(right_b++) == 1) {
                        ++parosoch;
                        ++size;
                    }
                }
            }
        }
        ++left_b;
    }
    cout << answer;
    return 0;
}