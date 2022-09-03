#ifndef CYCDDS
#define CYCDDS
#include "dds/dds.h"
#include "Pubsub_gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../factory/handlerFactory.h"


/**
 * @brief Function to initialze nanomsg pub sub.
 * @param structframwork Sturcture of nanomsg fucntion pointers.
 * @return void: Returns nothing.
 */
struct framwork;
void dds_operation_initialize(struct framwork *frame);

#endif
