add_library(vsomeIP SHARED 
vsomeip_pubsub.cpp 
vsomeip_pubsub.hpp
)
#add_subdirectory(cpp)
#\
SET_TARGET_PROPERTIES(vsomeIP PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(vsomeIP  ${Boost_LIBRARIES} ${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})