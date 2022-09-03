/**
 * @file zeromq_pubsub.c
 * @brief File containing zeromq functionality for publish and subscribe to systemcalls.
 *
 * This file contain functions of publish and subscribe through zeroMq.
 * 
 * @author Naren Bakshi
 */ 
#include "zeromq_pubsub.h"
zsock_t *socketpub, *socketsub;
char *msgclose;


/**
 * @brief Function to catch signal 'CTRL+C'. It closes all open sockets.
 * @param sig_num Function reqired signal number.
 * @return void.
 */
void sigintzeroHandler(int sig_num)
{
    zstr_free (&msgclose);
    zsock_destroy(&socketsub);
    zsock_destroy(&socketpub);
    printf("closing sockets ..\n");
    fflush(stdout);
    exit(0);
}

/**
 * @brief Function to bind publish for zeromq.
 * @param Handlerstruct Handle strucure with all required data.
 * @return void..
 */
void zmqpub_bind(Handlerstruct *me)
{
 zsock_t *socket = zsock_new_pub(me->url);
  assert(socket);

  me->sockZero = socket;
}



/**
 * @brief Function to publish data with zeromq.
 * @param Handlerstruct Handle strucure with all required data.
 * @param data Data value.
 * @return int: Returns 0 if sent.
 */
void zmqpublish(Handlerstruct *me, char* data) {
 
 socketpub = me->sockZero;
		signal(SIGINT, sigintzeroHandler);
 char destination[2597152];
 

	
  sprintf(destination,"%s %s",me->topic, data);
  int rc;
  printf("SERVER: PUBLISHING DATA %s\n", destination);
  rc =  zstr_send(me->sockZero, destination);

}


/**
 * @brief Function to bind subscribe for zeromq.
 * @param Handlerstruct Handle strucure with all required data.
 * @return zsock_t: Returns socket.
 */
void zmqsub_bind(Handlerstruct *me)
{
  zsock_t *socket = zsock_new_sub(me->url, me->topic);
  
 // socket = zsock_new_pair(url);
  assert(socket);
  printf("connection establiushed");

   me->sockZero = socket;

}



/**
 * @brief Function to subscribe data with zeromq.
 * @param Handlerstruct Handle strucure with all required data.
 * @return char: Returns reveived data.
 */
char* zmqsubscribe(Handlerstruct *me) {
  		
      char *msg;
      socketsub = me->sockZero;
      msgclose= msg;
		signal(SIGINT, sigintzeroHandler);

  
  for(;;){
     msg = zstr_recv(me->sockZero);
    //assert (msg);
    //zsys_info("CLIENT (%s):> %s", name, msg);
    //zsock_destroy(&socket);
    me->msgarrvd(0,me->topic,6,msg);
    msg = NULL;
  }

  return msg;
}


/**
 * @brief Function to initialize the framework structure. It initializes with all the zeromq function pointers.
 * @param structframwork Structure for framework.
 * @return void.
 */
void zeromq_operation_initialize(struct framwork *frame)
{
	frame->publish = &zmqpublish;
	frame->subscribe = &zmqsubscribe;
	frame->pub_bind =  &zmqpub_bind;
	frame->sub_bind = &zmqsub_bind;

        
}