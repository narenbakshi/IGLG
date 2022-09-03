#include <gtest/gtest.h>

extern "C"{
    #include "../../nanoMsg/nano_pubsub.h"
    #include "../../factory/handlerFactory.h"
}
struct framwork *nanoframwork;
struct handstruct *testhandler;
struct handstruct *testhandler1;

int msgarrvd_test(void *context, char *topicName, int topicLen, void* message)
{
    return 1;
}


int msgarrvd_negtest(void *context, char *topicName, int topicLen, void* message)
{
    return 1;
}
TEST(choosePublishHandler, PositiveNos) { 

    char *client = "Server";
    char *url = "ipc:///tmp/pubsub.ipc";
    testhandler = (handstruct *)malloc(sizeof(Handlerstruct));
    nanoframwork = (framwork *)malloc(sizeof(framwork));

    testhandler = choosePublishHandler("NANO","ipc:///tmp/pubsub.ipc","Tracer","Server");
    ASSERT_STREQ(client, testhandler->clientname);
    ASSERT_STREQ(url, testhandler->url);
   
}

TEST(choosePublishHandler, NegativeNos) { 

    char *client = "Server1";
    char *url = "ipc:///tmp/pubsub.ipc1";
    testhandler = (handstruct *)malloc(sizeof(Handlerstruct));
    nanoframwork = (framwork *)malloc(sizeof(framwork));

    testhandler = choosePublishHandler("NANO","ipc:///tmp/pubsub.ipc","Tracer","Server");
    ASSERT_STRNE(client, testhandler->clientname);
    ASSERT_STRNE(url, testhandler->url);
   
}

TEST(chooseSubscribeHandler, PositiveNos) { 

    char *client = "Client";
    char *url = "ipc:///tmp/pubsub.ipc";
    testhandler = (handstruct *)malloc(sizeof(Handlerstruct));
    nanoframwork = (framwork *)malloc(sizeof(framwork));

    testhandler = chooseSubscribeHandler("NANO","ipc:///tmp/pubsub.ipc","Tracer",&msgarrvd_test,"Client");
    ASSERT_STREQ(client, testhandler->clientname);
    ASSERT_STREQ(url, testhandler->url);
    ASSERT_EQ((int (*)(void*, char*, int, char*))&msgarrvd_test,testhandler->msgarrvd);
   
}

TEST(chooseSubscribeHandler, NegativeNos) { 

    char *client = "Client1";
    char *url = "ipc:///tmp/pubsub.ipc1";
    testhandler = (handstruct *)malloc(sizeof(Handlerstruct));
    nanoframwork = (framwork *)malloc(sizeof(framwork));

    testhandler = chooseSubscribeHandler("NANO","ipc:///tmp/pubsub.ipc","Tracer",&msgarrvd_test,"Client");
    ASSERT_STRNE(client, testhandler->clientname);
    ASSERT_STRNE(url, testhandler->url);
    ASSERT_NE((int (*)(void*, char*, int, char*))&msgarrvd_negtest,testhandler->msgarrvd);
   
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}