#ifndef ICEO
#define ICEO
#include "iceoryx_binding_c/publisher.h"
#include "iceoryx_binding_c/runtime.h"

#include "topic_data.h"
#include "sleep_for.h"

#include "iceoryx_binding_c/subscriber.h"
#include "iceoryx_binding_c/types.h"


#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include "string.h"

#include "../../responses.h"
#include "../../analyze.h"
#include "../../factory/handlerFactory.h"
struct framwork;
void ice_operation_initialize(struct framwork *frame);
#endif