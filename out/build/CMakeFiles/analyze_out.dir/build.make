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
include CMakeFiles/analyze_out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/analyze_out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/analyze_out.dir/flags.make

CMakeFiles/analyze_out.dir/analyze.c.o: CMakeFiles/analyze_out.dir/flags.make
CMakeFiles/analyze_out.dir/analyze.c.o: ../../analyze.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/analyze_out.dir/analyze.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/analyze_out.dir/analyze.c.o   -c /home/job2/Thesis/analyze.c

CMakeFiles/analyze_out.dir/analyze.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/analyze_out.dir/analyze.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/job2/Thesis/analyze.c > CMakeFiles/analyze_out.dir/analyze.c.i

CMakeFiles/analyze_out.dir/analyze.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/analyze_out.dir/analyze.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/job2/Thesis/analyze.c -o CMakeFiles/analyze_out.dir/analyze.c.s

CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.o: CMakeFiles/analyze_out.dir/flags.make
CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.o: middleware/cyclone_dds/Pubsub_gen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.o   -c /home/job2/Thesis/out/build/middleware/cyclone_dds/Pubsub_gen.c

CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/job2/Thesis/out/build/middleware/cyclone_dds/Pubsub_gen.c > CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.i

CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/job2/Thesis/out/build/middleware/cyclone_dds/Pubsub_gen.c -o CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.s

# Object files for target analyze_out
analyze_out_OBJECTS = \
"CMakeFiles/analyze_out.dir/analyze.c.o" \
"CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.o"

# External object files for target analyze_out
analyze_out_EXTERNAL_OBJECTS =

analyze_out: CMakeFiles/analyze_out.dir/analyze.c.o
analyze_out: CMakeFiles/analyze_out.dir/middleware/cyclone_dds/Pubsub_gen.c.o
analyze_out: CMakeFiles/analyze_out.dir/build.make
analyze_out: factory/libfactory.so
analyze_out: utils/libutils.so
analyze_out: middleware/zeroMq/libzeroMq.so
analyze_out: middleware/nanoMsg/libnanoMsg.so
analyze_out: middleware/pahomqtt/libpahomqtt.so
analyze_out: middleware/vsomeIP/libvsomeIP.so
analyze_out: middleware/cyclone_dds/libcyclone_dds.so
analyze_out: middleware/iceoryx/libiceoryx.so
analyze_out: /usr/lib/x86_64-linux-gnu/libxml2.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_log.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_system.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_log_setup.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_thread.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_regex.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
analyze_out: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
analyze_out: /usr/local/lib/libvsomeip3.so.3.1.20
analyze_out: /usr/local/lib/libddsc.so.0.9.0
analyze_out: /usr/local/lib/libiceoryx_binding_c.a
analyze_out: /usr/local/lib/libiceoryx_posh.a
analyze_out: /usr/local/lib/libiceoryx_hoofs.a
analyze_out: /usr/local/lib/libiceoryx_platform.a
analyze_out: CMakeFiles/analyze_out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/job2/Thesis/out/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable analyze_out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/analyze_out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/analyze_out.dir/build: analyze_out

.PHONY : CMakeFiles/analyze_out.dir/build

CMakeFiles/analyze_out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/analyze_out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/analyze_out.dir/clean

CMakeFiles/analyze_out.dir/depend:
	cd /home/job2/Thesis/out/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/job2/Thesis /home/job2/Thesis /home/job2/Thesis/out/build /home/job2/Thesis/out/build /home/job2/Thesis/out/build/CMakeFiles/analyze_out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/analyze_out.dir/depend
