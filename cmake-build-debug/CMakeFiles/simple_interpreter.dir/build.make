# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\college\projects\simple_interpreter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\college\projects\simple_interpreter\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/simple_interpreter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simple_interpreter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simple_interpreter.dir/flags.make

CMakeFiles/simple_interpreter.dir/main.c.obj: CMakeFiles/simple_interpreter.dir/flags.make
CMakeFiles/simple_interpreter.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\college\projects\simple_interpreter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/simple_interpreter.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\simple_interpreter.dir\main.c.obj   -c D:\college\projects\simple_interpreter\main.c

CMakeFiles/simple_interpreter.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simple_interpreter.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\college\projects\simple_interpreter\main.c > CMakeFiles\simple_interpreter.dir\main.c.i

CMakeFiles/simple_interpreter.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simple_interpreter.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\college\projects\simple_interpreter\main.c -o CMakeFiles\simple_interpreter.dir\main.c.s

# Object files for target simple_interpreter
simple_interpreter_OBJECTS = \
"CMakeFiles/simple_interpreter.dir/main.c.obj"

# External object files for target simple_interpreter
simple_interpreter_EXTERNAL_OBJECTS =

simple_interpreter.exe: CMakeFiles/simple_interpreter.dir/main.c.obj
simple_interpreter.exe: CMakeFiles/simple_interpreter.dir/build.make
simple_interpreter.exe: CMakeFiles/simple_interpreter.dir/linklibs.rsp
simple_interpreter.exe: CMakeFiles/simple_interpreter.dir/objects1.rsp
simple_interpreter.exe: CMakeFiles/simple_interpreter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\college\projects\simple_interpreter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable simple_interpreter.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\simple_interpreter.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simple_interpreter.dir/build: simple_interpreter.exe

.PHONY : CMakeFiles/simple_interpreter.dir/build

CMakeFiles/simple_interpreter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\simple_interpreter.dir\cmake_clean.cmake
.PHONY : CMakeFiles/simple_interpreter.dir/clean

CMakeFiles/simple_interpreter.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\college\projects\simple_interpreter D:\college\projects\simple_interpreter D:\college\projects\simple_interpreter\cmake-build-debug D:\college\projects\simple_interpreter\cmake-build-debug D:\college\projects\simple_interpreter\cmake-build-debug\CMakeFiles\simple_interpreter.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simple_interpreter.dir/depend

