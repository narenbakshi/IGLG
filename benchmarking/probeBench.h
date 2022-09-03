#ifndef PROBEBENCH
#define PROBEBENCH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h> 
#include <stdbool.h>

#include <unistd.h>
#include "../utils/configread.h"
#include "../utils/database.h"
#include "../factory/handlerFactory.h"

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names);
struct handstruct *syscallHandler;
/*
double what_time_is_it()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}*/


#endif