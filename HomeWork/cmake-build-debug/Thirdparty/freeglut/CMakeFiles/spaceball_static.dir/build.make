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
CMAKE_COMMAND = /snap/clion/277/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/277/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tami/Projects/OpenGL_Lab/HomeWork

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug

# Include any dependencies generated for this target.
include Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/compiler_depend.make

# Include the progress variables for this target.
include Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progress.make

# Include the compile flags for this target's objects.
include Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/flags.make

Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o: Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/flags.make
Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o: /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/spaceball/spaceball.c
Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o: Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o -MF CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o.d -o CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o -c /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/spaceball/spaceball.c

Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.i"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/spaceball/spaceball.c > CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.i

Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.s"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/spaceball/spaceball.c -o CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.s

Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o: Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/flags.make
Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o: /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/spaceball/vmath.c
Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o: Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o -MF CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o.d -o CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o -c /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/spaceball/vmath.c

Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.i"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/spaceball/vmath.c > CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.i

Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.s"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut/progs/demos/spaceball/vmath.c -o CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.s

# Object files for target spaceball_static
spaceball_static_OBJECTS = \
"CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o" \
"CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o"

# External object files for target spaceball_static
spaceball_static_EXTERNAL_OBJECTS =

Thirdparty/freeglut/bin/spaceball_static: Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/spaceball.c.o
Thirdparty/freeglut/bin/spaceball_static: Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/progs/demos/spaceball/vmath.c.o
Thirdparty/freeglut/bin/spaceball_static: Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/build.make
Thirdparty/freeglut/bin/spaceball_static: /usr/lib/x86_64-linux-gnu/libGLU.so
Thirdparty/freeglut/bin/spaceball_static: /usr/lib/x86_64-linux-gnu/libX11.so
Thirdparty/freeglut/bin/spaceball_static: /usr/lib/x86_64-linux-gnu/libXrandr.so
Thirdparty/freeglut/bin/spaceball_static: /usr/lib/x86_64-linux-gnu/libXi.so
Thirdparty/freeglut/bin/spaceball_static: Thirdparty/freeglut/lib/libglut.a
Thirdparty/freeglut/bin/spaceball_static: /usr/lib/x86_64-linux-gnu/libX11.so
Thirdparty/freeglut/bin/spaceball_static: /usr/lib/x86_64-linux-gnu/libXrandr.so
Thirdparty/freeglut/bin/spaceball_static: /usr/lib/x86_64-linux-gnu/libXi.so
Thirdparty/freeglut/bin/spaceball_static: Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable bin/spaceball_static"
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spaceball_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/build: Thirdparty/freeglut/bin/spaceball_static
.PHONY : Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/build

Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/clean:
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut && $(CMAKE_COMMAND) -P CMakeFiles/spaceball_static.dir/cmake_clean.cmake
.PHONY : Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/clean

Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/depend:
	cd /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tami/Projects/OpenGL_Lab/HomeWork /home/tami/Projects/OpenGL_Lab/HomeWork/Thirdparty/freeglut /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut /home/tami/Projects/OpenGL_Lab/HomeWork/cmake-build-debug/Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Thirdparty/freeglut/CMakeFiles/spaceball_static.dir/depend

