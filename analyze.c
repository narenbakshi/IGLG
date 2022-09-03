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
#include "analyze.h"


int setPaho = 0;
int setVsomeIP = 0;
int setDDS = 0;
int setIce = 0;
int counter= 0; 


sqlite3* db;

static int buffersize = 0;
int windowsizep,storage;
char **buffer;
char *insert = NULL;

/**
 * @brief Function for Buffer creation  with in the limits of window size.
 * @param parocname Syscall name.
 * @param buffer Storage buffer address.
 * @param windowsize The window size.
 * @return int: full = 1, means buffer is full otherwise full = 0.
 */
int create_buffer(char *procname,char **bbuffer, int windowsize)
{
  int i;
  printf("inside buffer\n");
  if(buffersize < windowsize)
  {
    for(i=windowsize-1; i>0; i--)
    {//printf("inside buffer for loop\n");
      bbuffer[i] = bbuffer[i-1];
    }
    //printf("ouside buffer for loop\n");
    bbuffer[0] = procname;
    //strcpy(bbuffer[0],procname);
    
    if(bbuffer[0] != NULL && bbuffer[1] != NULL && bbuffer[2] != NULL){
      printf("\nbuffers details %s %s %s with windowsize %d \n",bbuffer[0],bbuffer[1],bbuffer[2],windowsize);
    }
    
    buffersize++;
    if(buffersize == windowsize)
    {
      return 1;
    }
    return 0;
  }
  else
  {
    for(i=windowsize-1; i>0; i--)
    {
      bbuffer[i] = bbuffer[i-1];
    }
    bbuffer[0] = procname;
    printf("\nbuffers details %s %s %s with windowsize %d \n",bbuffer[0],bbuffer[1],bbuffer[2],windowsize); 
    return 1;   
  }
}


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
	char prcs[3000];
	char *word = "strace";
  char *anomalyname = NULL, *tempname = NULL;
  double timthen;

    bool status;
    //strcpy(payloadptr,message);
    payloadptr = (char*)message;
  
    
    printf(" message received analyze: %s\n ",payloadptr);
    timthen = what_time_is_it();
    counter++;
  
	 if( payloadptr != NULL)
   {
     prcname = malloc(100);
			/** Formating syscall to get the name of the call */
			sscanf(payloadptr, "%[^(]", prcs);
			
		if(strstr(prcs, word) == NULL)
    {	
			if(setPaho == 1 || setVsomeIP == 1 || setDDS == 1 || setIce == 1) 
      {
        
        strcpy(prcname,prcs);
        printf("CLIENT : RECEIVEDD %s\n", prcname);
        timthen = what_time_is_it();
        printf("timthen in analyze -----------------> %f and counter %d\n",timthen, counter);
      }
			else
      {
        sscanf(prcs, "%s %s",topicname,prcname);
			  printf("CLIENT : RECEIVED %s\n", prcname);
        timthen = what_time_is_it();
        printf("timthen  in analyze-----------------> %f and counter %d \n",timthen, counter);
			  
      }
		
      full =  create_buffer(prcname,buffer,windowsizep);
      prcname = NULL;
      free(prcname); 
      if(storage)
      {
          /**conditon to check if the buffer reached the window size * */
			  if(full == 1)
        {
          /** insert buffer in the database * */
          insert_syscall(buffer,insert, db);
        }
      }
      else
      {              
        if(full == 1)
        {
          
          status = check_stmt("select * from PROCESS", db, buffer);
           //printf("\nstatus is %s\n", status ? "true" : "false");   
          if(status == false)
          {
            anomalyname = malloc(30);
            for (i = 0; i<windowsizep ;i++)
            {
              if(i == 0)
              {
                
                  strcpy(anomalyname,buffer[i]);
              }
              else
              {
                tempname = malloc(30);
                strcpy(tempname,buffer[i]);
                asprintf(&anomalyname, "%s %s", anomalyname,tempname);
                free(tempname);
              } 
            }
            printf("\nsending anomaly %s with \n",anomalyname );
            analyzepubHandler->framworkptr->publish(analyzepubHandler,anomalyname);
            free(anomalyname);
          }
        }
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
	analyzesubHandler = chooseSubscribeHandler(reader.middleware,argv[2],"Filter",&msgarrvd,argv[1]);
	  		
	analyzepubHandler = malloc(sizeof(Handlerstruct));
	analyzepubHandler = choosePublishHandler(reader.middleware,argv[4],"Tracer",argv[3]);
  	


  storage = atoi(reader.storagemode);
  windowsizep = atoi(reader.windowsize);
  buffer = malloc(windowsizep *30);

  printf("checking value of storage mode %s\n",reader.storagemode);

   /**  Open database with the name taken from configuration. */
  rc = sqlite3_open(reader.dbhost, &db);
  if( rc ) {
    fprintf(stderr, "Can't open   database: %s\n", sqlite3_errmsg(db));
    return(0);
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }
  if(storage)
  {
    printf("creating table ....\n");
    /** create table based on windowsize  
     * database*/
    create_table(windowsizep,db);
    /** creating insert query for database */
    insert = create_insert(windowsizep);
  }
  else
  {
    check_table = check_table_exist("PROCESS",db);
    if(check_table == false)
    {
        printf("Table does not exists!!\n");
        exit(0);
    }

  }
  /* 
  * Condition to check if input argument is for Client call , \\
  * then store the syscalls in buffer 
  * */
	if ((argc >= 1))
	{
		
	  analyzesubHandler->framworkptr->subscribe(analyzesubHandler);
          
	}	 
	/* 
   * closing database 
  */
  //sqlite3_close(db);
	return 0;
}