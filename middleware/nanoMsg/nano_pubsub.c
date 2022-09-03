/**
 * @file nano_pubsub.c
 * @brief File containing nanomsg functionality for publish and subscribe to systemcalls.
 *
 * This file contain functions of publish and subscribe through nanomsg.
 * 
 * @author Naren Bakshi
 */ 

#include "nano_pubsub.h"
int sockclose;

/**
 * @brief Function to catch signal 'CTRL+C'. It closes all open sockets.
 * @param sig_num Function reqired signal number.
 * @return void.
 */
void sigintnanoHandler(int sig_num)
{
    nn_close (sockclose);
	printf("closing sockets ..\n");
	exit(0);
}

/**
 * @brief Function to throw fatal error.
 * @param func Function that threw the error.
 * @return void.
 */
void fatal(const char *func)
{
    	fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
}

/**
 * @brief Function to bind publish for nanomessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @return int: Returns socket.
 */
void nnpub_bind(Handlerstruct *me)
{
	int sock;

	if ((sock = nn_socket(AF_SP, NN_PUB)) < 0)
	{
		fatal("nn_socket");
	}
	if (nn_bind(sock, me->url) < 0)
	{
		fatal("nn_bind");
	}
	me->sockNano = sock;
 
}



/**
 * @brief Function to publish data with nanomessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @param data Data value.
 * @return int: Returns 0 if sent.
 */
void nnpublish(Handlerstruct *me, char* data)
{
    char destination[2597152];
	sockclose = me->sockNano;
	signal(SIGINT, sigintnanoHandler);

    sprintf(destination,"%s %s",me->topic, data);
    int sz_d = strlen(destination);
	printf("SERVER: PUBLISHING DATA %s\n", destination);
	int bytes = nn_send(me->sockNano,destination , sz_d, 0);
	if (bytes < 2)
	{
		fatal("nn_send");
		exit(0);
		
	}

}

/**
 * @brief Function to bind subscribe for nanomessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @return int: Returns socket.
 */
void nnsub_bind(Handlerstruct *me)
{
	int sock;

	if ((sock = nn_socket(AF_SP, NN_SUB)) < 0)
	{
		fatal("nn_socket");
	}

	if (nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, me->topic, strlen(me->topic)) < 0)
	{
		fatal("nn_setsockopt");
	}
	if (nn_connect(sock, me->url) < 0)
	{
		fatal("nn_connet");
	} 

	me->sockNano = sock;
}

/**
 * @brief Function to subscribe data with nanomessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @return char: Returns reveived data.
 */
char* nnsubscribe(Handlerstruct *me)
{
		sockclose = me->sockNano;
		signal(SIGINT, sigintnanoHandler);

		char *buf = NULL;
		for(;;)
		{
			int bytes = nn_recv(me->sockNano, &buf, NN_MSG, 0);
			
			if (bytes < 0)
			{
				fatal("nn_recv");
				exit(0);
			}
			me->msgarrvd(0,me->topic,6,buf);
			buf = NULL;
			
		}
		
}

/**
 * @brief Function to initialize the framework structure. It initializes with all the nanomsg function pointers.
 * @param structframwork Structure for framework.
 * @return void.
 */
void nano_operation_initialize(struct framwork *frame)
{
	frame->publish = &nnpublish;
	frame->subscribe = &nnsubscribe;
	frame->pub_bind =  &nnpub_bind;
	frame->sub_bind = &nnsub_bind;

}



