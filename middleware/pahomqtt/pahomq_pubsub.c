/**
 * @file pahomq_pubsub.c
 * @brief File containing paho mqtt functionality for publish and subscribe to systemcalls.
 *
 * This file contain functions of publish and subscribe through pahomqtt.
 * 
 * @author Naren Bakshi
 */ 
#include "pahomq_pubsub.h"

volatile MQTTAsync_token deliveredtoken;
int finished = 0;
int disc_finished = 0;
int subscribed = 0;
MQTTAsync socpub;
MQTTAsync socksub;
void sigintpahoHandler(int sig_num)
{
    MQTTAsync_destroy(&socpub);
    MQTTAsync_destroy(&socksub);
    printf("closing sockets ..\n");
	exit(0);
}


/**************************************************subscribe****************/

/**
 * @brief Function for connection lost , send a reconnection request.
 * @param context Pointer for next function.
 * @param cause Cause of the failure.
 * @return void: Returns nothing.
 */
void connlost(void *context, char *cause)
{
        Handlerstruct *me;
        me = context;
        MQTTAsync client = me->sockPaho;
        MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
        int rc;
        printf("\nConnection lost\n");
        printf("     cause: %s\n", cause);
        printf("Reconnecting\n");
        conn_opts.keepAliveInterval = 20;
        conn_opts.cleansession = 1;
        if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
        {
                printf("Failed to start connect, return code %d\n", rc);
                finished = 1;
        }
}

/**
 * @brief Function for Disconnect failed.
 * @param context Pointer for next function.
 * @param MQTTAsync_failureData Response for failure.
 * @return void: Returns nothing.
 */
void onDisconnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Disconnect failed\n");
	finished = 1;
}

/**
 * @brief Function for Successful Disconnection.
 * @param context Pointer for next function.
 * @param MQTTAsync_successData Response for success.
 * @return void: Returns nothing.
 */
void onDisconnect(void* context, MQTTAsync_successData* response)
{
        printf("Successful disconnection\n");
        disc_finished = 1;
}

/**
 * @brief Function for Send  Failure.
 * @param context Pointer for next function.
 * @param MQTTAsync_failureData Response for failure.
 * @return void: Returns nothing.
 */
void onSendFailure(void* context, MQTTAsync_failureData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;

	printf("Message send failed token %d error code %d\n", response->token, response->code);
	opts.onSuccess = onDisconnect;
	opts.onFailure = onDisconnectFailure;
	opts.context = client;
	if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start disconnect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Function for responce of send .
 * @param context Pointer for next function.
 * @param MQTTAsync_successData Response for success.
 * @return void: Returns nothing.
 */
void onSend(void* context, MQTTAsync_successData* response)
{
	// This gets called when a message is acknowledged successfully.
}

/**
 * @brief Function for responce of connection failure on publish .
 * @param context Pointer for next function.
 * @param MQTTAsync_successData Response for failure.
 * @return void: Returns nothing.
 */
void onConnectFailurePub(void* context, MQTTAsync_failureData* response)
{
	printf("Connect failed, rc %d\n", response ? response->code : 0);
	finished = 1;
}

/**
 * @brief Function for responce of sucessful connection on publish .
 * @param context Pointer for next function.
 * @param MQTTAsync_successData Response for failure.
 * @return void: Returns nothing.
 */
void onConnectPub(void* context, MQTTAsync_successData* response)
{
	printf("Successful connection\n");
}

/**
 * @brief Function for callback for subscription in paho. This function calls the callback for respective module callback.
 * @param context NUll pointer.
 * @param topicname Name of the topic.
 * @param topicLen Lenght of the topic.
 * @param message Contains the message reveived with the callback .
 * @return int.
 */
int msgarrvdpaho(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    int i;
    char* payloadptr;

    payloadptr = message->payload;
    printf("message%s\n",payloadptr);
    if(strcmp(topicName,"Tracer") == 0)
    {
        formattersubHandler->msgarrvd(context,topicName,topicLen,payloadptr);
    }
    else
    {
        analyzesubHandler->msgarrvd(context,topicName,topicLen,payloadptr);
    }
    putchar('\n');
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

/**
 * @brief Function for responce of subscribe .
 * @param context Pointer for next function.
 * @param MQTTAsync_successData Response for success.
 * @return void: Returns nothing.
 */
void onSubscribe(void* context, MQTTAsync_successData* response)
{
        printf("Subscribe succeeded\n");
        subscribed = 1;
}

/**
 * @brief Function for responce of failure on subscribe .
 * @param context Pointer for next function.
 * @param MQTTAsync_failureDatav Response for failure.
 * @return void: Returns nothing.
 */
void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
        printf("Subscribe failed, rc %d\n", response ? response->code : 0);
        finished = 1;
}

/**
 * @brief Function for responce of connection failure on subscribe .
 * @param context Pointer for next function.
 * @param MQTTAsync_failureDatav Response for failure.
 * @return void: Returns nothing.
 */
void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
        printf("Connect failed, rc %d\n", response ? response->code : 0);
        finished = 1;
}

/**
 * @brief Function for responce of connection on subscribe. This function is used to call subscribe with a topic.
 * @param context Pointer for next function.
 * @param MQTTAsync_successData Response for success.
 * @return void: Returns nothing.
 */
void onConnectsubscribe(void* context, MQTTAsync_successData* response)
{
        Handlerstruct *me;
        me = context;
        MQTTAsync client = me->sockPaho;
        MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
        MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
        int rc;
        //printf("Successful connection\n");
        //printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
        //   "Press Q<Enter> to quit\n\n", me->topic, me->clientname, QOS);
        opts.onSuccess = onSubscribe;
        opts.onFailure = onSubscribeFailure;
        opts.context = me;
        deliveredtoken = 0;
        if ((rc = MQTTAsync_subscribe(client, me->topic, QOS, &opts)) != MQTTASYNC_SUCCESS)
        {
                printf("Failed to start subscribe, return code %d\n", rc);
                exit(EXIT_FAILURE);
        }
}

/**
 * @brief Function to bind publish for pahomqtt.
 * @param Handlerstruct Handle strucure with all required data.
 * @return void: Returns nothing.
 */
void pmqpub_bind(Handlerstruct *me)
{
    MQTTAsync client;
	 MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    MQTTAsync_create(&client, me->url,  me->clientname, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	me->sockPaho = client;
    MQTTAsync_setCallbacks(me->sockPaho, NULL, connlost, NULL, NULL);
    //printf("publishing....\n");
    
    int rc;
        
    conn_opts.keepAliveInterval = 60;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = onConnectPub;
    conn_opts.onFailure = onConnectFailurePub;
    
    conn_opts.context = me;

    if ((rc = MQTTAsync_connect(me->sockPaho, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
            printf("Failed to start connect, return code %d\n", rc);
            exit(EXIT_FAILURE);
    }
	
}



/**
 * @brief Function to publish data with pahomqtt.
 * @param Handlerstruct Handle strucure with all required data.
 * @param data Data value.
 * @return void: Returns nothing.
 */
void pmqpublish(Handlerstruct *me, char* data)
{
        int rc;
   	MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
        MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

	pub_opts.onSuccess = onSend;
	pub_opts.onFailure = onSendFailure;
	pub_opts.context = me;

	
	pubmsg.payload = data;
	pubmsg.payloadlen = strlen(data);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
        printf("SERVER: PUBLISHING  with topic %s and DATA %s\n",me->topic, data);
	if ((rc = MQTTAsync_sendMessage(me->sockPaho, me->topic, &pubmsg, &pub_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start sendMessage, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
        socpub = me->sockPaho;
        signal(SIGINT, sigintpahoHandler);
}

/**
 * @brief Function to bind subscribe for pahomqtt.
 * @param Handlerstruct Handle strucure with all required data.
 * @return void: Returns nothing.
 */
void pmqsub_bind(Handlerstruct *me)
{
    MQTTAsync client;
         
 
    MQTTAsync_create(&client, me->url, me->clientname, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    
	me->sockPaho= client;
    
}

/**
 * @brief Function to subscribe data with pahomqtt.
 * @param Handlerstruct Handle strucure with all required data.
 * @return char: Returns reveived data.
 */
char* pmqsubscribe(Handlerstruct *me)
{

    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
    int rc,ch;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = onConnectsubscribe;
    conn_opts.onFailure = onConnectFailure;
    conn_opts.context = me;
    MQTTAsync_setCallbacks(me->sockPaho, NULL, connlost, msgarrvdpaho, NULL);
    if ((rc = MQTTAsync_connect(me->sockPaho, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
            printf("Failed to start connect, return code %d\n", rc);
            exit(EXIT_FAILURE);
    }
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n", me->topic, me->clientname, QOS);

    do
    {
            ch = getchar();
    } while (ch!='Q' && ch != 'q');
    disc_opts.onSuccess = onDisconnect;
    if ((rc = MQTTAsync_disconnect(me->sockPaho, &disc_opts)) != MQTTASYNC_SUCCESS)
    {
            printf("Failed to start disconnect, return code %d\n", rc);
            exit(EXIT_FAILURE);
    }
    socpub = me->sockPaho;
    signal(SIGINT, sigintpahoHandler);
    MQTTAsync_destroy(&(me->sockPaho));
}


/**
 * @brief Function to initialize the framework structure. It initializes with all the pahomqtt function pointers.
 * @param structframwork Structure for framework.
 * @return void.
 */
void pahomq_operation_initialize(struct framwork *frame)
{

	frame->publish = &pmqpublish;
	frame->subscribe = &pmqsubscribe;
	frame->pub_bind =  &pmqpub_bind;
	frame->sub_bind = &pmqsub_bind;

}



