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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/denys/CLionProjects/diary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/denys/CLionProjects/diary/build

# Include any dependencies generated for this target.
include CMakeFiles/ftxui-starter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ftxui-starter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ftxui-starter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ftxui-starter.dir/flags.make

CMakeFiles/ftxui-starter.dir/main.cpp.o: CMakeFiles/ftxui-starter.dir/flags.make
CMakeFiles/ftxui-starter.dir/main.cpp.o: /home/denys/CLionProjects/diary/main.cpp
CMakeFiles/ftxui-starter.dir/main.cpp.o: CMakeFiles/ftxui-starter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/denys/CLionProjects/diary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ftxui-starter.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ftxui-starter.dir/main.cpp.o -MF CMakeFiles/ftxui-starter.dir/main.cpp.o.d -o CMakeFiles/ftxui-starter.dir/main.cpp.o -c /home/denys/CLionProjects/diary/main.cpp

CMakeFiles/ftxui-starter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ftxui-starter.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denys/CLionProjects/diary/main.cpp > CMakeFiles/ftxui-starter.dir/main.cpp.i

CMakeFiles/ftxui-starter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ftxui-starter.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denys/CLionProjects/diary/main.cpp -o CMakeFiles/ftxui-starter.dir/main.cpp.s

# Object files for target ftxui-starter
ftxui__starter_OBJECTS = \
"CMakeFiles/ftxui-starter.dir/main.cpp.o"

# External object files for target ftxui-starter
ftxui__starter_EXTERNAL_OBJECTS =

ftxui-starter: CMakeFiles/ftxui-starter.dir/main.cpp.o
ftxui-starter: CMakeFiles/ftxui-starter.dir/build.make
ftxui-starter: _deps/ftxui-build/libftxui-screen.a
ftxui-starter: _deps/ftxui-build/libftxui-dom.a
ftxui-starter: _deps/ftxui-build/libftxui-component.a
ftxui-starter: _deps/ftxui-build/libftxui-dom.a
ftxui-starter: _deps/ftxui-build/libftxui-screen.a
ftxui-starter: CMakeFiles/ftxui-starter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/denys/CLionProjects/diary/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ftxui-starter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftxui-starter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ftxui-starter.dir/build: ftxui-starter
.PHONY : CMakeFiles/ftxui-starter.dir/build

CMakeFiles/ftxui-starter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ftxui-starter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ftxui-starter.dir/clean

CMakeFiles/ftxui-starter.dir/depend:
	cd /home/denys/CLionProjects/diary/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/denys/CLionProjects/diary /home/denys/CLionProjects/diary /home/denys/CLionProjects/diary/build /home/denys/CLionProjects/diary/build /home/denys/CLionProjects/diary/build/CMakeFiles/ftxui-starter.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ftxui-starter.dir/depend

