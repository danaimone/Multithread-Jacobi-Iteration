# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/danaimone/CLionProjects/concurrent-jacobi-iteration

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/jacobi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jacobi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jacobi.dir/flags.make

CMakeFiles/jacobi.dir/src/barrier.c.o: CMakeFiles/jacobi.dir/flags.make
CMakeFiles/jacobi.dir/src/barrier.c.o: ../src/barrier.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/danaimone/CLionProjects/concurrent-jacobi-iteration/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/jacobi.dir/src/barrier.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jacobi.dir/src/barrier.c.o   -c /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/src/barrier.c

CMakeFiles/jacobi.dir/src/barrier.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jacobi.dir/src/barrier.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/src/barrier.c > CMakeFiles/jacobi.dir/src/barrier.c.i

CMakeFiles/jacobi.dir/src/barrier.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jacobi.dir/src/barrier.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/src/barrier.c -o CMakeFiles/jacobi.dir/src/barrier.c.s

CMakeFiles/jacobi.dir/src/main.c.o: CMakeFiles/jacobi.dir/flags.make
CMakeFiles/jacobi.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/danaimone/CLionProjects/concurrent-jacobi-iteration/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/jacobi.dir/src/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jacobi.dir/src/main.c.o   -c /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/src/main.c

CMakeFiles/jacobi.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jacobi.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/src/main.c > CMakeFiles/jacobi.dir/src/main.c.i

CMakeFiles/jacobi.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jacobi.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/src/main.c -o CMakeFiles/jacobi.dir/src/main.c.s

# Object files for target jacobi
jacobi_OBJECTS = \
"CMakeFiles/jacobi.dir/src/barrier.c.o" \
"CMakeFiles/jacobi.dir/src/main.c.o"

# External object files for target jacobi
jacobi_EXTERNAL_OBJECTS =

jacobi: CMakeFiles/jacobi.dir/src/barrier.c.o
jacobi: CMakeFiles/jacobi.dir/src/main.c.o
jacobi: CMakeFiles/jacobi.dir/build.make
jacobi: CMakeFiles/jacobi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/danaimone/CLionProjects/concurrent-jacobi-iteration/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable jacobi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jacobi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jacobi.dir/build: jacobi

.PHONY : CMakeFiles/jacobi.dir/build

CMakeFiles/jacobi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jacobi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jacobi.dir/clean

CMakeFiles/jacobi.dir/depend:
	cd /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/danaimone/CLionProjects/concurrent-jacobi-iteration /Users/danaimone/CLionProjects/concurrent-jacobi-iteration /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/cmake-build-debug /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/cmake-build-debug /Users/danaimone/CLionProjects/concurrent-jacobi-iteration/cmake-build-debug/CMakeFiles/jacobi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jacobi.dir/depend

