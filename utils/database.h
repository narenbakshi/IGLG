/**
 * @file database.h
 * @brief Header file containing  function calls for database access.
 *
 * This file is a header file for accessing the databse. The database name is taken from the cofigurations.
 * 
 * @author Naren Bakshi
 * @date 23 Nov 2020
 */ 
#ifndef DATABASE
#define DATABASE

#include <sqlite3.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#include <stdbool.h>
#include "../benchmarking/probeBench.h"

int first_row;

/**
 * @brief Function for create table callback.
 * @return static int :Status of the callback
 */
static int callback(void *, int argc, char **, char **);



/**
 * @brief Function for select callback.
 * @return int: Status of the callback
 */
//int select_callback(void *, int , char **, char **);

/**
 * @brief Function for select statment to read database.
 * @param stmt Statement string.
 * @param db Database pointer.
 * @return void: Returns nothing.
 */
void select_stmt(const char*, sqlite3*);

/**
 * @brief Function for check statment to read database.
 * @param stmt1 Statement string.
 * @param db Database pointer.
 * @param buffer Buffer pointer contains the syscalls.
 * @return bool: Returns match_found if syscalls are present.
 */
bool check_stmt(const char*, sqlite3*, char** );


/**
 * @brief Function to check the table exist.
 * @param tbl_name Table Name.
 * @param db Database pointer.
 * @return bool: Returns boolean.
 */
bool check_table_exist(char* tbl_name, sqlite3* db);

/**
 * @brief Function to create table for database,
 * It drops the previous table and create a new with windowsize columns.
 * @param windowsize Size of the window.
 * @param db Database pointer.
 * @return void: Returns nothing.
 */
void create_table(int, sqlite3* );

/**
 * @brief Function to create insert query for database.
 * @param windowsize Size of the window.
 * @return char*: Returns the query string.
 */
char* create_insert(int );

/**
 * @brief Function to insert the buffer filled with system call into the database.
 * @param syscall Array pointer of system calls.
 * @param insert Insert query string.
 * @param db Database pointer.
 * @return int: Returns 0 if successfull.
 */
int insert_syscall(char **, char *, sqlite3*);

#endif