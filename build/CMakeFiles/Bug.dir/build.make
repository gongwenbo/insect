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
include CMakeFiles/Bug.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Bug.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Bug.dir/flags.make

CMakeFiles/Bug.dir/Entry/Entry.cpp.o: CMakeFiles/Bug.dir/flags.make
CMakeFiles/Bug.dir/Entry/Entry.cpp.o: ../Entry/Entry.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Bug.dir/Entry/Entry.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bug.dir/Entry/Entry.cpp.o -c /home/lenfien/projects/Bug/Entry/Entry.cpp

CMakeFiles/Bug.dir/Entry/Entry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bug.dir/Entry/Entry.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lenfien/projects/Bug/Entry/Entry.cpp > CMakeFiles/Bug.dir/Entry/Entry.cpp.i

CMakeFiles/Bug.dir/Entry/Entry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bug.dir/Entry/Entry.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lenfien/projects/Bug/Entry/Entry.cpp -o CMakeFiles/Bug.dir/Entry/Entry.cpp.s

CMakeFiles/Bug.dir/Entry/Entry.cpp.o.requires:

.PHONY : CMakeFiles/Bug.dir/Entry/Entry.cpp.o.requires

CMakeFiles/Bug.dir/Entry/Entry.cpp.o.provides: CMakeFiles/Bug.dir/Entry/Entry.cpp.o.requires
	$(MAKE) -f CMakeFiles/Bug.dir/build.make CMakeFiles/Bug.dir/Entry/Entry.cpp.o.provides.build
.PHONY : CMakeFiles/Bug.dir/Entry/Entry.cpp.o.provides

CMakeFiles/Bug.dir/Entry/Entry.cpp.o.provides.build: CMakeFiles/Bug.dir/Entry/Entry.cpp.o


CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o: CMakeFiles/Bug.dir/flags.make
CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o: ../Runner/DoPoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o -c /home/lenfien/projects/Bug/Runner/DoPoll.cpp

CMakeFiles/Bug.dir/Runner/DoPoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bug.dir/Runner/DoPoll.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lenfien/projects/Bug/Runner/DoPoll.cpp > CMakeFiles/Bug.dir/Runner/DoPoll.cpp.i

CMakeFiles/Bug.dir/Runner/DoPoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bug.dir/Runner/DoPoll.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lenfien/projects/Bug/Runner/DoPoll.cpp -o CMakeFiles/Bug.dir/Runner/DoPoll.cpp.s

CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o.requires:

.PHONY : CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o.requires

CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o.provides: CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o.requires
	$(MAKE) -f CMakeFiles/Bug.dir/build.make CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o.provides.build
.PHONY : CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o.provides

CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o.provides.build: CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o


CMakeFiles/Bug.dir/Com/Syslog.cpp.o: CMakeFiles/Bug.dir/flags.make
CMakeFiles/Bug.dir/Com/Syslog.cpp.o: ../Com/Syslog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Bug.dir/Com/Syslog.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bug.dir/Com/Syslog.cpp.o -c /home/lenfien/projects/Bug/Com/Syslog.cpp

CMakeFiles/Bug.dir/Com/Syslog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bug.dir/Com/Syslog.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lenfien/projects/Bug/Com/Syslog.cpp > CMakeFiles/Bug.dir/Com/Syslog.cpp.i

CMakeFiles/Bug.dir/Com/Syslog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bug.dir/Com/Syslog.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lenfien/projects/Bug/Com/Syslog.cpp -o CMakeFiles/Bug.dir/Com/Syslog.cpp.s

CMakeFiles/Bug.dir/Com/Syslog.cpp.o.requires:

.PHONY : CMakeFiles/Bug.dir/Com/Syslog.cpp.o.requires

CMakeFiles/Bug.dir/Com/Syslog.cpp.o.provides: CMakeFiles/Bug.dir/Com/Syslog.cpp.o.requires
	$(MAKE) -f CMakeFiles/Bug.dir/build.make CMakeFiles/Bug.dir/Com/Syslog.cpp.o.provides.build
.PHONY : CMakeFiles/Bug.dir/Com/Syslog.cpp.o.provides

CMakeFiles/Bug.dir/Com/Syslog.cpp.o.provides.build: CMakeFiles/Bug.dir/Com/Syslog.cpp.o


CMakeFiles/Bug.dir/Database/Database.cpp.o: CMakeFiles/Bug.dir/flags.make
CMakeFiles/Bug.dir/Database/Database.cpp.o: ../Database/Database.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Bug.dir/Database/Database.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bug.dir/Database/Database.cpp.o -c /home/lenfien/projects/Bug/Database/Database.cpp

CMakeFiles/Bug.dir/Database/Database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bug.dir/Database/Database.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lenfien/projects/Bug/Database/Database.cpp > CMakeFiles/Bug.dir/Database/Database.cpp.i

CMakeFiles/Bug.dir/Database/Database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bug.dir/Database/Database.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lenfien/projects/Bug/Database/Database.cpp -o CMakeFiles/Bug.dir/Database/Database.cpp.s

CMakeFiles/Bug.dir/Database/Database.cpp.o.requires:

.PHONY : CMakeFiles/Bug.dir/Database/Database.cpp.o.requires

CMakeFiles/Bug.dir/Database/Database.cpp.o.provides: CMakeFiles/Bug.dir/Database/Database.cpp.o.requires
	$(MAKE) -f CMakeFiles/Bug.dir/build.make CMakeFiles/Bug.dir/Database/Database.cpp.o.provides.build
.PHONY : CMakeFiles/Bug.dir/Database/Database.cpp.o.provides

CMakeFiles/Bug.dir/Database/Database.cpp.o.provides.build: CMakeFiles/Bug.dir/Database/Database.cpp.o


CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o: CMakeFiles/Bug.dir/flags.make
CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o: ../Real/PackageProcessor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o -c /home/lenfien/projects/Bug/Real/PackageProcessor.cpp

CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lenfien/projects/Bug/Real/PackageProcessor.cpp > CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.i

CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lenfien/projects/Bug/Real/PackageProcessor.cpp -o CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.s

CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o.requires:

.PHONY : CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o.requires

CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o.provides: CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o.requires
	$(MAKE) -f CMakeFiles/Bug.dir/build.make CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o.provides.build
.PHONY : CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o.provides

CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o.provides.build: CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o


CMakeFiles/Bug.dir/Com/Conf.cpp.o: CMakeFiles/Bug.dir/flags.make
CMakeFiles/Bug.dir/Com/Conf.cpp.o: ../Com/Conf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Bug.dir/Com/Conf.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bug.dir/Com/Conf.cpp.o -c /home/lenfien/projects/Bug/Com/Conf.cpp

CMakeFiles/Bug.dir/Com/Conf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bug.dir/Com/Conf.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lenfien/projects/Bug/Com/Conf.cpp > CMakeFiles/Bug.dir/Com/Conf.cpp.i

CMakeFiles/Bug.dir/Com/Conf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bug.dir/Com/Conf.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lenfien/projects/Bug/Com/Conf.cpp -o CMakeFiles/Bug.dir/Com/Conf.cpp.s

CMakeFiles/Bug.dir/Com/Conf.cpp.o.requires:

.PHONY : CMakeFiles/Bug.dir/Com/Conf.cpp.o.requires

CMakeFiles/Bug.dir/Com/Conf.cpp.o.provides: CMakeFiles/Bug.dir/Com/Conf.cpp.o.requires
	$(MAKE) -f CMakeFiles/Bug.dir/build.make CMakeFiles/Bug.dir/Com/Conf.cpp.o.provides.build
.PHONY : CMakeFiles/Bug.dir/Com/Conf.cpp.o.provides

CMakeFiles/Bug.dir/Com/Conf.cpp.o.provides.build: CMakeFiles/Bug.dir/Com/Conf.cpp.o


CMakeFiles/Bug.dir/Phone/Reporter.cpp.o: CMakeFiles/Bug.dir/flags.make
CMakeFiles/Bug.dir/Phone/Reporter.cpp.o: ../Phone/Reporter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Bug.dir/Phone/Reporter.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Bug.dir/Phone/Reporter.cpp.o -c /home/lenfien/projects/Bug/Phone/Reporter.cpp

CMakeFiles/Bug.dir/Phone/Reporter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bug.dir/Phone/Reporter.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lenfien/projects/Bug/Phone/Reporter.cpp > CMakeFiles/Bug.dir/Phone/Reporter.cpp.i

CMakeFiles/Bug.dir/Phone/Reporter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bug.dir/Phone/Reporter.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lenfien/projects/Bug/Phone/Reporter.cpp -o CMakeFiles/Bug.dir/Phone/Reporter.cpp.s

CMakeFiles/Bug.dir/Phone/Reporter.cpp.o.requires:

.PHONY : CMakeFiles/Bug.dir/Phone/Reporter.cpp.o.requires

CMakeFiles/Bug.dir/Phone/Reporter.cpp.o.provides: CMakeFiles/Bug.dir/Phone/Reporter.cpp.o.requires
	$(MAKE) -f CMakeFiles/Bug.dir/build.make CMakeFiles/Bug.dir/Phone/Reporter.cpp.o.provides.build
.PHONY : CMakeFiles/Bug.dir/Phone/Reporter.cpp.o.provides

CMakeFiles/Bug.dir/Phone/Reporter.cpp.o.provides.build: CMakeFiles/Bug.dir/Phone/Reporter.cpp.o


# Object files for target Bug
Bug_OBJECTS = \
"CMakeFiles/Bug.dir/Entry/Entry.cpp.o" \
"CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o" \
"CMakeFiles/Bug.dir/Com/Syslog.cpp.o" \
"CMakeFiles/Bug.dir/Database/Database.cpp.o" \
"CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o" \
"CMakeFiles/Bug.dir/Com/Conf.cpp.o" \
"CMakeFiles/Bug.dir/Phone/Reporter.cpp.o"

# External object files for target Bug
Bug_EXTERNAL_OBJECTS =

Bug: CMakeFiles/Bug.dir/Entry/Entry.cpp.o
Bug: CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o
Bug: CMakeFiles/Bug.dir/Com/Syslog.cpp.o
Bug: CMakeFiles/Bug.dir/Database/Database.cpp.o
Bug: CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o
Bug: CMakeFiles/Bug.dir/Com/Conf.cpp.o
Bug: CMakeFiles/Bug.dir/Phone/Reporter.cpp.o
Bug: CMakeFiles/Bug.dir/build.make
Bug: CMakeFiles/Bug.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lenfien/projects/Bug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Bug"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Bug.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Bug.dir/build: Bug

.PHONY : CMakeFiles/Bug.dir/build

CMakeFiles/Bug.dir/requires: CMakeFiles/Bug.dir/Entry/Entry.cpp.o.requires
CMakeFiles/Bug.dir/requires: CMakeFiles/Bug.dir/Runner/DoPoll.cpp.o.requires
CMakeFiles/Bug.dir/requires: CMakeFiles/Bug.dir/Com/Syslog.cpp.o.requires
CMakeFiles/Bug.dir/requires: CMakeFiles/Bug.dir/Database/Database.cpp.o.requires
CMakeFiles/Bug.dir/requires: CMakeFiles/Bug.dir/Real/PackageProcessor.cpp.o.requires
CMakeFiles/Bug.dir/requires: CMakeFiles/Bug.dir/Com/Conf.cpp.o.requires
CMakeFiles/Bug.dir/requires: CMakeFiles/Bug.dir/Phone/Reporter.cpp.o.requires

.PHONY : CMakeFiles/Bug.dir/requires

CMakeFiles/Bug.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Bug.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Bug.dir/clean

CMakeFiles/Bug.dir/depend:
	cd /home/lenfien/projects/Bug/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lenfien/projects/Bug /home/lenfien/projects/Bug /home/lenfien/projects/Bug/build /home/lenfien/projects/Bug/build /home/lenfien/projects/Bug/build/CMakeFiles/Bug.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Bug.dir/depend

