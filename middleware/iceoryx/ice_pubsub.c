
#include "ice_pubsub.h"

bool killswitch = false;
static void sigHandler(int signalValue)
{
    // Ignore unused variable warning
    (void)signalValue;
    // caught SIGINT or SIGTERM, now exit gracefully
    killswitch = true;
}

/**
 * @brief Function to bind publish for nanomessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @return int: Returns socket.
 */
void icepub_bind(Handlerstruct *me)
{
    //! [create runtime instance]
     char* APP_NAME = me->clientname;
    iox_runtime_init(APP_NAME);
    //! [create runtime instance]

    //! [create publisher port]
    iox_pub_options_t options;
    iox_pub_options_init(&options);
    options.historyCapacity = 10U;
    options.nodeName = "iox-c-publisher-node";
    iox_pub_storage_t *publisherStorage;
    publisherStorage = (iox_pub_storage_t *)malloc(sizeof(iox_pub_storage_t));
    iox_pub_t publisher = iox_pub_init(publisherStorage, "Thesis", "Iceoryx", me->topic, &options);
    me->icepub = publisher;
    
}


/**
 * @brief Function to publish data with nanomessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @param data Data value.
 * @return int: Returns 0 if sent.
 */
void icepublish(Handlerstruct *me, char* data)
{
    iox_pub_t publisher = me->icepub;
    int ct = 12;
    const char APP_NAME[] = "iox-c-publisher";

    //while (!killswitch)
    {
        struct Userdata* userPayload = NULL;
        if (AllocationResult_SUCCESS == iox_pub_loan_chunk(publisher, &userPayload, sizeof(struct Userdata)))
        {

            struct Userdata* sample = (struct Userdata*)userPayload;

            //strcpy(sample->data,data);
            //sample->data = data;
            strcpy(sample->data,data);
            sample->value = ct;
 

            printf("%s sent value: %sf\n", APP_NAME, userPayload->data);
            fflush(stdout);

            iox_pub_publish_chunk(publisher, userPayload);

            ++ct;

            sleep_for(400);
        }
        else
        {
            printf("Failed to allocate chunk!");
        }
    }
     if(killswitch == true)
     {
         iox_pub_deinit(publisher);

     }
    
    //! [send and print number]

    //! [cleanup]
    

}




void icesub_bind(Handlerstruct *me)
{
//! [create runtime instance]
     char* APP_NAME = me->clientname;
    iox_runtime_init(APP_NAME);
    iox_sub_options_t options;
    iox_sub_options_init(&options);
    options.historyRequest = 10U;
    options.queueCapacity = 50U;
    options.nodeName = "iox-c-subscriber-node";
        
    iox_sub_storage_t *subscriberStorage;
    subscriberStorage = (iox_sub_storage_t *)malloc(sizeof(iox_sub_storage_t));
    iox_sub_t subscriber = iox_sub_init(subscriberStorage, "Thesis", "Iceoryx", me->topic, &options);
    me->icesub = subscriber;

}
char* icesubscribe(Handlerstruct *me)
{
    iox_sub_t subscriber = me->icesub;

    //! [create subscriber port]

    //! [receive and print data]
    while (!killswitch)
    {
        if (SubscribeState_SUBSCRIBED == iox_sub_get_subscription_state(subscriber))
        {
            const void* userPayload = NULL;
            char payload[2597152];
            // we will receive more than one sample here since the publisher is sending a
            // new sample every 400 ms and we check for new samples only every second
            while (ChunkReceiveResult_SUCCESS == iox_sub_take_chunk(subscriber, &userPayload))
            {
                struct Userdata* sample = (struct Userdata*)(userPayload);
                //payload = malloc(30);
                strcpy(payload,sample->data);
                //payload =sample->data;
                me->msgarrvd(0,me->topic,6,sample->data);
                printf("%s got value: %s and %d\n", me->clientname, sample->data, sample->value);
                //printf("=-----that it----\n");
                fflush(stdout);
                //payload = NULL;
                //free(payload);
                iox_sub_release_chunk(subscriber, userPayload);
            }
            printf("\n");
        }
        else
        {
            printf("Not subscribed!\n");
        }

        sleep_for(1000);
    }
    //! [receive and print data]

    //! [cleanup]
    if(killswitch == true)
    {
        iox_sub_deinit(subscriber);
    }
    
    //! [cleanup]
}

/**
 * @brief Function to initialize the framework structure. It initializes with all the pahomqtt function pointers.
 * @param structframwork Structure for framework.
 * @return void.
 */
void ice_operation_initialize(struct framwork *frame)
{

	frame->publish = &icepublish;
	frame->subscribe = &icesubscribe;
	frame->pub_bind =  &icepub_bind;
	frame->sub_bind = &icesub_bind;

}