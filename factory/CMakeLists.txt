add_library(factory SHARED 
    handlerFactory.c
    handlerFactory.h    
)

link_directories (middleware/zeroMq
middleware/nanoMsg
middleware/pahomqtt
middleware/vsomeIP
)