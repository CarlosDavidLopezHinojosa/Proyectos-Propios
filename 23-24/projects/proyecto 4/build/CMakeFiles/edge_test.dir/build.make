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
CMAKE_SOURCE_DIR = "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/build"

# Include any dependencies generated for this target.
include CMakeFiles/edge_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/edge_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/edge_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/edge_test.dir/flags.make

CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o: CMakeFiles/edge_test.dir/flags.make
CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o: ../Edge/edge_test.cpp
CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o: CMakeFiles/edge_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o -MF CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o.d -o CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o -c "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/Edge/edge_test.cpp"

CMakeFiles/edge_test.dir/Edge/edge_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edge_test.dir/Edge/edge_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/Edge/edge_test.cpp" > CMakeFiles/edge_test.dir/Edge/edge_test.cpp.i

CMakeFiles/edge_test.dir/Edge/edge_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edge_test.dir/Edge/edge_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/Edge/edge_test.cpp" -o CMakeFiles/edge_test.dir/Edge/edge_test.cpp.s

# Object files for target edge_test
edge_test_OBJECTS = \
"CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o"

# External object files for target edge_test
edge_test_EXTERNAL_OBJECTS =

edge_test: CMakeFiles/edge_test.dir/Edge/edge_test.cpp.o
edge_test: CMakeFiles/edge_test.dir/build.make
edge_test: CMakeFiles/edge_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable edge_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/edge_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/edge_test.dir/build: edge_test
.PHONY : CMakeFiles/edge_test.dir/build

CMakeFiles/edge_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/edge_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/edge_test.dir/clean

CMakeFiles/edge_test.dir/depend:
	cd "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/build" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/build" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 4/build/CMakeFiles/edge_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/edge_test.dir/depend

