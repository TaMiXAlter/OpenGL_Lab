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
CMAKE_COMMAND = /snap/clion/275/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/275/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tami/Projects/OpenGL_Lab/HomeWork

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug

# Include any dependencies generated for this target.
include Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/compiler_depend.make

# Include the progress variables for this target.
include Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progress.make

# Include the compile flags for this target's objects.
include Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/flags.make

Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o: Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/flags.make
Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o: /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/smooth_opengl3/smooth_opengl3.c
Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o: Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o -MF CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o.d -o CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o -c /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/smooth_opengl3/smooth_opengl3.c

Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.i"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/smooth_opengl3/smooth_opengl3.c > CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.i

Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.s"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/smooth_opengl3/smooth_opengl3.c -o CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.s

# Object files for target smooth_opengl3
smooth_opengl3_OBJECTS = \
"CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o"

# External object files for target smooth_opengl3
smooth_opengl3_EXTERNAL_OBJECTS =

Thirdparty/freeglut/bin/smooth_opengl3: Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/progs/demos/smooth_opengl3/smooth_opengl3.c.o
Thirdparty/freeglut/bin/smooth_opengl3: Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/build.make
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libGLU.so
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libX11.so
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libXrandr.so
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libXi.so
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libGL.so
Thirdparty/freeglut/bin/smooth_opengl3: Thirdparty/freeglut/lib/libglut.so.3.12.0
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libX11.so
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libXrandr.so
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libXi.so
Thirdparty/freeglut/bin/smooth_opengl3: /usr/lib/x86_64-linux-gnu/libGL.so
Thirdparty/freeglut/bin/smooth_opengl3: Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/smooth_opengl3"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smooth_opengl3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/build: Thirdparty/freeglut/bin/smooth_opengl3
.PHONY : Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/build

Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/clean:
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && $(CMAKE_COMMAND) -P CMakeFiles/smooth_opengl3.dir/cmake_clean.cmake
.PHONY : Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/clean

Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/depend:
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tami/Projects/OpenGL_Lab/HomeWork /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Thirdparty/freeglut/CMakeFiles/smooth_opengl3.dir/depend

