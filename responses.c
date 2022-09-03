/**
 * @file responses.c
 * @brief File containing formator functionality for formating systemcalls.
 *
 * This file subscribe to the topic Tracer and recieive the system calls. Then it removes the other unnecessary data 
 * and just extracts the system call name.
 * 
 * @author Naren Bakshi
 */ 
#include "responses.h"

int setPaho = 0;

/**
 * @brief Function for callback for subscription in syscall_formattor. It publishes the filtered data to analyze. 
 * @param context NUll pointer.
 * @param topicname Name of the topic.
 * @param topicLen Lenght of the topic.
 * @param message Contains the message reveived with the callback .
 * @return int.
 */
int msgarrvd(void *context, char *topicName, int topicLen, void* message)
{

	char* payloadptr;
	char prcname[1000];
	char topicname[1000];
	char prcs[1000];
	char *word = "strace";
    printf("Message arrived responses\n");
    //printf("   message: %s" , message );
    payloadptr = message;


	if( payloadptr != NULL){
		/** Formating syscall to get the name of the call */
		sscanf(payloadptr, "%[^(]", prcs);
		sscanf(prcs, "%s %s",topicname,prcname);
				
		if(strstr(prcs, word) == NULL)
		{	
			if(setPaho == 1)
			{
				printf("CLIENT : RECEIVED PAHO %s\n", prcs);
				//formatterpubHandler->framworkptr->publish(formatterpubHandler,prcs);
			}
			else
			{
				printf("CLIENT : RECEIVED  %s\n", prcs);
				//formatterpubHandler->framworkptr->publish(formatterpubHandler,prcname);
			}
						
		}				
	}
}
 
/**
 * @brief Main function of responses
 * @param argc Number of arguments.
 * @param argv Contain URL.
 * @return Should not return anything.
 */ 

int main(int argc, char *argv[])
{
	struct config reader;
	reader = configReader();
	if(strcmp(reader.middleware,"PAHO") == 0)
	{
		printf("setting paho value\n");
		setPaho = 1;
	}


	printf("start\n");
	formattersubHandler = malloc(sizeof(Handlerstruct));
	formattersubHandler = chooseSubscribeHandler(reader.middleware,argv[2],"Tracer",&msgarrvd,argv[1]);

	//formatterpubHandler = malloc(sizeof(Handlerstruct));
	//formatterpubHandler = choosePublishHandler(reader.middleware,argv[4],"Newbar",argv[3]);
  	
	
	/*
	*  Condition to check if input argument is for Client call ,
	* then send the formated syscall with topic Filter 
	*/
	if ((argc >= 1))
	{	
		
		formattersubHandler->framworkptr->subscribe(formattersubHandler);
		
		
	}

	return 0;
}