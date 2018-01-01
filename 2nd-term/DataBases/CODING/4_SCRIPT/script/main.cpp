#include <stdio.h>
#include "sqlite3.h"
#include <iostream>
#include <fstream>

//create table db (login varchar(32), password varchar(32))
//insert into db (login, password) (\"artem\", \"1234\")
//select * from db
const char* szSql = "";
const char* tail;
sqlite3_stmt* st;

void read_file() {
	ifstream fin("test.SQL");
	cout << szSql;
	//записать с потака в строку
	//тейл отрезает часть запроса, которая еще не подгортовилась
}

using namespace std;

int main(int argc, char** argv) {
	int rc;
	sqlite3 *db;
	rc = sqlite3_open("db", &db);

	if (rc != SQLITE_OK) {
		return 1;
	}

	tail = szSql;
	
	rc = sqlite3_prepare(
		db, /* Database handle */
		tail,  /* SQL statement, UTF-8 encoded */
		/* SQL statement, UTF-8 encoded */
		-1, /* Maximum length of zSql in bytes. */
		&st, /* OUT: Statement handle */
		&tail /* OUT: Pointer to unused portion of zSql */
		);

	if (rc != SQLITE_OK) {
		return 1;
	}

	int nColCnt = sqlite3_column_count(st);

	while ( true ) {
		rc = sqlite3_step(st);
		if (rc != SQLITE_ROW) {
			break;
		}
		for (int iCol = 0; iCol < nColCnt; ++iCol) {
			cout << sqlite3_column_name(st, iCol) << sqlite3_column_text(st, iCol) << endl;
		}
		cout << endl;
	}

	printf("%d\n", rc);
	if (rc != SQLITE_DONE) {
		
		return 1;
	}
	sqlite3_close(db);
	return 0;
}