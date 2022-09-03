/**
 * @file responses.h
 * @brief Header file containing structure pointers of Handler for syscall_formatter module.
 *
 * This file is a header file for storing structure pointers of Handler . This
 * global pointers are used in for different protocols as a factory pattern.
 * 
 * @author Naren Bakshi
 * @date 18 Jul 2021
 */
#ifndef FORMATTER
#define FORMATTER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>

#include "utils/configread.h"
#include "factory/handlerFactory.h"

struct handstruct  *formatterpubHandler;

struct handstruct  *formattersubHandler;

#endif