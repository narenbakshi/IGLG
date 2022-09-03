/**
 * @file handlerFactory.c
 * @brief File containing functionality for choosing publish and subscribe handler with initializing framework structure.
 *
 * This file contain functions of initializing publish and subscribe handler.
 * 
 * @author Naren Bakshi
 */ 

#include "handlerFactory.h"


/**
 * @brief Function is used to choose between different protocols.
 *  This function initialzes all the parameters required for publishing data .
 * @param option Name of the protocol from configuration.
 * @param url Complete url string.
 * @param topic Name of the topic.
 * @param clientnm Name of the client .
 * @return Handlerstruct: contains all protocol required data.
 */
Handlerstruct* choosePublishHandler(char *option, char *url, char *topic, char *clientnm)
{

   Handlerstruct *newHandler;
   newHandler = malloc(sizeof(Handlerstruct));
    if (strcmp(option,"NANO") == 0)
    {
    	  struct framwork *nanoframwork;
    	  nanoframwork = malloc(sizeof(newframwork));
    	  /* Initializing all nanomsg functions */
    	  nano_operation_initialize(nanoframwork);
    	  /**  Binding socket with the url for publishing*/ 
			  printf("inside publish nano\n");

        newHandler->framworkptr = nanoframwork;
        newHandler->topic = topic;
        newHandler->url = url;
        newHandler->clientname = clientnm;
        newHandler->framworkptr->pub_bind(newHandler);
        
        		        
    }
    else if (strcmp(option,"ZEROMQ") == 0)
    {
      struct framwork *zmqframwork;
      zmqframwork = malloc(sizeof(newframwork));
      /* Initializing all zeromq functions */
      zeromq_operation_initialize(zmqframwork);
      /* Binding socket with the url for publishing*/ 
      printf("inside publish zero\n");

        newHandler->framworkptr = zmqframwork;
        newHandler->topic = topic;
        newHandler->url = url;
        newHandler->clientname = clientnm;
        newHandler->framworkptr->pub_bind(newHandler);
        
    }
    else if (strcmp(option,"PAHO") == 0)
    {
      struct framwork *pmqframework;
      pmqframework = malloc(sizeof(newframwork));

      pahomq_operation_initialize(pmqframework);

      printf("inside publish pahomq\n");
      newHandler->framworkptr = pmqframework;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->clientname = clientnm;
      
      newHandler->framworkptr->pub_bind(newHandler);
      
    
    } 
    else if (strcmp(option,"VSOMEIP") == 0)
    {
      struct framwork *vsmipframework;
      vsmipframework = malloc(sizeof(newframwork));

      vsmip_operation_initialize(vsmipframework);

      printf("inside publish vsomeip\n");
      newHandler->framworkptr = vsmipframework;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->clientname = clientnm;
      
      newHandler->framworkptr->pub_bind(newHandler);
    }
    else if (strcmp(option,"CYCDDS") == 0)
    {
      struct framwork *cycddsframework;
      cycddsframework = malloc(sizeof(newframwork));

      dds_operation_initialize(cycddsframework);

      printf("inside publish dds\n");
      newHandler->framworkptr = cycddsframework;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->clientname = clientnm;
      
      newHandler->framworkptr->pub_bind(newHandler);
    }
    else 
    {
      struct framwork *iceframework;
      iceframework = malloc(sizeof(newframwork));

      ice_operation_initialize(iceframework);

      printf("inside publish iceoryxs\n");
      newHandler->framworkptr = iceframework;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->clientname = clientnm;
      
      newHandler->framworkptr->pub_bind(newHandler);
    }
    return newHandler;

}

/**
 * @brief Function is used to choose between different protocols.
 *  This function initialzes all the parameters required for Subscribing data .
 * @param option Name of the protocol from configuration.
 * @param url Complete url string.
 * @param topic Name of the topic.
 * @param fun Function pointer for callback.
 * @param clientnm Name of the client.
 * @return Handlerstruct: contains all protocol required data.
 */
Handlerstruct* chooseSubscribeHandler(char *option, char *url, char *topic, int (*fun)(void *, char *, int , void*), char *clientnm)
{
    Handlerstruct *newHandler;
    newHandler = malloc(sizeof(Handlerstruct));
    if (strcmp(option,"NANO") == 0)
    {
    	struct framwork *nanoframwork;
    	nanoframwork = malloc(sizeof(newframwork));

    	/* Initializing all nanomsg functions */
    	nano_operation_initialize(nanoframwork);

			
			printf("inside sub handle nano   \n");
			newHandler->framworkptr = nanoframwork;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->msgarrvd = (int(*) (void *, char *, int , char *))fun;
      newHandler->clientname = clientnm;
      newHandler->framworkptr->sub_bind(newHandler);
      
			
    }
    else if (strcmp(option,"ZEROMQ") == 0)
    {
      struct framwork *zmqframwork;
      zmqframwork = malloc(sizeof(newframwork));
      /* Initializing all zeromq functions */
      zeromq_operation_initialize(zmqframwork);
      /* Binding socket with the url for publishing*/ 

      printf("inside sub handle zero\n");
			newHandler->framworkptr = zmqframwork;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->msgarrvd = (int(*) (void *, char *, int , char *))fun;
      newHandler->clientname = clientnm;
      newHandler->framworkptr->sub_bind(newHandler);
      

    }
    else if (strcmp(option,"PAHO") == 0)
    {
      struct framwork *pmqframework;
      pmqframework = malloc(sizeof(newframwork));

      pahomq_operation_initialize(pmqframework);

      printf("inside sub handle pahomq\n");
			newHandler->framworkptr = pmqframework;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->msgarrvd = (int(*) (void *, char *, int , char *))fun;
      newHandler->clientname = clientnm;
      newHandler->framworkptr->sub_bind(newHandler);
      

    } 
    else if (strcmp(option,"VSOMEIP") == 0)
    {
      struct framwork *vsmipframework;
      vsmipframework = malloc(sizeof(newframwork));

      vsmip_operation_initialize(vsmipframework);

      printf("inside sub handle vsomeip\n");
      newHandler->framworkptr = vsmipframework;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->clientname = clientnm;
      newHandler->msgarrvd = (int(*) (void *, char *, int , char *))fun;
      newHandler->framworkptr->sub_bind(newHandler);
    }
    else if (strcmp(option,"CYCDDS") == 0)
    {
      struct framwork *cycddsframework;
      cycddsframework = malloc(sizeof(newframwork));

      dds_operation_initialize(cycddsframework);

      printf("inside sub handle dds\n");
      newHandler->framworkptr = cycddsframework;
      newHandler->topic = topic;
      newHandler->url = url;
      newHandler->clientname = clientnm;
      newHandler->msgarrvd = (int(*) (void *, char *, int , char *))fun;
      newHandler->framworkptr->sub_bind(newHandler);
    }
    else 
    {
      struct framwork *iceframework;
      iceframework = malloc(sizeof(newframwork));

      ice_operation_initialize(iceframework);

      printf("inside sub handle iceoryx\n");
      newHandler->framworkptr = iceframework;
      newHandler->topic = topic;
      newHandler->url = url;
      if(clientnm == NULL)
      {
        clientnm = "analysis";

      }
      newHandler->clientname = clientnm;
      newHandler->msgarrvd = (int(*) (void *, char *, int , char *))fun;
      newHandler->framworkptr->sub_bind(newHandler);
    }
    return newHandler;

}