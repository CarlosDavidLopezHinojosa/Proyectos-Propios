# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build"

# Include any dependencies generated for this target.
include CMakeFiles/lb2_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lb2_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lb2_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lb2_test.dir/flags.make

CMakeFiles/lb2_test.dir/lb2.cpp.o: CMakeFiles/lb2_test.dir/flags.make
CMakeFiles/lb2_test.dir/lb2.cpp.o: ../lb2.cpp
CMakeFiles/lb2_test.dir/lb2.cpp.o: CMakeFiles/lb2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lb2_test.dir/lb2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lb2_test.dir/lb2.cpp.o -MF CMakeFiles/lb2_test.dir/lb2.cpp.o.d -o CMakeFiles/lb2_test.dir/lb2.cpp.o -c "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/lb2.cpp"

CMakeFiles/lb2_test.dir/lb2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lb2_test.dir/lb2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/lb2.cpp" > CMakeFiles/lb2_test.dir/lb2.cpp.i

CMakeFiles/lb2_test.dir/lb2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lb2_test.dir/lb2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/lb2.cpp" -o CMakeFiles/lb2_test.dir/lb2.cpp.s

# Object files for target lb2_test
lb2_test_OBJECTS = \
"CMakeFiles/lb2_test.dir/lb2.cpp.o"

# External object files for target lb2_test
lb2_test_EXTERNAL_OBJECTS =

lb2_test: CMakeFiles/lb2_test.dir/lb2.cpp.o
lb2_test: CMakeFiles/lb2_test.dir/build.make
lb2_test: CMakeFiles/lb2_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lb2_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lb2_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lb2_test.dir/build: lb2_test
.PHONY : CMakeFiles/lb2_test.dir/build

CMakeFiles/lb2_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lb2_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lb2_test.dir/clean

CMakeFiles/lb2_test.dir/depend:
	cd "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build/CMakeFiles/lb2_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lb2_test.dir/depend

