add_library(zeroMq SHARED 
    zeromq_pubsub.c 
    zeromq_pubsub.h
)
target_link_libraries(zeroMq -lczmq -lzmq)