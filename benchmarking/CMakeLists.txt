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
set(AllINCLUDES PUBLIC ../factory
PUBLIC ../utils
PUBLIC ../middleware/zeroMq
PUBLIC ../middleware/nanoMsg
PUBLIC ../middleware/pahomqtt
PUBLIC ../middleware/vsomeIP
PUBLIC ../middleware/cyclone_dds
PUBLIC ../middleware/iceoryx)

include_directories(${VSOMEIP3_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
link_directories(/usr/lib)

add_library(probeBench_header INTERFACE)
target_sources(probeBench_header INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/probeBench.h"
)
target_include_directories(probeBench_header INTERFACE
          "${CMAKE_CURRENT_SOURCE_DIR}"
     )

add_library(analyzeBench_header INTERFACE)
target_sources(analyzeBench_header INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench.h"
)
target_include_directories(analyzeBench_header INTERFACE
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
add_executable(analyzeBench_out1 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench1.c)
add_executable(analyzeBench_out2 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench2.c)
add_executable(analyzeBench_out3 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench3.c)
add_executable(analyzeBench_out4 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench4.c)
add_executable(analyzeBench_out5 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench5.c)
add_executable(analyzeBench_out6 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench6.c)
add_executable(analyzeBench_out7 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench7.c)
add_executable(analyzeBench_out8 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench8.c)
add_executable(analyzeBench_out9 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench9.c)
add_executable(analyzeBench_out10 ${CMAKE_CURRENT_SOURCE_DIR}/analyze_bench10.c)

target_include_directories(probeBench_out
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out1
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out2
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out3
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out4
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out5
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out6
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out7
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out8
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out9
     ${AllINCLUDES}
     ${LIBXML2_INCLUDE_DIR}
)
target_include_directories(analyzeBench_out10
     ${AllINCLUDES}
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
SET_TARGET_PROPERTIES(probeBench_out analyzeBench_out1 factory utils zeroMq nanoMsg pahomqtt cyclone_dds iceoryx PROPERTIES LINKER_LANGUAGE C)

target_link_libraries(probeBench_out probeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out1 probeBench_header analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out2 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out3 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out4 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out5 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out6 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out7 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out8 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out9 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)
target_link_libraries(analyzeBench_out10 analyzeBench_header factory utils zeroMq nanoMsg pahomqtt vsomeIP cyclone_dds iceoryx ${LIBXML2_LIBRARY} sqlite3)