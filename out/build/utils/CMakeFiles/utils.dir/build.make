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
include utils/CMakeFiles/utils.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/utils.dir/flags.make

utils/CMakeFiles/utils.dir/configread.c.o: utils/CMakeFiles/utils.dir/flags.make
utils/CMakeFiles/utils.dir/configread.c.o: ../../utils/configread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object utils/CMakeFiles/utils.dir/configread.c.o"
	cd /home/job2/Thesis/out/build/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/utils.dir/configread.c.o   -c /home/job2/Thesis/utils/configread.c

utils/CMakeFiles/utils.dir/configread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/utils.dir/configread.c.i"
	cd /home/job2/Thesis/out/build/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/job2/Thesis/utils/configread.c > CMakeFiles/utils.dir/configread.c.i

utils/CMakeFiles/utils.dir/configread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/utils.dir/configread.c.s"
	cd /home/job2/Thesis/out/build/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/job2/Thesis/utils/configread.c -o CMakeFiles/utils.dir/configread.c.s

utils/CMakeFiles/utils.dir/database.c.o: utils/CMakeFiles/utils.dir/flags.make
utils/CMakeFiles/utils.dir/database.c.o: ../../utils/database.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object utils/CMakeFiles/utils.dir/database.c.o"
	cd /home/job2/Thesis/out/build/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/utils.dir/database.c.o   -c /home/job2/Thesis/utils/database.c

utils/CMakeFiles/utils.dir/database.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/utils.dir/database.c.i"
	cd /home/job2/Thesis/out/build/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/job2/Thesis/utils/database.c > CMakeFiles/utils.dir/database.c.i

utils/CMakeFiles/utils.dir/database.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/utils.dir/database.c.s"
	cd /home/job2/Thesis/out/build/utils && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/job2/Thesis/utils/database.c -o CMakeFiles/utils.dir/database.c.s

# Object files for target utils
utils_OBJECTS = \
"CMakeFiles/utils.dir/configread.c.o" \
"CMakeFiles/utils.dir/database.c.o"

# External object files for target utils
utils_EXTERNAL_OBJECTS =

utils/libutils.so: utils/CMakeFiles/utils.dir/configread.c.o
utils/libutils.so: utils/CMakeFiles/utils.dir/database.c.o
utils/libutils.so: utils/CMakeFiles/utils.dir/build.make
utils/libutils.so: utils/CMakeFiles/utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared library libutils.so"
	cd /home/job2/Thesis/out/build/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/utils.dir/build: utils/libutils.so

.PHONY : utils/CMakeFiles/utils.dir/build

utils/CMakeFiles/utils.dir/clean:
	cd /home/job2/Thesis/out/build/utils && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/utils.dir/clean

utils/CMakeFiles/utils.dir/depend:
	cd /home/job2/Thesis/out/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/job2/Thesis /home/job2/Thesis/utils /home/job2/Thesis/out/build /home/job2/Thesis/out/build/utils /home/job2/Thesis/out/build/utils/CMakeFiles/utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/utils.dir/depend

