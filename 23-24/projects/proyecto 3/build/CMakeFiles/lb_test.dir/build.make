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
include CMakeFiles/lb_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lb_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lb_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lb_test.dir/flags.make

CMakeFiles/lb_test.dir/lb.cpp.o: CMakeFiles/lb_test.dir/flags.make
CMakeFiles/lb_test.dir/lb.cpp.o: ../lb.cpp
CMakeFiles/lb_test.dir/lb.cpp.o: CMakeFiles/lb_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lb_test.dir/lb.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lb_test.dir/lb.cpp.o -MF CMakeFiles/lb_test.dir/lb.cpp.o.d -o CMakeFiles/lb_test.dir/lb.cpp.o -c "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/lb.cpp"

CMakeFiles/lb_test.dir/lb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lb_test.dir/lb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/lb.cpp" > CMakeFiles/lb_test.dir/lb.cpp.i

CMakeFiles/lb_test.dir/lb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lb_test.dir/lb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/lb.cpp" -o CMakeFiles/lb_test.dir/lb.cpp.s

# Object files for target lb_test
lb_test_OBJECTS = \
"CMakeFiles/lb_test.dir/lb.cpp.o"

# External object files for target lb_test
lb_test_EXTERNAL_OBJECTS =

lb_test: CMakeFiles/lb_test.dir/lb.cpp.o
lb_test: CMakeFiles/lb_test.dir/build.make
lb_test: CMakeFiles/lb_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lb_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lb_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lb_test.dir/build: lb_test
.PHONY : CMakeFiles/lb_test.dir/build

CMakeFiles/lb_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lb_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lb_test.dir/clean

CMakeFiles/lb_test.dir/depend:
	cd "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build" "/home/carlos/Escritorio/Proyectos Propios/23-24/projects/proyecto 3/build/CMakeFiles/lb_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lb_test.dir/depend

