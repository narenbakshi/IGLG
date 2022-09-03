/**
 * @file configread.h
 * @brief Header file containing structures and function calls for reading configurations.
 *
 * This file is a header file for reading configurations function. It reads the ile from configpath.
 * 
 * @author Naren Bakshi
 * @date 18 Nov 2020
 */ 
#ifndef CONFIGREAD
#define CONFIGREAD

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//#define CONFIGPATH  "../../config.xml"
//#define CONFIGPATH "/home/job2/thesis_backup/config.xml"

/**
 * @struct config
 * @brief Structure contains the  pointers for configparameters.
 * */
typedef struct config
{
    xmlChar *pidr;  /**< pidr is used to read the pid from the file. */
    xmlChar *pname; /**< pname is used to read the process name from the file. */
    xmlChar *windowsize; /**< windowsize is used to read the size of the window from the file. */
    xmlChar *storagemode; /**< storagemode is used to read the true or false mode from the file. */
    xmlChar *dbhost; /**< dbhost is used to read the database name from the file. */
    xmlChar *brokerip; /**< brokerip is used to read the ip address of the broker from the file. */
    xmlChar *logginglevel; /**< logginglevel is used to read the level of logging from the file. */
    xmlChar *moduleoption; /**< moduleoption is used to read the name of the module to run from the file */
    xmlChar *middleware; /**< middleware is used to read the name of the protocol from the file. */
    xmlChar *transer;
    xmlChar *benchmarkTime; 

}Config;

/**
 * @brief Function to read configurations.
 * @param void No parameter.
 * @return Config: Return the config structure.
 */
Config configReader(void);


#endif

