/**
 * @file analyze.c
 * @brief File containing analyze functionality for storing or verifying systemcalls.
 *
 * This file subscribe to the topic filter . Then it creates a buffer of syscalls received with the 
 * limit of window size. Here configuration is read and if the storage mode is set to false it reads from the 
 * database and check of the system calls received are present otherwise if the storage mode is true it
 * store the data in the database.
 * 
 * @author Naren Bakshi
 */ 
#define _GNU_SOURCE 
#include "analyze_bench.h"


int setPaho = 0;
int setVsomeIP = 0;
int setDDS = 0;
int setIce = 0;
int counter=0;

sqlite3* db;
struct handstruct  *analyzesubHandler;
double timethen;


/**
 * @brief Function for callback for subscription in analyze. The function checks if the syscalls are in database. If not it reports an anomaly
 * otherwise it store the syscalls in sqlite database.
 * @param context NUll pointer.
 * @param topicname Name of the topic.
 * @param topicLen Lenght of the topic.
 * @param message Contains the message reveived with the callback .
 * @return int.
 */
int msgarrvd(void *context, char *topicName, int topicLen, void* message)
{
  int i,full;
	char *prcname = NULL;
  char* payloadptr;
	char topicname[100];
	char prcs[2597152];
	char *word = "strace";
  char *anomalyname = NULL, *tempname = NULL;
  double a,b;
  counter++;
printf("counter %d\n", counter);
    bool status;
    //strcpy(payloadptr,message);
    payloadptr = message;
  
    
    printf("   message received analyze: %s\n ",payloadptr);
    printf("     topic: %s\n", topicName);
  if( payloadptr != NULL)
   {
     
     prcname = malloc(2597152);
			/** Formating syscall to get the name of the call */
			sscanf(payloadptr, "%[^(]", prcs);
			
	if(strstr(prcs, word) == NULL)
    {	
      
	  if(setPaho == 1 || setVsomeIP == 1 || setDDS == 1 || setIce == 1) 
      {
        
        strcpy(prcname,prcs);
        printf("CLIENT : RECEIVEDD TO BENCH1 %s\n", prcname);
        timethen = what_time_is_it();
        printf("timethen %.6lf and counter %d \n",timethen,counter);
      }
	  else
      {
        sscanf(prcs, "%s %s",topicname,prcname);
			  printf("CLIENT : RECEIVED TO BENCH1 %s\n", prcname);
        timethen = what_time_is_it();
        printf("timethen %.6lf and counter %d \n",timethen,counter);
			  
      }
      if(counter == 42 || counter == 126)
      {
        
        
        //a = (*timethen);
        //b = (*timenow);
        //printf("Selected Middleware time taken to receive %.6lf\n ", timethen - timenow);
      }
    }
  }
}


 
/**
 * @brief Main function of analyze file
 * @param argc Number of arguments.
 * @param argv Contain URL.
 * @return Should not return anything.
 */ 
int main(int argc, char *argv[])
{

	struct config reader;
  bool check_table;
	reader = configReader();
  
  //timethen = malloc(sizeof(double));
  if(strcmp(reader.middleware,"PAHO") == 0)
	{
		setPaho = 1;
	}
  if(strcmp(reader.middleware,"VSOMEIP") == 0)
	{
		setVsomeIP = 1;
	}
  if(strcmp(reader.middleware,"CYCDDS") == 0)
	{
		setDDS = 1;
	}
  if(strcmp(reader.middleware,"ICEORYX") == 0)
	{
		setIce = 1;
	}

  int rc;
	char topicname[100];
   
	printf("start\n");

  	analyzesubHandler = malloc(sizeof(Handlerstruct));
	analyzesubHandler = chooseSubscribeHandler(reader.middleware,argv[2],"Benchi",&msgarrvd,argv[1]);
  /* 
  * Condition to check if input argument is for Client call , \\
  * then store the syscalls in buffer 
  * */
	if ((argc >= 1))
	{
		
	  analyzesubHandler->framworkptr->subscribe(analyzesubHandler);
          
	}	 

  free(analyzesubHandler);
	/* 
   * closing database 
  */
  //sqlite3_close(db);
	return 0;
}