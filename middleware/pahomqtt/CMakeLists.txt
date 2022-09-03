add_library(pahomqtt SHARED 
    pahomq_pubsub.c 
    pahomq_pubsub.h
)
target_link_libraries(pahomqtt -lpaho-mqtt3a)