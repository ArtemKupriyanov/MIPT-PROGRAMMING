#include <stdio.h>
#include "sqlite3.h"

const char* szSql = "SELECT * FROM moz_places";
const char* tail;
sqlite3_stmt* st;

int main(int argc, char** argv) {
    int rc;
    sqlite3 *db;
    rc = sqlite3_open("places.sqlite", &db);

    if ( rc != SQLITE_OK ) {
        return 1;
    }

    rc = sqlite3_prepare(
            db, /* Database handle */
            szSql,  /* SQL statement, UTF-8 encoded */
            /* SQL statement, UTF-8 encoded */
            -1, /* Maximum length of zSql in bytes. */
            &st, /* OUT: Statement handle */
            &tail /* OUT: Pointer to unused portion of zSql */
    );

    if ( rc != SQLITE_OK ) {
        return 1;
    }

    int nColCnt = sqlite3_column_count(st);

    while ( 1 ) {
        rc = sqlite3_step(st);
        if (rc != SQLITE_ROW) {
            break;
        }
        for (int iCol = 0; iCol < nColCnt; ++iCol) {
            printf("%s%s\n", sqlite3_column_name(st, iCol), sqlite3_column_text(st, iCol));
        }
        printf("\n");
    }

    if ( rc != SQLITE_DONE ) {
        return 1;
    }
    sqlite3_close(db);
    return 0;
}