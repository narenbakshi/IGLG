cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(thesis)

set (PROJECT_NAME thesis)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lnanomsg -lxml2 -lsqlite3 -lczmq -lzmq -lpaho-mqtt3a -w")
# Find the CycloneDDS package.

find_package(Threads REQUIRED)
find_package(LibXml2 REQUIRED)
find_package (SQLite3)

find_package(iceoryx_posh CONFIG REQUIRED)
find_package(iceoryx_binding_c CONFIG REQUIRED)
find_package(iceoryx_hoofs CONFIG REQUIRED)


find_package(vsomeip3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS log system)
include_directories(/usr/include/libxml2)
include_directories(/usr/include)

set(ALLInc PUBLIC factory
PUBLIC utils
PUBLIC middleware/zeroMq
PUBLIC middleware/nanoMsg
PUBLIC middleware/pahomqtt
PUBLIC middleware/vsomeIP
PUBLIC middleware/cyclone_dds
PUBLIC middleware/iceoryx)

include_directories(${VSOMEIP3_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
link_directories(/usr/lib)


add_library(probe_head INTERFACE)
target_sources(probe_head INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/probe.h"
)
target_include_directories(probe_head INTERFACE
          "${CMAKE_CURRENT_SOURCE_DIR}"
     )
 
add_library(analyze_head INTERFACE)
target_sources(analyze_head INTERFACE
          "${CMAKE_CURRENT_SOURCE_DIR}/analyze.h"
     )
target_include_directories(analyze_head INTERFACE
          "${CMAKE_CURRENT_SOURCE_DIR}"
     )
 
add_library(responses_head INTERFACE)
target_sources(responses_head INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/responses.h"
)
target_include_directories(responses_head INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )


add_subdirectory(factory)
add_subdirectory(utils)
add_subdirectory(middleware/zeroMq)
add_subdirectory(middleware/nanoMsg)
add_subdirectory(middleware/pahomqtt)
add_subdirectory(middleware/vsomeIP)
add_subdirectory(middleware/cyclone_dds)
add_subdirectory(middleware/iceoryx)
add_subdirectory(benchmarking)



 
add_executable(probe_out ${CMAKE_CURRENT_SOURCE_DIR}/probe.c)
add_executable(analyze_out ${CMAKE_CURRENT_SOURCE_DIR}/analyze.c)
add_executable(responses_out ${CMAKE_CURRENT_SOURCE_DIR}/responses.c)
target_include_directories(probe_out
     ${ALLInc}
     ${LIBXML2_INCLUDE_DIR}
)

target_include_directories(analyze_out
     ${ALLInc}
     ${LIBXML2_INCLUDE_DIR}
)

target_include_directories(responses_out
     ${ALLInc}
     ${LIBXML2_INCLUDE_DIR}
)
link_directories(
     factory
     utils
     middleware/zeroMq
     middleware/nanoMsg
     middleware/pahomqtt
     middleware/vsomeIP
     middleware/cyclone_dds
     middleware/iceoryx
)



SET_TARGET_PROPERTIES(vsomeIP PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(probe_out analyze_out responses_out factory utils zeroMq nanoMsg pahomqtt cyclone_dds iceoryx PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(probe_out probe_head factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyze_out analyze_head factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(responses_out responses_head factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)