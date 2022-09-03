#pragma once
/**
 * @file handlerFactory.h
 * @brief Header file containing structures for Handler.
 *
 * This file is a header file for storing stuctures for handler. This
 * Handler contains details of different protocol with the structures of Handlerstruct and framwork .
 * 
 * @author Naren Bakshi
 * @date 18 Jul 2021
 */ 
// access functions
#ifdef __cplusplus
    #define EXPORT_C extern "C"
#else
    #define EXPORT_C
#endif

#ifndef HANDLER
#define HANDLER
#include <stdio.h>
#include <string.h>
#include "../middleware/nanoMsg/nano_pubsub.h"
#include "../middleware/zeroMq/zeromq_pubsub.h"
#include "../middleware/pahomqtt/pahomq_pubsub.h"
#include "/home/job2/Thesis/middleware/vsomeIP/vsomeip_pubsub.hpp"
#include "/home/job2/Thesis/middleware/cyclone_dds/dds_pubsub.h"
#include "/home/job2/Thesis/middleware/iceoryx/ice_pubsub.h"


#ifdef __cplusplus // only actually define the class if this is C++
class subVsomeIP;
class pubVsomeIP;
#endif
/**
 * @struct handstruct
 * @brief Structure contains the  values required for each protocol.
 * */
typedef struct handstruct{ 
    char *clientname; /**< clientname is used to store the name of the instance. */
    int sockNano; /**< sockNano is used to store the name of the socket for Nano. */
    zsock_t *sockZero; /**< sockZero is used to store the name of the socket for ZeroMQ. */
    MQTTAsync sockPaho; /**< sockZero is used to store the name of the socket for pahoMQTT. */
    dds_entity_t sock_dds;
    char *topic; /**< topic is used to store the name of the topic */
    char *url; /**< url is used to store the complete url */
    struct framwork *framworkptr; /**< framworkptr is used to store the structure for framworks containing the function pointers   */
    int (*msgarrvd)(void *context, char *topicName, int topicLen, char *message); /**< msgarrvd is a callback function pointer */
    char *data; /**< data is used to store the data for the current instance */
    iox_pub_t icepub; /**< icepub is used to store the name of the socket for Iceoryx publisher. */
    iox_sub_t icesub; /**< icesub is used to store the name of the socket for Iceoryx subscriber. */
    #ifdef __cplusplus
    pubVsomeIP* sockVsomeIPpub; /**< sockVsomeIPpub is used to store the name of the socket for VsomeIP publisher. */
    subVsomeIP* sockVsomeIPsub; /**< sockVsomeIPsub is used to store the name of the socket for VsomeIP subscriber. */
    #endif
}Handlerstruct;

/**
 * @struct framwork
 * @brief Structure contains the  values required for each protocols function pointer.
 * */
typedef struct framwork
{
    void (*publish)(struct handstruct *me, char *data); /**< publish function pointer for publishing data. */
    char* (*subscribe)(struct handstruct *me); /**< subscribe function pointer for subscribing data. */
    void (*sub_bind)(struct handstruct *me ); /**< subscribe bind function pointer for binding Topic. */
    void (*pub_bind)(struct handstruct *me);/**< publish bind function pointer for binding url. */    
}newframwork;

double what_time_is_it()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}



Handlerstruct* choosePublishHandler(char *option, char *url, char *topic, char *clientnm);
Handlerstruct* chooseSubscribeHandler(char *option, char *url, char *topic, int (*fun)(void *, char *, int , void* ), char *clientnm);
#endif