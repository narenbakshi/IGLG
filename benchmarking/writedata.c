/**
 * @file probe.c
 * @brief File containing functionality to read systemcalls with stracer command.
 *
 * This file reads the system calls with straer command called with popen.I has a funcion to get the 
 * pid of the system call with the prcess name.
 * 
 * @author Naren Bakshi
 */ 

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h> 
#include <stdbool.h>
sqlite3* db;
int y = 0,ctr = 0;
size_t size = 22020096;
char **ptr;
int first_row = 1;
FILE *fp;

void append(char *s, char c) {
    size_t len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
}




int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {

  int i;
  
  int randnumber;
  
  
  int* nof_records = (int*) p_data;
  (*nof_records)++;

  if (first_row) {
    first_row = 0;
  }

 
  
  for(i=0; i < num_fields; i++) {
    if (p_fields[i]) {
        //ptr = realloc(ptr, 2 * sizeof(p_fields[i]));
        
        append(ptr[y], p_fields[i]);
        ctr++;
        printf("counter %d\n",ctr);
        if(ctr == 262144)
        {
            fprintf(fp, "%s -1\n", ptr[y]);
          //fputs(ptr[y], fp);
          printf("data sending %s with size %d\n", ptr[y], strlen(ptr[y]));
          ctr= 0;
          y = y+1;
          ptr[y] = (char*)malloc(sizeof(char)*size);
          
           if(y == 10)
            {
                return;
            }
          
        }
      //printf("%20s n", p_fields[i]);
    }
    else {
      //printf("%20s", "y ");
    }
  }

  printf("\n");
  return 0;
}

/**
 * @brief Function for Select statment.
 * @param stmt Pointerfor statment.
 * @param db Database pointer.
 * @return void: Returns void.
 */
void select_stmt(const char* stmt, sqlite3* db) {
  char *errmsg;
  int   ret;
  int   nrecs = 0;

  ret = sqlite3_exec(db, stmt, select_callback, &nrecs, &errmsg);
  if(y == 10)
  {
    return;
  }

  if(ret!=SQLITE_OK) {
    printf("Error in select statement %s [%s].\n", stmt, errmsg);
  }
  else {
    printf("\n   %d records returned.\n", nrecs);
  }
}


/**
 * @brief Main function of probe file
 * @param argc Number of arguments.
 * @param argv Contain URL.
 * @return Should not return anything.
 */ 
int main(int argc, char *argv[])
{
	sqlite3 *db;
	int rc,j;
  char path[2035];
  char second[1035];
  char command[20];
  char payloadptr[2035];
	char *sql;
  clock_t start, end;
  double cpu_time_used;
  size_t size = 1048576;
  ptr = (char**)malloc(sizeof(char*)*size);
  ptr[y] = (char*)malloc(sizeof(char)*size);
    
    fp = fopen ("data.txt", "w+");

	/* Create SQL statement */
   sql = "SELECT * from incidents";
   
	  
	/**  Open database with the name taken from configuration. */
  rc = sqlite3_open("sfpd-incidents.sqlite", &db);
  if( rc ) {
    fprintf(stderr, "Can't open   database: %s\n", sqlite3_errmsg(db));
    return(0);
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }
   
  select_stmt(sql,db);
  //while(1){
  //  syscallHandler->framworkptr->publish(syscallHandler,"naren");
  //  counter++;
  //}
 

  fclose(fp);
  free(ptr);
  

  return 0;
}