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
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tami/OpenGl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tami/OpenGl/build

# Include any dependencies generated for this target.
include Thirdparty/freeglut/CMakeFiles/resizer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Thirdparty/freeglut/CMakeFiles/resizer.dir/compiler_depend.make

# Include the progress variables for this target.
include Thirdparty/freeglut/CMakeFiles/resizer.dir/progress.make

# Include the compile flags for this target's objects.
include Thirdparty/freeglut/CMakeFiles/resizer.dir/flags.make

Thirdparty/freeglut/CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o: Thirdparty/freeglut/CMakeFiles/resizer.dir/flags.make
Thirdparty/freeglut/CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o: /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/resizer/resizer.c
Thirdparty/freeglut/CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o: Thirdparty/freeglut/CMakeFiles/resizer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tami/OpenGl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Thirdparty/freeglut/CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Thirdparty/freeglut/CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o -MF CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o.d -o CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o -c /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/resizer/resizer.c

Thirdparty/freeglut/CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.i"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/resizer/resizer.c > CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.i

Thirdparty/freeglut/CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.s"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/resizer/resizer.c -o CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.s

# Object files for target resizer
resizer_OBJECTS = \
"CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o"

# External object files for target resizer
resizer_EXTERNAL_OBJECTS =

Thirdparty/freeglut/bin/resizer: Thirdparty/freeglut/CMakeFiles/resizer.dir/progs/demos/resizer/resizer.c.o
Thirdparty/freeglut/bin/resizer: Thirdparty/freeglut/CMakeFiles/resizer.dir/build.make
Thirdparty/freeglut/bin/resizer: /usr/lib/x86_64-linux-gnu/libGLU.so
Thirdparty/freeglut/bin/resizer: /usr/lib/x86_64-linux-gnu/libX11.so
Thirdparty/freeglut/bin/resizer: /usr/lib/x86_64-linux-gnu/libXi.so
Thirdparty/freeglut/bin/resizer: /usr/lib/x86_64-linux-gnu/libGL.so
Thirdparty/freeglut/bin/resizer: Thirdparty/freeglut/lib/libglut.so.3.12.0
Thirdparty/freeglut/bin/resizer: /usr/lib/x86_64-linux-gnu/libX11.so
Thirdparty/freeglut/bin/resizer: /usr/lib/x86_64-linux-gnu/libXi.so
Thirdparty/freeglut/bin/resizer: /usr/lib/x86_64-linux-gnu/libGL.so
Thirdparty/freeglut/bin/resizer: Thirdparty/freeglut/CMakeFiles/resizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tami/OpenGl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/resizer"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/resizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Thirdparty/freeglut/CMakeFiles/resizer.dir/build: Thirdparty/freeglut/bin/resizer
.PHONY : Thirdparty/freeglut/CMakeFiles/resizer.dir/build

Thirdparty/freeglut/CMakeFiles/resizer.dir/clean:
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && $(CMAKE_COMMAND) -P CMakeFiles/resizer.dir/cmake_clean.cmake
.PHONY : Thirdparty/freeglut/CMakeFiles/resizer.dir/clean

Thirdparty/freeglut/CMakeFiles/resizer.dir/depend:
	cd /home/tami/OpenGl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tami/OpenGl /home/tami/OpenGl/Thirdparty/freeglut /home/tami/OpenGl/build /home/tami/OpenGl/build/Thirdparty/freeglut /home/tami/OpenGl/build/Thirdparty/freeglut/CMakeFiles/resizer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Thirdparty/freeglut/CMakeFiles/resizer.dir/depend

