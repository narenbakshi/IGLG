/**
 * @file probe.c
 * @brief File containing functionality to read systemcalls with stracer command.
 *
 * This file reads the system calls with straer command called with popen.I has a funcion to get the 
 * pid of the system call with the prcess name.
 * 
 * @author Naren Bakshi
 */ 
#include "probe.h"

struct config reader;
int counter = 0;

/**
 * @brief Function to get the pid with process name.
 * @param process_Name Name of the process.
 * @return pid_t: Returns the pid of the process.
 */
pid_t get_PID(xmlChar *process_Name)
{
  char buf[100];
  char command[20];

  /* Pidof command to get the pid of the process */
  sprintf(command, "pidof -s  %s",process_Name);
  /* Open the command for reading. */
  FILE *fp = popen(command, "r");

  fgets(buf, 100, fp);
  /*Covert string to unsinged long */
  pid_t pid = strtoul(buf, NULL, 10);

  pclose(fp);  
  return pid;
}

/**
 * @brief Main function of probe file
 * @param argc Number of arguments.
 * @param argv Contain URL.
 * @return Should not return anything.
 */ 
int main(int argc, char *argv[])
{

  char second[1035];
  FILE *fp;
  pid_t pid;
  char command[20];
  char path[2035];
  double timenow;
  
  char payloadptr[2035];
  int benchmarking_mode;
 
  
  syscallHandler = malloc(sizeof(Handlerstruct));
  //char process_Name[10] = "firefox";
  

  reader = configReader();
   
  syscallHandler = choosePublishHandler(reader.middleware,argv[2],"Filter",argv[1]);
    /**  get the Pid */
  if(reader.pname != NULL)
  {
    printf("\ninside if pname=%s\n", reader.pname);
    pid = get_PID(reader.pname); 
  }
  else
  {
    pid = atoi(reader.pidr);
  }
  printf("getting pid  ====%d \n",pid);  
  //pid = 8992;
  /**  Tracing command to get all system calls */
  sprintf(command, "perf trace -p  %d 2>&1",pid);

  /* Open the command for reading. */
  fp = popen(command, "r");
  if (fp == NULL)
  {
    printf("Failed to run command\n");
    exit(1);
  }

  /**  Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path), fp) != NULL)
  {
    /** Condition to check if input argument is for Server call , 
     * then send the syscalls with topic Tracer */
    if((argc >= 1))
    {
      counter++;
      timenow = what_time_is_it();
      printf("timenow ------------------->%f and counter %d\n",timenow, counter );
        //sscanf(payloadptr, "^[^\(]*", path);
      syscallHandler->framworkptr->publish(syscallHandler,path);

    
    }
      
  }
  /* close */
  pclose(fp);

  
  return 0;
}