#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

const char* szSql = "SELECT ? id FROM T WHERE login = ? AND password = ?";
const char* tail;
sqlite3_stmt* st;

int str_size(char* str) {
    for (int i = 0; i < 50; ++i) {
        if (str[i] == '\0') {
            return i;
        }
    }
    return  -1;
}

int main(int argc, char** argv) {
    int rc;
    sqlite3 *db;
    rc = sqlite3_open("temp.sqlite", &db);
    if ( rc != SQLITE_OK ) {
        return 1;
    }
    rc = sqlite3_prepare(
            db,
            szSql,
            -1,
            &st,
            &tail
    );
    char* login;
    char* password;
    login = (char*)malloc(50*sizeof(char));
    password = (char*)malloc(50*sizeof(char));
    scanf("%s", login);
    scanf("%s", password);
    int login_size = str_size(login);
    int password_size = str_size(password);
    int r1 = sqlite3_bind_text(st, 1, login, login_size, NULL);
    int r2 = sqlite3_bind_text(st, 2, password, password_size, NULL);

    if (rc != SQLITE_OK) {
        return 1;
    }
    int nColCnt = sqlite3_column_count(st);
    while ( 1 ) {
        rc =sqlite3_step(st);
        if (rc != SQLITE_ROW) {
            break;
        }
        for (int iCol = 0; iCol < nColCnt; ++iCol) {
            printf("%s%s\n", sqlite3_column_name(st, iCol), sqlite3_column_text(st, iCol));
        }
        printf("\n");
    }
    if (rc != SQLITE_DONE) {
        return -1;
    }
    sqlite3_close(db);
    return 0;
}