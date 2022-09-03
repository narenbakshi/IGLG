/**
 * @file pahomq_pubsub.h
 * @brief Header file containing structures and function calls for pahomqtt message.
 *
 * This file is a header file for storing stucture of function calls pointers. These
 * function pointers are initialized in a c file and then later can call the functions of pahomqtt.
 * 
 * @author Naren Bakshi
 * @date 16 Jul 2021
 */ 
#ifndef PAHOMQT
#define PAHOMQT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTAsync.h"
#include "../../responses.h"
#include "../../analyze.h"
#include "../../factory/handlerFactory.h"
#define QOS         2
#define TIMEOUT     10000L

/**
 * @brief Function to initialze pahomqtt pub sub.
 * @param structframwork Sturcture for pahomqtt fucntion pointers.
 * @return void: Returns nothing.
 */
struct framwork;
void pahomq_operation_initialize(struct framwork *frame);

#endif