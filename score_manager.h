#pragma once
#include <sqlite3.h>
#include <stdio.h>

void initDatabase(const char* db_name);


void initDatabase(const char* db_name) {
	sqlite3* db;
	char* err_msg = 0;
	int sqlite_returncode;

    // 데이터베이스 열기 또는 생성하기
    sqlite_returncode = sqlite3_open(db_name, &db);

	if (sqlite_returncode != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

    // 테이블 생성 SQL문
    const char* sql_create_tables =
        "CREATE TABLE IF NOT EXISTS SnakeHighScores ("
        "score INTEGER NOT NULL);"
        "CREATE TABLE IF NOT EXISTS TetrisHighScores ("
        "score INTEGER NOT NULL);"
        "CREATE TABLE IF NOT EXISTS TicTacToeScores ("
        "player_wins INTEGER NOT NULL, "
        "computer_wins INTEGER NOT NULL, "
        "draws INTEGER NOT NULL);";

    // 테이블 생성
    sqlite_returncode = sqlite3_exec(db, sql_create_tables, 0, 0, &err_msg);

    if (sqlite_returncode != SQLITE_OK) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    // 초기값 삽입 SQL문
    const char* sql_insert_initial_values =
        "INSERT INTO SnakeHighScores (score) "
        "SELECT 0 WHERE NOT EXISTS (SELECT 1 FROM SnakeHighScores);"
        "INSERT INTO TetrisHighScores (score) "
        "SELECT 0 WHERE NOT EXISTS (SELECT 1 FROM TetrisHighScores);"
        "INSERT INTO TicTacToeScores (player_wins, computer_wins, draws) "
        "SELECT 0, 0, 0 WHERE NOT EXISTS (SELECT 1 FROM TicTacToeScores);";

    // 초기값 삽입
    sqlite_returncode = sqlite3_exec(db, sql_insert_initial_values, 0, 0, &err_msg);

    if (sqlite_returncode != SQLITE_OK) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    // 데이터베이스 닫기
    sqlite3_close(db);

}