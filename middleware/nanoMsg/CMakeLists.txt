add_library(nanoMsg SHARED 
    nano_pubsub.c 
    nano_pubsub.h
)
target_link_libraries(nanoMsg -lnanomsg)