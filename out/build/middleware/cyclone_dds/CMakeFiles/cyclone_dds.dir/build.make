# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/job2/.local/lib/python3.5/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/job2/.local/lib/python3.5/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/job2/Thesis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/job2/Thesis/out/build

# Include any dependencies generated for this target.
include middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/depend.make

# Include the progress variables for this target.
include middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/progress.make

# Include the compile flags for this target's objects.
include middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/flags.make

middleware/cyclone_dds/Pubsub_gen.c: ../../middleware/cyclone_dds/Pubsub_gen.idl
middleware/cyclone_dds/Pubsub_gen.c: /usr/local/bin/idlc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating Pubsub_gen.c, Pubsub_gen.h"
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && /usr/local/bin/idlc /home/job2/Thesis/middleware/cyclone_dds/Pubsub_gen.idl

middleware/cyclone_dds/Pubsub_gen.h: middleware/cyclone_dds/Pubsub_gen.c
	@$(CMAKE_COMMAND) -E touch_nocreate middleware/cyclone_dds/Pubsub_gen.h

middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/dds_pubsub.c.o: middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/flags.make
middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/dds_pubsub.c.o: ../../middleware/cyclone_dds/dds_pubsub.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/dds_pubsub.c.o"
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cyclone_dds.dir/dds_pubsub.c.o   -c /home/job2/Thesis/middleware/cyclone_dds/dds_pubsub.c

middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/dds_pubsub.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cyclone_dds.dir/dds_pubsub.c.i"
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/job2/Thesis/middleware/cyclone_dds/dds_pubsub.c > CMakeFiles/cyclone_dds.dir/dds_pubsub.c.i

middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/dds_pubsub.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cyclone_dds.dir/dds_pubsub.c.s"
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/job2/Thesis/middleware/cyclone_dds/dds_pubsub.c -o CMakeFiles/cyclone_dds.dir/dds_pubsub.c.s

middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.o: middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/flags.make
middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.o: middleware/cyclone_dds/Pubsub_gen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.o"
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.o   -c /home/job2/Thesis/out/build/middleware/cyclone_dds/Pubsub_gen.c

middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.i"
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/job2/Thesis/out/build/middleware/cyclone_dds/Pubsub_gen.c > CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.i

middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.s"
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/job2/Thesis/out/build/middleware/cyclone_dds/Pubsub_gen.c -o CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.s

# Object files for target cyclone_dds
cyclone_dds_OBJECTS = \
"CMakeFiles/cyclone_dds.dir/dds_pubsub.c.o" \
"CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.o"

# External object files for target cyclone_dds
cyclone_dds_EXTERNAL_OBJECTS =

middleware/cyclone_dds/libcyclone_dds.so: middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/dds_pubsub.c.o
middleware/cyclone_dds/libcyclone_dds.so: middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/Pubsub_gen.c.o
middleware/cyclone_dds/libcyclone_dds.so: middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/build.make
middleware/cyclone_dds/libcyclone_dds.so: /usr/local/lib/libddsc.so.0.9.0
middleware/cyclone_dds/libcyclone_dds.so: middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C shared library libcyclone_dds.so"
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cyclone_dds.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/build: middleware/cyclone_dds/libcyclone_dds.so

.PHONY : middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/build

middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/clean:
	cd /home/job2/Thesis/out/build/middleware/cyclone_dds && $(CMAKE_COMMAND) -P CMakeFiles/cyclone_dds.dir/cmake_clean.cmake
.PHONY : middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/clean

middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/depend: middleware/cyclone_dds/Pubsub_gen.c
middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/depend: middleware/cyclone_dds/Pubsub_gen.h
	cd /home/job2/Thesis/out/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/job2/Thesis /home/job2/Thesis/middleware/cyclone_dds /home/job2/Thesis/out/build /home/job2/Thesis/out/build/middleware/cyclone_dds /home/job2/Thesis/out/build/middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : middleware/cyclone_dds/CMakeFiles/cyclone_dds.dir/depend

