cmake_minimum_required(VERSION 3.5)

project(thesisBench)

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

include_directories(${VSOMEIP3_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
link_directories(/usr/lib)

add_library(probeBench_header INTERFACE)
target_sources(probeBench_header INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/probeBench.h"
)
target_include_directories(probeBench_header INTERFACE
          "${CMAKE_CURRENT_SOURCE_DIR}"
     )

include_directories(../factory)
include_directories(../utils)
include_directories(../middleware/zeroMq)
include_directories(../middleware/nanoMsg)
include_directories(../middleware/pahomqtt)
include_directories(../middleware/vsomeIP)
include_directories(../middleware/cyclone_dds)
include_directories(../middleware/iceoryx)

add_executable(probeBench_out ${CMAKE_CURRENT_SOURCE_DIR}/probeBench.c)

target_include_directories(probeBench_out
     PUBLIC ../factory
     PUBLIC ../utils
     PUBLIC ../middleware/zeroMq
     PUBLIC ../middleware/nanoMsg
     PUBLIC ../middleware/pahomqtt
     PUBLIC ../middleware/vsomeIP
     PUBLIC ../middleware/cyclone_dds
     PUBLIC ../middleware/iceoryx
     ${LIBXML2_INCLUDE_DIR}
)
link_directories(
     ../factory
     ../utils
     ../middleware/zeroMq
     ../middleware/nanoMsg
     ../middleware/pahomqtt
     ../middleware/vsomeIP
     ../middleware/cyclone_dds
     ../middleware/iceoryx
)

SET_TARGET_PROPERTIES(vsomeIP PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(probeBench_out factory utils zeroMq nanoMsg pahomqtt cyclone_dds iceoryx PROPERTIES LINKER_LANGUAGE C)

target_link_libraries(probeBench_out probeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
