/**
 * @file nano_pubsub.h
 * @brief Header file containing structures and function calls for nano message.
 *
 * This file is a header file for storing stucture of function calls pointers. These
 * function pointers are initialized in a c file and then later can call the functions of nanomsg.
 * 
 * @author Naren Bakshi
 * @date 18 Nov 2020
 */ 
#ifndef NANO
#define NANO
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include <nanomsg/ws.h>
#include "../../factory/handlerFactory.h"

#include <nanomsg/pair.h>


#define SERVER "server"
#define CLIENT "client"


/**
 * @brief Structure contains the function pointers of nano message.
 * Apllied when the flag is set to nanomsg
 **/



/**
 * @brief Function to initialze nanomsg pub sub.
 * @param structframwork Sturcture of nanomsg fucntion pointers.
 * @return void: Returns nothing.
 */
struct framwork;
void nano_operation_initialize(struct framwork *frame);

#endif