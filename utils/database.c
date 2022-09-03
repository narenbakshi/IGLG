/**
 * @file database.c
 * @brief File containing functionality to access database.
 *
 * This file is used to access database with create database , table and select query.
 * 
 * @author Naren Bakshi
 */ 
#include "database.h"

/**
 * @brief Function for callback .
 * @param NotUsed Pointer Not Used.
 * @param argc Arguments count.
 * @param argv Arguments value.
 * @param azColName Pointer for choosing Argument  .
 * @return int: Returns static int.
 */


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}






/**
 * @brief Function to check the select statment.
 * @param stmt1 Pointerfor statment.
 * @param db Database pointer.
 * @param buffer char pointer for buffer.
 * @return bool: Returns boolean.
 */
bool check_stmt(const char* stmt1,sqlite3* db, char** buffer) 
{
  int  windowsize = 3,i;
  bool match_found = false;
  int                  bytes;
  const unsigned char* text; 
  int                  row = 0;
  sqlite3_stmt *stmt;
  if (sqlite3_prepare(db,stmt1, -1,&stmt, 0 ) != SQLITE_OK) 
    {
      printf("\nCould not prepare statement.");
    }

  bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
        case SQLITE_ROW:
            bytes = sqlite3_column_bytes(stmt, 0);
            for(i = 0; i< windowsize;i++)
            {
              text  = sqlite3_column_text(stmt, i);
              if(strcmp((const char*)text,buffer[i]) == 0)
              {
                match_found = true;
              }
              else
              {
                printf("\n not found \n");
                match_found = false;
                break;
              }
            }       
            row++;
            break;
        case SQLITE_DONE:
            done = true;
            break;
        default:
            fprintf(stderr, "Failed.\n");
        }
        if(match_found == true)
        {
          
          sqlite3_finalize(stmt);
          return match_found;
          
        }
    }
   sqlite3_finalize(stmt);
  return match_found;
}

/**
 * @brief Function to check the table exist.
 * @param tbl_name Table Name.
 * @param db Database pointer.
 * @return bool: Returns boolean.
 */
bool check_table_exist(char* tbl_name, sqlite3* db)
{
  sqlite3_stmt *stmt;
  bool found = false;
  const char *sql = "SELECT 1 FROM sqlite_master where type='table' and name=?";

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    printf("error: ", sqlite3_errmsg(db));
    return found;
  }
  sqlite3_bind_text(stmt, 1, tbl_name, -1, SQLITE_TRANSIENT);

  rc = sqlite3_step(stmt);
  
  if (rc == SQLITE_ROW)
    found = true;
  else if (rc == SQLITE_DONE)
    found = false;
  else {
    printf("error: ", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return found;
  }

  sqlite3_finalize(stmt);
  return found;
}


/**
 * @brief Function to Create table including drop of previous table.
 * @param windowsize Size of the Window.
 * @param db Database pointer.
 * @return void: Returns void.
 */
void create_table(int windowsize, sqlite3* db)
{

  char *start = "DROP TABLE IF EXISTS PROCESS; \
  CREATE TABLE IF NOT EXISTS PROCESS(";
  char *mid = (char*)malloc(windowsize * 24);
  char *end = (char*)malloc(windowsize * 10);
	char *temp1 = (char*)malloc(windowsize * 10);
  char *temp2 = (char*)malloc(windowsize * 10);

  char *sql = NULL;
  int rc, i;
  char *zErrMsg = 0;
/* Create table  */
  for(i=0; i<windowsize -1; i++)
  { 
    asprintf(&temp1,"syscall%d TEXT NOT NULL,", i );
    asprintf(&temp2,"syscall%d,", i );
    if(i==0)
    {
      asprintf(&mid,"%s",temp1);
      asprintf(&end,"%s",temp2);
    }
    else
    {
      asprintf(&mid,"%s %s", mid,temp1);
      asprintf(&end,"%s %s", end,temp2);
    }
  }
	asprintf(&temp1,"syscall%d TEXT NOT NULL,", windowsize -1 );
	asprintf(&mid, "%s %s", mid,temp1);
	asprintf(&temp2, "syscall%d", windowsize -1 );
  asprintf(&end, "%s %s", end,temp2);
  asprintf(&sql,"%s%s PRIMARY KEY (%s));",start ,mid,end);

	printf("Query = %s",sql);

	/* Execute SQL statement */
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
  if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Table created successfully\n");
  }
}


/**
 * @brief Function for Create insert  to create insert query .
 * @param windowsize Size of the Window.
 * @return char: Returns char pointer.
 */
char* create_insert(int windowsize)
{
  int i;
  char *start = "insert into PROCESS values (";
  char *mid1 = (char*)malloc(windowsize * 10);
  char *end1 = (char*)malloc(windowsize * 24);
  mid1 = "?";

  for(i=0; i<windowsize -1; i++)
  {
    asprintf(&mid1,"%s, ?",mid1);
  }
  asprintf(&end1,"%s %s )",start,mid1);

  return end1;

}


/**
 * @brief Function for Insert syscall  to insert the system calls.
 * @param syscall Name of system call.
 * @param insert String for insert statment
 * @param db Database pointer.
 * @return int: Returns int
 */
int insert_syscall(char **syscall, char *insert, sqlite3* db)
{
  sqlite3_stmt *stmt;

  /* preparing insert call */
 if (sqlite3_prepare(
    db, 
    insert,  // stmt
    -1, // If than zero, then stmt is read up to the first nul terminator
    &stmt,
    0  // Pointer to unused portion of stmt
    )
       != SQLITE_OK) 
  {
      printf("\nCould not prepare statement.");
      return 1;
  }

  printf("strings %s%s%s",syscall[0],syscall[1],syscall[2]);

  /*insert the buffert in query */
  if (sqlite3_bind_text (
    stmt,
    1,  // Index of wildcard
    syscall[0],
    -1,  // length of text
    SQLITE_STATIC
    )
      != SQLITE_OK) 
    {
     printf("\nCould not bind txt.\n");
     return 1;
    }

    if (sqlite3_bind_text (
    stmt,
    2,  // Index of wildcard
    syscall[1],
    -1,  // length of text
    SQLITE_STATIC
    )
    != SQLITE_OK) 
    {
      printf("\nCould not bind txt.\n");
      return 1;
    }

    if (sqlite3_bind_text (
    stmt,
    3,  // Index of wildcard
    syscall[2],
    -1,  // length of text
    SQLITE_STATIC
      )
      != SQLITE_OK) 
    {
      printf("\nCould not bind txt.\n");
      return 1;
    }

  /* finalizing the query */
    if (sqlite3_step(stmt) != SQLITE_DONE) 
    {
      printf("\nCould not step (execute) stmt.\n");
    }
    else
    {
      printf("\n statement executed");
    }
    return 0;
}