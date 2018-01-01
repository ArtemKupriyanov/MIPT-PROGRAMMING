#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using std::vector;
using std::min;
using std::make_pair;

class Edge {
public:
    int from;
    int to;
    int capacity;
    int flow;
    int reverseInd;
};

vector<vector<Edge>> gr;
vector<int> skip;
vector<int> distance;
vector<vector<int>> capacity;
int maxFlow;
int start, finish;

int dinica(int v, int min)
{
    if (v == finish)
    {
        maxFlow += min;
        return min;
    }

    for (size_t i = skip[v]; i < gr[v].size(); ++i)
    {
        if ((gr[v][i].capacity - gr[v][i].flow > 0) && (distance[v] + 1 == distance[gr[v][i].to]))
        {
            int result = dinica(gr[v][i].to, min(min, gr[v][i].capacity - gr[v][i].flow));
            if (result > 0)
            {
                gr[v][i].flow += result;
                gr[gr[v][i].to][gr[v][i].reverseInd].flow -= result;
                return result;
            }
            else
            {
                ++skip[v];
            }
        }
    }
    return 0;
}

void maximalFlow(int n)
{
    skip.assign(n + 1, 0);
    while (2 * 2 == 4)
    {
        queue<pair<int, int>> bfs;
        distance.assign(n + 1, 2000000000);
        skip.assign(n + 1, 0);
        bfs.push(make_pair(start, 0));
        distance[start] = 0;
        while (bfs.size() != 0)
        {
            pair<int, int> tmp = bfs.front();
            bfs.pop();
            for (size_t i = 0; i < gr[tmp.first].size(); ++i)
            {
                if ((distance[gr[tmp.first][i].to] > distance[tmp.first] + 1) && (gr[tmp.first][i].capacity - gr[tmp.first][i].flow > 0))
                {
                    distance[gr[tmp.first][i].to] = distance[tmp.first] + 1;
                    bfs.push(make_pair(gr[tmp.first][i].to, distance[tmp.first] + 1));
                }
            }
        }
        if (distance[finish] == 2000000000)
            break;
        while (dinica(start, 2000000000) > 0)
        {

        }
    }
    distance.clear();
    skip.clear();
}

class sym
{
public:
    char c;
    int col;
    int num;
};

int valent(char c)
{
    if(c == 'O')
        return 2;
    if(c == 'H')
        return 1;
    if(c == 'N')
        return 3;
    if(c == 'C')
        return 4;
    return 0;
}

int main()
{
    int n, m;
    int cnt = 0;
    cin >> n >> m;
    vector < vector<sym>> chem;
    chem.resize(n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            char c;
            cin >> c;
            if (c != '.')
            {
                ++cnt;
                chem[i].push_back({ c, (int)(i + j) % 2, cnt + 1});
            }
            else
            {
                chem[i].push_back({ c, (int)(i + j) % 2, 0 });
            }
        }
    }

    gr.resize(cnt + 3);

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            if (chem[i][j].col == 0 && chem[i][j].c != '.')
            {
                if(i > 0)
                if (chem[i - 1][j].c != '.')
                {
                    gr[chem[i][j].num].push_back({ chem[i][j].num, chem[i - 1][j].num, 1, 0, (int)gr[chem[i - 1][j].num].size() });
                    gr[chem[i - 1][j].num].push_back({ chem[i - 1][j].num, chem[i][j].num, 0, 0, (int)gr[chem[i][j].num].size() - 1 });
                }
                if(i < n - 1)
                if (chem[i + 1][j].c != '.')
                {
                    gr[chem[i][j].num].push_back({ chem[i][j].num, chem[i + 1][j].num, 1, 0, (int)gr[chem[i + 1][j].num].size() });
                    gr[chem[i + 1][j].num].push_back({ chem[i + 1][j].num, chem[i][j].num, 0, 0, (int)gr[chem[i][j].num].size() - 1 });
                }
                if (j > 0)
                if (chem[i][j - 1].c != '.')
                {
                    gr[chem[i][j].num].push_back({ chem[i][j].num, chem[i][j - 1].num, 1, 0, (int)gr[chem[i][j - 1].num].size() });
                    gr[chem[i][j - 1].num].push_back({ chem[i][j - 1].num, chem[i][j].num, 0, 0, (int)gr[chem[i][j].num].size() - 1 });
                }
                if(j < m - 1)
                if (chem[i][j + 1].c != '.')
                {
                    gr[chem[i][j].num].push_back({ chem[i][j].num, chem[i][j + 1].num, 1, 0, (int)gr[chem[i][j + 1].num].size() });
                    gr[chem[i][j + 1].num].push_back({ chem[i][j + 1].num, chem[i][j].num, 0, 0, (int)gr[chem[i][j].num].size() - 1 });
                }
            }
        }
    }
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            if (chem[i][j].c != '.' && chem[i][j].col == 0)
            {
                gr[1].push_back({ 1, chem[i][j].num, valent(chem[i][j].c), 0, (int)gr[chem[i][j].num].size() });
                gr[chem[i][j].num].push_back({ chem[i][j].num, 1, 0, 0, (int)gr[1].size() - 1 });
            }
            if (chem[i][j].c != '.' && chem[i][j].col == 1)
            {
                gr[chem[i][j].num].push_back({ chem[i][j].num, cnt + 2, valent(chem[i][j].c), 0, (int)gr[cnt + 2].size() });
                gr[cnt + 2].push_back({ cnt + 2, chem[i][j].num, 0, 0, (int)gr[chem[i][j].num].size() - 1 });
            }
        }
    }
    start = 1;
    finish = cnt + 2;
    maximalFlow(cnt + 2);
    bool f = true;
    for(size_t i = 0; i < gr[1].size(); ++i)
    {
        if(gr[1][i].capacity > 0 && gr[1][i].flow < gr[1][i].capacity)
        {
            f = false;
            break;
        }
    }
    for(size_t i = 2; i < cnt + 2; ++i)
    {
        if(!f)
            break;
        for(size_t j = 0; j < gr[i].size(); ++j)
        {
            if(gr[i][j].to == cnt + 2 && gr[i][j].capacity > 0 && gr[i][j].flow < gr[i][j].capacity)
            {
                f = false;
                break;
            }
        }
    }
    if(f && (cnt >= 1))
        cout << "Valid" << endl;
    else
        cout << "Invalid" << endl;
    return 0;
}