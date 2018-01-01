#include <stdio.h>
#include "sqlite3.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* szSql;
const char* tail;
sqlite3_stmt* st;

string read_file(string file_name) {
    ifstream fin(file_name.c_str());
    if (!fin.is_open()) {
        cout << "can't read file";
        return "\n";
    }
    string answer;
    char symbol;
    while (!fin.eof()) {
        fin.read(&symbol, 1);
        answer.push_back(symbol);
    }
    return answer;
}

int main(int argc, char** argv) {
    int rc;
    string directory_name = "/home/artem/Desktop/DataBases/programming/3_BIND/Bind/";
    string file_name = "test.SQL";

    string szSql_str = read_file(directory_name + file_name);

    sqlite3 *db;
    szSql = szSql_str.c_str();
    tail = szSql;

    rc = sqlite3_open("db", &db);
    //cout << "tail: " << tail << endl << "szSql: " << szSql << endl;
    if (rc != SQLITE_OK) {
        return 1;
    }
    while (strlen(tail) != 0) {
        rc = sqlite3_prepare(db, szSql, -1, &st, &tail);
        //cout << "tail: " << strlen(tail) << endl;
        if (rc != SQLITE_OK) {
            cout << "preparing failed!" << endl;
            return 2;
        }

        szSql = tail;
        if (!strlen(tail)) {
            break;
        }
        int nColCnt = sqlite3_column_count(st);
        while (true) {
            rc = sqlite3_step(st);
            if (rc != SQLITE_ROW) {
                break;
            }
            for (int iCol = 0; iCol < nColCnt; ++iCol) {
                cout << sqlite3_column_name(st, iCol) << " " << sqlite3_column_text(st, iCol) << endl;
            }
            cout << endl;
        }
        if (rc != SQLITE_DONE) {
            return 3;
        }
        sqlite3_finalize(st);
    }

    szSql = "select * from Players where weight_lbs > ? and height < ?;";

    rc = sqlite3_prepare(db, szSql, -1, &st, &tail);
    int param1;
    double param2;
    cout << "weight, height" << endl;
    cin >> param1 >> param2;
    int rc1 = sqlite3_bind_int(st, 1, param1);
    int rc2 = sqlite3_bind_double(st, 2, param2);

    if (rc != SQLITE_OK) {
        return 2;
    }

    if (rc1 != SQLITE_OK || rc2 != SQLITE_OK) {
        return 3;
    }

    int nColCnt = sqlite3_column_count(st);
    while (1) {
        rc = sqlite3_step(st);
        if (rc != SQLITE_ROW) {
            break;
        }
        int iCol = 0;
        for (iCol; iCol < nColCnt; ++iCol) {
            cout << sqlite3_column_name(st, iCol) << sqlite3_column_text(st, iCol) << endl;
        }
        cout << endl;
    }
    if (rc != SQLITE_DONE) {
        return 4;
    }
    sqlite3_finalize(st);
    return 0;
}
