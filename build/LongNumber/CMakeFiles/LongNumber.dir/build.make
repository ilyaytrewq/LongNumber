# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ilyaytrewq/code/LongNumber

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ilyaytrewq/code/LongNumber/build

# Include any dependencies generated for this target.
include LongNumber/CMakeFiles/LongNumber.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include LongNumber/CMakeFiles/LongNumber.dir/compiler_depend.make

# Include the progress variables for this target.
include LongNumber/CMakeFiles/LongNumber.dir/progress.make

# Include the compile flags for this target's objects.
include LongNumber/CMakeFiles/LongNumber.dir/flags.make

LongNumber/CMakeFiles/LongNumber.dir/LongNumber.cpp.o: LongNumber/CMakeFiles/LongNumber.dir/flags.make
LongNumber/CMakeFiles/LongNumber.dir/LongNumber.cpp.o: /home/ilyaytrewq/code/LongNumber/LongNumber/LongNumber.cpp
LongNumber/CMakeFiles/LongNumber.dir/LongNumber.cpp.o: LongNumber/CMakeFiles/LongNumber.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ilyaytrewq/code/LongNumber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object LongNumber/CMakeFiles/LongNumber.dir/LongNumber.cpp.o"
	cd /home/ilyaytrewq/code/LongNumber/build/LongNumber && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT LongNumber/CMakeFiles/LongNumber.dir/LongNumber.cpp.o -MF CMakeFiles/LongNumber.dir/LongNumber.cpp.o.d -o CMakeFiles/LongNumber.dir/LongNumber.cpp.o -c /home/ilyaytrewq/code/LongNumber/LongNumber/LongNumber.cpp

LongNumber/CMakeFiles/LongNumber.dir/LongNumber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/LongNumber.dir/LongNumber.cpp.i"
	cd /home/ilyaytrewq/code/LongNumber/build/LongNumber && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ilyaytrewq/code/LongNumber/LongNumber/LongNumber.cpp > CMakeFiles/LongNumber.dir/LongNumber.cpp.i

LongNumber/CMakeFiles/LongNumber.dir/LongNumber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/LongNumber.dir/LongNumber.cpp.s"
	cd /home/ilyaytrewq/code/LongNumber/build/LongNumber && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ilyaytrewq/code/LongNumber/LongNumber/LongNumber.cpp -o CMakeFiles/LongNumber.dir/LongNumber.cpp.s

# Object files for target LongNumber
LongNumber_OBJECTS = \
"CMakeFiles/LongNumber.dir/LongNumber.cpp.o"

# External object files for target LongNumber
LongNumber_EXTERNAL_OBJECTS =

LongNumber/libLongNumber.a: LongNumber/CMakeFiles/LongNumber.dir/LongNumber.cpp.o
LongNumber/libLongNumber.a: LongNumber/CMakeFiles/LongNumber.dir/build.make
LongNumber/libLongNumber.a: LongNumber/CMakeFiles/LongNumber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ilyaytrewq/code/LongNumber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libLongNumber.a"
	cd /home/ilyaytrewq/code/LongNumber/build/LongNumber && $(CMAKE_COMMAND) -P CMakeFiles/LongNumber.dir/cmake_clean_target.cmake
	cd /home/ilyaytrewq/code/LongNumber/build/LongNumber && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LongNumber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
LongNumber/CMakeFiles/LongNumber.dir/build: LongNumber/libLongNumber.a
.PHONY : LongNumber/CMakeFiles/LongNumber.dir/build

LongNumber/CMakeFiles/LongNumber.dir/clean:
	cd /home/ilyaytrewq/code/LongNumber/build/LongNumber && $(CMAKE_COMMAND) -P CMakeFiles/LongNumber.dir/cmake_clean.cmake
.PHONY : LongNumber/CMakeFiles/LongNumber.dir/clean

LongNumber/CMakeFiles/LongNumber.dir/depend:
	cd /home/ilyaytrewq/code/LongNumber/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilyaytrewq/code/LongNumber /home/ilyaytrewq/code/LongNumber/LongNumber /home/ilyaytrewq/code/LongNumber/build /home/ilyaytrewq/code/LongNumber/build/LongNumber /home/ilyaytrewq/code/LongNumber/build/LongNumber/CMakeFiles/LongNumber.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : LongNumber/CMakeFiles/LongNumber.dir/depend

