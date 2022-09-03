/**
 * @file zeromq_pubsub.h
 * @brief Header file containing structures and function calls for zeromq message.
 *
 * This file is a header file for storing stucture of function calls pointers. These
 * function pointers are initialized in a c file and then later can call the functions of zeromq.
 * 
 * @author Naren Bakshi
 * @date 18 Nov 2020
 */ 
#ifndef ZEROMQ
#define ZEROMQ
#include <czmq.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../factory/handlerFactory.h"



/**
 * @brief Function to initialze zeromq pub sub.
 * @param zerofrmwk Sturcture of zeromq fucntion pointers.
 * @return void: Returns nothing.
 */
struct framwork;
void zeromq_operation_initialize(struct framwork *frame);

#endif