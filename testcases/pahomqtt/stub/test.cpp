#include <gtest/gtest.h>
#include<unistd.h>

extern "C"{
    #include "../../../nanoMsg/nano_pubsub.h"
    #include "../../../factory/handlerFactory.h"
}

//struct handstruct *testhandlerpahopub;
struct handstruct *testhandlerpahosub;
char* subdata;
char* pubdataexpected;


int msgarrvd_test(void *context, char *topicName, int topicLen, void* message)
{
    
    subdata = (char*)message;
    pubdataexpected = "new Testing123";
    printf("received msg%s\n",message);
    
    if(strcmp(subdata, pubdataexpected) == 0)
    {
        printf("\nTestcase passed\n");
            
    }
    else
    {
        assert(strcmp(subdata, pubdataexpected) == 0);
        
    }
    
    exit(0);
    return 1;
}


int msgarrvd_negtest(void *context, char *topicName, int topicLen, void* message)
{
    return 1;
}

TEST(pahosubscribe, PositiveNos) { 

    char* pubdata;
    unsigned int microsecond = 1000000;
    pubdata = "Testing123";
    
    char *url = "tcp://localhost:1883";
    testhandlerpahosub = (handstruct *)malloc(sizeof(Handlerstruct));

    testhandlerpahosub = chooseSubscribeHandler("PAHO",url,"Tracer",&msgarrvd_test,"ExampleClientpub");
    
    testhandlerpahosub->framworkptr->subscribe(testhandlerpahosub);
    //usleep(2 * microsecond);
    
    
    
    
    
    
    ASSERT_STREQ (pubdata, subdata);
    exit(0);
   
}
/*
TEST(publishsubscribe, NegativeNos) { 

    unsigned int microsecond = 1000000;
    pubdata = "\0";
    
    char *url = "ipc:///tmp/pubsub.ipc";
    testhandlerpub = (handstruct *)malloc(sizeof(Handlerstruct));
    testhandlersub = (handstruct *)malloc(sizeof(Handlerstruct));

    testhandlerpub = choosePublishHandler("NANO",url,"\0","Server");
    testhandlersub = chooseSubscribeHandler("NANO",url,"\0",&msgarrvd_test,"Client");
    testhandlerpub->framworkptr->publish(testhandlerpub,pubdata);
    usleep(2 * microsecond);
    testhandlersub->framworkptr->subscribe(testhandlersub);
    ASSERT_STREQ(pubdata, subdata);
    exit(0);
   
}*/




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}