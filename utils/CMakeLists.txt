add_library(utils SHARED 
    configread.c 
    configread.h 
    database.c 
    database.h
)
add_definitions( "-DCONFIGPATH=\"/home/job2/Thesis/config.xml\"" )
#add_definitions(-CONFIGPATH="/home/job2/Thesis/config.xml")

