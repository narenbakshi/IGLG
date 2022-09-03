/**
 * @file analyze.h
 * @brief Header file containing structure pointers of Handler for analyze module.
 *
 * This file is a header file for storing structure pointers of Handler . This
 * global pointers are used in for different protocols as a factory pattern.
 * 
 * @author Naren Bakshi
 * @date 18 Jul 2021
 */ 
#ifndef analyze
#define analyze

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "factory/handlerFactory.h"
#include "utils/configread.h"

#include <sqlite3.h> 
#include <stdbool.h>
#include "utils/configread.h"
#include "utils/database.h"
 


struct handstruct  *analyzepubHandler;
struct handstruct  *analyzesubHandler;

#endif