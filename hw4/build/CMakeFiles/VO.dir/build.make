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
CMAKE_SOURCE_DIR = /home/sjtu/Documents/hw4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sjtu/Documents/hw4/build

# Include any dependencies generated for this target.
include CMakeFiles/VO.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VO.dir/flags.make

CMakeFiles/VO.dir/src/VO.cpp.o: CMakeFiles/VO.dir/flags.make
CMakeFiles/VO.dir/src/VO.cpp.o: ../src/VO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjtu/Documents/hw4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VO.dir/src/VO.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VO.dir/src/VO.cpp.o -c /home/sjtu/Documents/hw4/src/VO.cpp

CMakeFiles/VO.dir/src/VO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VO.dir/src/VO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjtu/Documents/hw4/src/VO.cpp > CMakeFiles/VO.dir/src/VO.cpp.i

CMakeFiles/VO.dir/src/VO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VO.dir/src/VO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjtu/Documents/hw4/src/VO.cpp -o CMakeFiles/VO.dir/src/VO.cpp.s

# Object files for target VO
VO_OBJECTS = \
"CMakeFiles/VO.dir/src/VO.cpp.o"

# External object files for target VO
VO_EXTERNAL_OBJECTS =

libVO.a: CMakeFiles/VO.dir/src/VO.cpp.o
libVO.a: CMakeFiles/VO.dir/build.make
libVO.a: CMakeFiles/VO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sjtu/Documents/hw4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libVO.a"
	$(CMAKE_COMMAND) -P CMakeFiles/VO.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VO.dir/build: libVO.a

.PHONY : CMakeFiles/VO.dir/build

CMakeFiles/VO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VO.dir/clean

CMakeFiles/VO.dir/depend:
	cd /home/sjtu/Documents/hw4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sjtu/Documents/hw4 /home/sjtu/Documents/hw4 /home/sjtu/Documents/hw4/build /home/sjtu/Documents/hw4/build /home/sjtu/Documents/hw4/build/CMakeFiles/VO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VO.dir/depend
