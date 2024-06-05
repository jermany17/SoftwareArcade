#pragma once
#include <sqlite3.h>
#include <stdio.h>

void initDatabase(const char* db_name);


void initDatabase(const char* db_name) {
	sqlite3* db;
	char* err_msg = 0;
	int sqlite_returncode;

    sqlite_returncode = sqlite3_open(db_name, &db);         // 데이터베이스 열기 또는 생성하기

	if (sqlite_returncode != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

    const char* sql_create_tables =                         // 테이블 생성 SQL문
        "CREATE TABLE IF NOT EXISTS SnakeHighScores ("
        "score INTEGER NOT NULL);"
        "CREATE TABLE IF NOT EXISTS TetrisHighScores ("
        "score INTEGER NOT NULL);"
        "CREATE TABLE IF NOT EXISTS TicTacToeScores ("
        "player_wins INTEGER NOT NULL, "
        "computer_wins INTEGER NOT NULL, "
        "draws INTEGER NOT NULL);";

    sqlite_returncode = sqlite3_exec(db, sql_create_tables, 0, 0, &err_msg);    // 테이블 생성

    if (sqlite_returncode != SQLITE_OK) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    const char* sql_insert_initial_values =                  // 초기값 삽입 SQL문
        "INSERT INTO SnakeHighScores (score) "
        "SELECT 0 WHERE NOT EXISTS (SELECT 1 FROM SnakeHighScores);"
        "INSERT INTO TetrisHighScores (score) "
        "SELECT 0 WHERE NOT EXISTS (SELECT 1 FROM TetrisHighScores);"
        "INSERT INTO TicTacToeScores (player_wins, computer_wins, draws) "
        "SELECT 0, 0, 0 WHERE NOT EXISTS (SELECT 1 FROM TicTacToeScores);";

    sqlite_returncode = sqlite3_exec(db, sql_insert_initial_values, 0, 0, &err_msg);        // 초기값 삽입

    if (sqlite_returncode != SQLITE_OK) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);          // 데이터베이스 닫기

}

int getHeightScore(const char* db_name, const char* gameName) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int sqlite_returncode;
    int highestScore = 0;
    char sql[256];

    sqlite_returncode = sqlite3_open(db_name, &db);
    if (sqlite_returncode != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    snprintf(sql, sizeof(sql), "SELECT MAX(score) FROM %sHighScores;", gameName);

    sqlite_returncode = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (sqlite_returncode != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite_returncode = sqlite3_step(stmt);
    if (sqlite_returncode == SQLITE_ROW) {
        highestScore = sqlite3_column_int(stmt, 0);
    }
    else {
        printf("Failed to get data: %s\n", sqlite3_errmsg(db));
    }

    sqlite_returncode = sqlite3_step(stmt);
    if (sqlite_returncode == SQLITE_ROW) {
        highestScore = sqlite3_column_int(stmt, 0);
    }
    else {
        printf("Failed to get data: %s\n", sqlite3_errmsg(db));
    }

    sqlite_returncode = sqlite3_step(stmt);
    if (sqlite_returncode == SQLITE_ROW) {
        highestScore = sqlite3_column_int(stmt, 0);
    } else {
        printf("Failed to get data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
    return highestScore;

}