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
include Thirdparty/freeglut/CMakeFiles/shapes_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Thirdparty/freeglut/CMakeFiles/shapes_static.dir/compiler_depend.make

# Include the progress variables for this target.
include Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progress.make

# Include the compile flags for this target's objects.
include Thirdparty/freeglut/CMakeFiles/shapes_static.dir/flags.make

Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o: Thirdparty/freeglut/CMakeFiles/shapes_static.dir/flags.make
Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o: /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/shapes/shapes.c
Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o: Thirdparty/freeglut/CMakeFiles/shapes_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tami/OpenGl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o -MF CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o.d -o CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o -c /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/shapes/shapes.c

Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.i"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/shapes/shapes.c > CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.i

Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.s"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/shapes/shapes.c -o CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.s

Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o: Thirdparty/freeglut/CMakeFiles/shapes_static.dir/flags.make
Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o: /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/shapes/glmatrix.c
Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o: Thirdparty/freeglut/CMakeFiles/shapes_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tami/OpenGl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o -MF CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o.d -o CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o -c /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/shapes/glmatrix.c

Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.i"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/shapes/glmatrix.c > CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.i

Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.s"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tami/OpenGl/Thirdparty/freeglut/progs/demos/shapes/glmatrix.c -o CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.s

# Object files for target shapes_static
shapes_static_OBJECTS = \
"CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o" \
"CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o"

# External object files for target shapes_static
shapes_static_EXTERNAL_OBJECTS =

Thirdparty/freeglut/bin/shapes_static: Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/shapes.c.o
Thirdparty/freeglut/bin/shapes_static: Thirdparty/freeglut/CMakeFiles/shapes_static.dir/progs/demos/shapes/glmatrix.c.o
Thirdparty/freeglut/bin/shapes_static: Thirdparty/freeglut/CMakeFiles/shapes_static.dir/build.make
Thirdparty/freeglut/bin/shapes_static: /usr/lib/x86_64-linux-gnu/libGLU.so
Thirdparty/freeglut/bin/shapes_static: /usr/lib/x86_64-linux-gnu/libX11.so
Thirdparty/freeglut/bin/shapes_static: /usr/lib/x86_64-linux-gnu/libXi.so
Thirdparty/freeglut/bin/shapes_static: /usr/lib/x86_64-linux-gnu/libGL.so
Thirdparty/freeglut/bin/shapes_static: Thirdparty/freeglut/lib/libglut.a
Thirdparty/freeglut/bin/shapes_static: /usr/lib/x86_64-linux-gnu/libX11.so
Thirdparty/freeglut/bin/shapes_static: /usr/lib/x86_64-linux-gnu/libXi.so
Thirdparty/freeglut/bin/shapes_static: /usr/lib/x86_64-linux-gnu/libGL.so
Thirdparty/freeglut/bin/shapes_static: Thirdparty/freeglut/CMakeFiles/shapes_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tami/OpenGl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable bin/shapes_static"
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shapes_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Thirdparty/freeglut/CMakeFiles/shapes_static.dir/build: Thirdparty/freeglut/bin/shapes_static
.PHONY : Thirdparty/freeglut/CMakeFiles/shapes_static.dir/build

Thirdparty/freeglut/CMakeFiles/shapes_static.dir/clean:
	cd /home/tami/OpenGl/build/Thirdparty/freeglut && $(CMAKE_COMMAND) -P CMakeFiles/shapes_static.dir/cmake_clean.cmake
.PHONY : Thirdparty/freeglut/CMakeFiles/shapes_static.dir/clean

Thirdparty/freeglut/CMakeFiles/shapes_static.dir/depend:
	cd /home/tami/OpenGl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tami/OpenGl /home/tami/OpenGl/Thirdparty/freeglut /home/tami/OpenGl/build /home/tami/OpenGl/build/Thirdparty/freeglut /home/tami/OpenGl/build/Thirdparty/freeglut/CMakeFiles/shapes_static.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Thirdparty/freeglut/CMakeFiles/shapes_static.dir/depend

