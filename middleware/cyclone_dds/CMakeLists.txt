

if (NOT TARGET CycloneDDS::ddsc)
# Find the CycloneDDS package. If it is not in a default location, try
# finding it relative to the example where it most likely resides.
find_package(CycloneDDS REQUIRED)
endif()
idlc_generate(TARGET Pubsub_gen_lib FILES "Pubsub_gen.idl")

add_library(cyclone_dds SHARED 
    dds_pubsub.c 
    dds_pubsub.h
)

# This is a convenience function, provided by the CycloneDDS package,
# that will supply a library target related the the given idl file.
# In short, it takes the idl file, generates the source files with
# the proper data types and compiles them into a library.
#idlc_generate(TARGET Pubsub_gen_lib FILES "Pubsub_gen.idl" WARNINGS no-implicit-extensibility)

target_link_libraries(cyclone_dds Pubsub_gen_lib CycloneDDS::ddsc)