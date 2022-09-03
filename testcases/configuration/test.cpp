#include <gtest/gtest.h>

extern "C"{
    #include "../../utils/configread.h"
}

 


TEST(create_insert, PositiveNos) { 

     struct config st;
     st.brokerip = ( xmlChar *)"localhost";
     st.pname = ( xmlChar *)"firefox";
     st.windowsize = ( xmlChar *)"3";
     st.dbhost = ( xmlChar *)"../Traces.sqlite";
     st.storagemode = ( xmlChar *)"0";
     st.logginglevel = ( xmlChar *)"WARNING";
     st.middleware = ( xmlChar *)"PAHO";

    struct config re;
    re = configReader();
    //EXPECT_TRUE(start == new1);
    ASSERT_STREQ((const char*)st.brokerip, (const char*)re.brokerip);
    ASSERT_STREQ((const char*)st.pname, (const char*)re.pname);
    ASSERT_STREQ((const char*)st.windowsize, (const char*)re.windowsize);
    ASSERT_STREQ((const char*)st.dbhost, (const char*)re.dbhost);
    ASSERT_STREQ((const char*)st.storagemode, (const char*)re.storagemode);
    ASSERT_STREQ((const char*)st.logginglevel, (const char*)re.logginglevel);
    ASSERT_STREQ((const char*)st.middleware, (const char*)re.middleware);

}

TEST(create_insert, NegativeNos) { 

     struct config st;
     st.brokerip = ( xmlChar *)"localhost1";
     st.pname = ( xmlChar *)"firefox1";
     st.windowsize = ( xmlChar *)"31";
     st.dbhost = ( xmlChar *)"../Traces.sqlite1";
     st.storagemode = ( xmlChar *)"01";
     st.logginglevel = ( xmlChar *)"WARNING1";
     st.middleware = ( xmlChar *)"PAHO1";

    struct config re;
    re = configReader();
    //EXPECT_TRUE(start == new1);
    ASSERT_STRNE((const char*)st.brokerip, (const char*)re.brokerip);
    ASSERT_STRNE((const char*)st.pname, (const char*)re.pname);
    ASSERT_STRNE((const char*)st.windowsize, (const char*)re.windowsize);
    ASSERT_STRNE((const char*)st.dbhost, (const char*)re.dbhost);
    ASSERT_STRNE((const char*)st.storagemode, (const char*)re.storagemode);
    ASSERT_STRNE((const char*)st.logginglevel, (const char*)re.logginglevel);
    ASSERT_STRNE((const char*)st.middleware, (const char*)re.middleware);

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}