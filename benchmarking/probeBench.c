/**
 * @file probe.c
 * @brief File containing functionality to read systemcalls with stracer command.
 *
 * This file reads the system calls with straer command called with popen.I has a funcion to get the 
 * pid of the system call with the prcess name.
 * 
 * @author Naren Bakshi
 */ 
#include "probeBench.h"
#include <time.h>

#define MAX_LINE_LENGTH 2097152

sqlite3* db;
struct config reader;
double timenow,timestart;
int y = 0,ctr = 0;
FILE *fptr;
int setDDS = 0;


int random1() 
{ 
    int num = rand() % 600; 
    return num; 
    
}


void sleep_for1(uint32_t milliseconds)
{
    usleep(milliseconds * 1000U);
}

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {

  int i;
  
  int randnumber;
  
  
  int* nof_records = (int*) p_data;
  (*nof_records)++;

  if (first_row) {
    first_row = 0;
  }
  if((strcmp(reader.transer,"Sporadic")  == 0))
  {
    sleep_for1(30);
  }
  
  
  
  for(i=0; i < num_fields; i++) {
    if (p_fields[i]) {
        timenow = what_time_is_it();
        if(setDDS ==1)
        {
            sleep_for1(20);
        }
        syscallHandler->framworkptr->publish(syscallHandler,p_fields[i]);
        printf("timenow %f\n",timenow);
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
  first_row = 1;

  ret = sqlite3_exec(db, stmt, select_callback, &nrecs, &errmsg);

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
  char *datafile;
  clock_t start, end;
  double cpu_time_used;
  
  datafile = malloc(sizeof(char) * 2597152);  

  syscallHandler = malloc(sizeof(Handlerstruct));

  reader = configReader();
  if(strcmp(reader.middleware,"CYCDDS") == 0)
  {
     setDDS = 1;
  }

  syscallHandler = choosePublishHandler(reader.middleware,argv[2],"Benchi",argv[1]);

  sleep_for1(200);
  start = clock();
  int counter = 1;
   
   if((strcmp(reader.transer,"Periodic")  == 0))
    {
      	/* Create SQL statement */
      sql = "SELECT * from PROCESS";
   
	  
	    /**  Open database with the name taken from configuration. */
      rc = sqlite3_open("Traces.sqlite", &db);
      if( rc ) {
        fprintf(stderr, "Can't open   database: %s\n", sqlite3_errmsg(db));
        return(0);
      } else {
        fprintf(stdout, "Opened database successfully\n");
      }
      timestart = what_time_is_it();
      select_stmt(sql,db);
    }
    else{
      fptr = fopen("/home/job2/Thesis/benchmarking/data.txt","r+");
      if(fptr == NULL)
        printf("unable to read file \n");
        timestart = what_time_is_it();
      while(fgets(datafile, MAX_LINE_LENGTH, fptr)){
        //printf("file data%s\n", datafile);
        syscallHandler->framworkptr->publish(syscallHandler,datafile);
    }

    }
  //while(1){
  //  syscallHandler->framworkptr->publish(syscallHandler,"naren");
  //  counter++;
  //}
  
  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  /**  get the Pid */

  printf("Selected Middleware Publisher frome took %f seconds to execute \n", cpu_time_used);
  printf("timestart %f\n",timestart );
  while (1)
  {
  
  }
  
 
  fclose(fptr);
  
  free(syscallHandler);
  // for(;;);
  return 0;
}