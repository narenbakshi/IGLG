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
include middleware/pahomqtt/CMakeFiles/pahomqtt.dir/depend.make

# Include the progress variables for this target.
include middleware/pahomqtt/CMakeFiles/pahomqtt.dir/progress.make

# Include the compile flags for this target's objects.
include middleware/pahomqtt/CMakeFiles/pahomqtt.dir/flags.make

middleware/pahomqtt/CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.o: middleware/pahomqtt/CMakeFiles/pahomqtt.dir/flags.make
middleware/pahomqtt/CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.o: ../../middleware/pahomqtt/pahomq_pubsub.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object middleware/pahomqtt/CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.o"
	cd /home/job2/Thesis/out/build/middleware/pahomqtt && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.o   -c /home/job2/Thesis/middleware/pahomqtt/pahomq_pubsub.c

middleware/pahomqtt/CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.i"
	cd /home/job2/Thesis/out/build/middleware/pahomqtt && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/job2/Thesis/middleware/pahomqtt/pahomq_pubsub.c > CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.i

middleware/pahomqtt/CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.s"
	cd /home/job2/Thesis/out/build/middleware/pahomqtt && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/job2/Thesis/middleware/pahomqtt/pahomq_pubsub.c -o CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.s

# Object files for target pahomqtt
pahomqtt_OBJECTS = \
"CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.o"

# External object files for target pahomqtt
pahomqtt_EXTERNAL_OBJECTS =

middleware/pahomqtt/libpahomqtt.so: middleware/pahomqtt/CMakeFiles/pahomqtt.dir/pahomq_pubsub.c.o
middleware/pahomqtt/libpahomqtt.so: middleware/pahomqtt/CMakeFiles/pahomqtt.dir/build.make
middleware/pahomqtt/libpahomqtt.so: middleware/pahomqtt/CMakeFiles/pahomqtt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libpahomqtt.so"
	cd /home/job2/Thesis/out/build/middleware/pahomqtt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pahomqtt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
middleware/pahomqtt/CMakeFiles/pahomqtt.dir/build: middleware/pahomqtt/libpahomqtt.so

.PHONY : middleware/pahomqtt/CMakeFiles/pahomqtt.dir/build

middleware/pahomqtt/CMakeFiles/pahomqtt.dir/clean:
	cd /home/job2/Thesis/out/build/middleware/pahomqtt && $(CMAKE_COMMAND) -P CMakeFiles/pahomqtt.dir/cmake_clean.cmake
.PHONY : middleware/pahomqtt/CMakeFiles/pahomqtt.dir/clean

middleware/pahomqtt/CMakeFiles/pahomqtt.dir/depend:
	cd /home/job2/Thesis/out/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/job2/Thesis /home/job2/Thesis/middleware/pahomqtt /home/job2/Thesis/out/build /home/job2/Thesis/out/build/middleware/pahomqtt /home/job2/Thesis/out/build/middleware/pahomqtt/CMakeFiles/pahomqtt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : middleware/pahomqtt/CMakeFiles/pahomqtt.dir/depend

