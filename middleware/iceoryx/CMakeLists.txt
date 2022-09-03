include(GNUInstallDirs)

find_package(iceoryx_posh CONFIG REQUIRED)
find_package(iceoryx_binding_c CONFIG REQUIRED)
find_package(iceoryx_hoofs CONFIG REQUIRED)

get_target_property(ICEORYX_CXX_STANDARD iceoryx_posh::iceoryx_posh CXX_STANDARD)
include(IceoryxPlatform)

if("-Wno-noexcept-type" IN_LIST ICEORYX_WARNINGS)
    list(REMOVE_ITEM ICEORYX_WARNINGS "-Wno-noexcept-type")
endif()



add_library(iceoryx SHARED 
    ice_pubsub.c 
    ice_pubsub.h
)

# This is a convenience function, provided by the CycloneDDS package,
# that will supply a library target related the the given idl file.
# In short, it takes the idl file, generates the source files with
# the proper data types and compiles them into a library.
#idlc_generate(TARGET Pubsub_gen_lib FILES "Pubsub_gen.idl" WARNINGS no-implicit-extensibility)

target_compile_options(iceoryx PRIVATE ${ICEORYX_WARNINGS} ${ICEORYX_SANITIZER_FLAGS})
target_link_libraries(iceoryx  iceoryx_binding_c::iceoryx_binding_c)