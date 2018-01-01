#include <iostream>
#include <vector>
#include <limits.h>
#include <set>

using namespace std;

const int day_length = 24;

//минимальная мера - 1 час

struct information {
    int from;
    int to;
    int time_departure;
    int time_arrival;

    information ()
            : from(0),
              to(0),
              time_departure(0),
              time_arrival(0) {}

    information(int from, int to, int time_departure, int time_arrival)
            : from(from),
              to(to),
              time_departure(time_departure),
              time_arrival(time_arrival) {}
};

void read_data(vector <vector <information> >& info, int& n, int& a, int& b, int& start_time) {
    cout << "size, count ways, from, to, start_time" << endl;
    int count_ways;
    cin >> n >> count_ways >> a >> b >> start_time;
    info.resize(n);
    int from, to, time_departure, time_arrival;
    for (int i = 0; i < count_ways; ++i) {
        cin >> from >> to >> time_departure >> time_arrival;
        if (time_departure > time_arrival) {
            time_arrival += day_length;
        }
        information tmp(from, to, time_departure, time_arrival);
        info[from].push_back( tmp );
    }
}

void print_info (vector <vector <information> >& info) {
    for (int i = 0; i < info.size(); ++i) {
        for (int j = 0; j < info.size(); ++j) {
            cout << " time depature: " << info[i][j].time_departure << " time arrive: " << info[i][j].time_arrival;
        }
        cout << endl;
    }
}

//считает сколько дней (в часах) нужно ждать
int wait(int arrival, int departure) {
    int answer = (arrival / 24) * 24; //количество дней (в часах)
    if (arrival % 24 < departure) {
        return answer;
    }
    return answer + 24;
}

void dijkstra_algo (vector<vector<information> >& info, vector<int>& time, int size, int from, int start_time) {
    time[from] = start_time;
    set< pair<int, int> > unused;
    //unused.insert(make_pair(time[from], from));
    for (int i = 0; i < info[from].size(); ++i) {
        if (wait(time[from], info[from][i].time_departure) > 0 ) {
            time[info[from][i].to] =
                    wait(time[from], info[from][i].time_departure) - start_time + info[from][i].time_arrival;
        } else {
            time[info[from][i].to] = info[from][i].time_arrival;
        }
        unused.insert(make_pair( time[info[from][i].to], info[from][i].to ) );
    }
    while ( !unused.empty() ) {
        pair <int, int> city = *unused.begin();
        int city_number = city.second;
        unused.erase( unused.begin() );
        for (int j = 0; j < info[city_number].size(); ++j) {
            int now_time_to_next_city = time[ info[city_number][j].to ];
            if (now_time_to_next_city > wait(time[city_number], info[city_number][j].time_departure ) +
                    info[city_number][j].time_arrival) {
                now_time_to_next_city = wait(time[city_number], info[city_number][j].time_departure ) +
                                        info[city_number][j].time_arrival;
                time[ info[city_number][j].to ] = now_time_to_next_city;
                unused.insert(make_pair(time[ info[city_number][j].to ], info[city_number][j].to ));
            }
        }
    }
}

int main() {
    vector <vector <information> > info;
    int n, a, b, start_time;
    read_data(info, n, a, b, start_time);
    vector<int> time(n, INT_MAX);
    //print_info(info);
    dijkstra_algo(info, time, n, a, start_time);
    if (time[b] == INT_MAX) {
        cout << "Нет пути" << endl;
    } else {
        cout << time[b];
    }
    return 0;
}
