# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/ubuntu/lsc/dsf-lsc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/lsc/dsf-lsc/build

# Include any dependencies generated for this target.
include src/CMakeFiles/view.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/view.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/view.dir/flags.make

src/CMakeFiles/view.dir/view/view.cc.o: src/CMakeFiles/view.dir/flags.make
src/CMakeFiles/view.dir/view/view.cc.o: ../src/view/view.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/lsc/dsf-lsc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/view.dir/view/view.cc.o"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/view.dir/view/view.cc.o -c /home/ubuntu/lsc/dsf-lsc/src/view/view.cc

src/CMakeFiles/view.dir/view/view.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/view.dir/view/view.cc.i"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/lsc/dsf-lsc/src/view/view.cc > CMakeFiles/view.dir/view/view.cc.i

src/CMakeFiles/view.dir/view/view.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/view.dir/view/view.cc.s"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/lsc/dsf-lsc/src/view/view.cc -o CMakeFiles/view.dir/view/view.cc.s

src/CMakeFiles/view.dir/logger/timeStamp.cc.o: src/CMakeFiles/view.dir/flags.make
src/CMakeFiles/view.dir/logger/timeStamp.cc.o: ../src/logger/timeStamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/lsc/dsf-lsc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/view.dir/logger/timeStamp.cc.o"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/view.dir/logger/timeStamp.cc.o -c /home/ubuntu/lsc/dsf-lsc/src/logger/timeStamp.cc

src/CMakeFiles/view.dir/logger/timeStamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/view.dir/logger/timeStamp.cc.i"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/lsc/dsf-lsc/src/logger/timeStamp.cc > CMakeFiles/view.dir/logger/timeStamp.cc.i

src/CMakeFiles/view.dir/logger/timeStamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/view.dir/logger/timeStamp.cc.s"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/lsc/dsf-lsc/src/logger/timeStamp.cc -o CMakeFiles/view.dir/logger/timeStamp.cc.s

src/CMakeFiles/view.dir/logger/message.cc.o: src/CMakeFiles/view.dir/flags.make
src/CMakeFiles/view.dir/logger/message.cc.o: ../src/logger/message.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/lsc/dsf-lsc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/view.dir/logger/message.cc.o"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/view.dir/logger/message.cc.o -c /home/ubuntu/lsc/dsf-lsc/src/logger/message.cc

src/CMakeFiles/view.dir/logger/message.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/view.dir/logger/message.cc.i"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/lsc/dsf-lsc/src/logger/message.cc > CMakeFiles/view.dir/logger/message.cc.i

src/CMakeFiles/view.dir/logger/message.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/view.dir/logger/message.cc.s"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/lsc/dsf-lsc/src/logger/message.cc -o CMakeFiles/view.dir/logger/message.cc.s

src/CMakeFiles/view.dir/logger/logger.cc.o: src/CMakeFiles/view.dir/flags.make
src/CMakeFiles/view.dir/logger/logger.cc.o: ../src/logger/logger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/lsc/dsf-lsc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/view.dir/logger/logger.cc.o"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/view.dir/logger/logger.cc.o -c /home/ubuntu/lsc/dsf-lsc/src/logger/logger.cc

src/CMakeFiles/view.dir/logger/logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/view.dir/logger/logger.cc.i"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/lsc/dsf-lsc/src/logger/logger.cc > CMakeFiles/view.dir/logger/logger.cc.i

src/CMakeFiles/view.dir/logger/logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/view.dir/logger/logger.cc.s"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/lsc/dsf-lsc/src/logger/logger.cc -o CMakeFiles/view.dir/logger/logger.cc.s

# Object files for target view
view_OBJECTS = \
"CMakeFiles/view.dir/view/view.cc.o" \
"CMakeFiles/view.dir/logger/timeStamp.cc.o" \
"CMakeFiles/view.dir/logger/message.cc.o" \
"CMakeFiles/view.dir/logger/logger.cc.o"

# External object files for target view
view_EXTERNAL_OBJECTS =

../bin/view: src/CMakeFiles/view.dir/view/view.cc.o
../bin/view: src/CMakeFiles/view.dir/logger/timeStamp.cc.o
../bin/view: src/CMakeFiles/view.dir/logger/message.cc.o
../bin/view: src/CMakeFiles/view.dir/logger/logger.cc.o
../bin/view: src/CMakeFiles/view.dir/build.make
../bin/view: src/CMakeFiles/view.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/lsc/dsf-lsc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../../bin/view"
	cd /home/ubuntu/lsc/dsf-lsc/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/view.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/view.dir/build: ../bin/view

.PHONY : src/CMakeFiles/view.dir/build

src/CMakeFiles/view.dir/clean:
	cd /home/ubuntu/lsc/dsf-lsc/build/src && $(CMAKE_COMMAND) -P CMakeFiles/view.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/view.dir/clean

src/CMakeFiles/view.dir/depend:
	cd /home/ubuntu/lsc/dsf-lsc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/lsc/dsf-lsc /home/ubuntu/lsc/dsf-lsc/src /home/ubuntu/lsc/dsf-lsc/build /home/ubuntu/lsc/dsf-lsc/build/src /home/ubuntu/lsc/dsf-lsc/build/src/CMakeFiles/view.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/view.dir/depend

