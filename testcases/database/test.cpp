#include <gtest/gtest.h>

extern "C"{
    #include "../../utils/database.h"
}
 
TEST(create_insert, PositiveNos) { 

     char *start = "insert into PROCESS values ( ?, ? )";
     char *new1;
     new1 = create_insert(2);

    //EXPECT_TRUE(start == new1);
    ASSERT_STREQ(start, create_insert(2));

}
 
TEST(create_insert, NegativeNos) {
    char *start = "insert into PROCESS values ( ?, ? )";

    ASSERT_STRNE(start, create_insert(3));

}


TEST(check_table_exist, PositiveNos) {

    int rc;
    sqlite3* db;
    rc = sqlite3_open("Traces.sqlite", &db);
    create_table(3,db);
    bool found = true;
    

    ASSERT_EQ(found, check_table_exist("PROCESS",db));

}

TEST(check_table_exist, NegativeNos) {

    int rc,rc1; 
    sqlite3* db;
    bool found = true;
    char *zErrMsg = 0;
    char *start = "DROP TABLE IF EXISTS PROCESS";

    rc1 = sqlite3_open("Traces.sqlite", &db);
    rc = sqlite3_exec(db, start, 0, 0, &zErrMsg);
    ASSERT_NE(found, check_table_exist("PROCESS",db));

}


TEST(insert_syscall, PositiveNos) {

    int rc;
    sqlite3* db;
    char *insert = "insert into PROCESS values ( ?, ?, ? )";
    rc = sqlite3_open("Traces.sqlite", &db);
    create_table(3,db);
    int found = 0;
    char **buffer1;
    buffer1 = (char**)malloc(3 *30);
    buffer1[0] = "Test";
    buffer1[1] = "Case";
    buffer1[2] = "pass";
    

    ASSERT_EQ(found, insert_syscall(buffer1,insert, db));

}

TEST(insert_syscall, NegativeNos) {

    int rc;
    sqlite3* db;
    char *insert = "insert into PROCESS values ( ?, ?, ? )";
    //rc = sqlite3_open("Traces.sqlite", &db);
    create_table(3,db);
    int found = 0;
    char **buffer1;
    buffer1 = (char**)malloc(3 *30);
    buffer1[0] = "Test";
    buffer1[1] = "Case";
    buffer1[2] = "pass";
    

    ASSERT_NE(found, insert_syscall(buffer1,insert, db));

}
 

TEST(check_stmt , PositiveNos) {

    int rc;
    sqlite3* db;
    rc = sqlite3_open("Traces.sqlite", &db);
    int found = true;
    char **buffer1;
    buffer1 = (char**)malloc(3 *30);
    buffer1[0] = "Test";
    buffer1[1] = "Case";
    buffer1[2] = "pass";
    

    ASSERT_EQ(found, check_stmt("select * from PROCESS", db, buffer1));

}

TEST(check_stmt , NegativeNos) {

    int rc;
    sqlite3* db;
    rc = sqlite3_open("Traces.sqlite", &db);
    create_table(3,db);
    int found = true;
    char **buffer1;
    buffer1 = (char**)malloc(3 *30);
    buffer1[0] = "Test";
    buffer1[1] = "Case";
    buffer1[2] = "pass";
    

    ASSERT_NE(found, check_stmt("select * from PROCESS", db, buffer1));

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}