# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lenfien/projects/Bug

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lenfien/projects/Bug/build

# Include any dependencies generated for this target.
include CMakeFiles/SimClient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SimClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SimClient.dir/flags.make

CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o: CMakeFiles/SimClient.dir/flags.make
CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o: ../UnitTest/SimClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o -c /home/lenfien/projects/Bug/UnitTest/SimClient.cpp

CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lenfien/projects/Bug/UnitTest/SimClient.cpp > CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.i

CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lenfien/projects/Bug/UnitTest/SimClient.cpp -o CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.s

CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o.requires:

.PHONY : CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o.requires

CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o.provides: CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o.requires
	$(MAKE) -f CMakeFiles/SimClient.dir/build.make CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o.provides.build
.PHONY : CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o.provides

CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o.provides.build: CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o


# Object files for target SimClient
SimClient_OBJECTS = \
"CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o"

# External object files for target SimClient
SimClient_EXTERNAL_OBJECTS =

SimClient: CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o
SimClient: CMakeFiles/SimClient.dir/build.make
SimClient: CMakeFiles/SimClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SimClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SimClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SimClient.dir/build: SimClient

.PHONY : CMakeFiles/SimClient.dir/build

CMakeFiles/SimClient.dir/requires: CMakeFiles/SimClient.dir/UnitTest/SimClient.cpp.o.requires

.PHONY : CMakeFiles/SimClient.dir/requires

CMakeFiles/SimClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SimClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SimClient.dir/clean

CMakeFiles/SimClient.dir/depend:
	cd /home/lenfien/projects/Bug/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lenfien/projects/Bug /home/lenfien/projects/Bug /home/lenfien/projects/Bug/build /home/lenfien/projects/Bug/build /home/lenfien/projects/Bug/build/CMakeFiles/SimClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SimClient.dir/depend
