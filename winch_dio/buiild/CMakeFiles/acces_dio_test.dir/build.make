# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /root/Documents/DIODO_Test/access_wrapper/test_dio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Documents/DIODO_Test/access_wrapper/test_dio/buiild

# Include any dependencies generated for this target.
include CMakeFiles/acces_dio_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/acces_dio_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/acces_dio_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/acces_dio_test.dir/flags.make

CMakeFiles/acces_dio_test.dir/main.cpp.o: CMakeFiles/acces_dio_test.dir/flags.make
CMakeFiles/acces_dio_test.dir/main.cpp.o: ../main.cpp
CMakeFiles/acces_dio_test.dir/main.cpp.o: CMakeFiles/acces_dio_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Documents/DIODO_Test/access_wrapper/test_dio/buiild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/acces_dio_test.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/acces_dio_test.dir/main.cpp.o -MF CMakeFiles/acces_dio_test.dir/main.cpp.o.d -o CMakeFiles/acces_dio_test.dir/main.cpp.o -c /root/Documents/DIODO_Test/access_wrapper/test_dio/main.cpp

CMakeFiles/acces_dio_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acces_dio_test.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Documents/DIODO_Test/access_wrapper/test_dio/main.cpp > CMakeFiles/acces_dio_test.dir/main.cpp.i

CMakeFiles/acces_dio_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acces_dio_test.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Documents/DIODO_Test/access_wrapper/test_dio/main.cpp -o CMakeFiles/acces_dio_test.dir/main.cpp.s

CMakeFiles/acces_dio_test.dir/aiousb.cpp.o: CMakeFiles/acces_dio_test.dir/flags.make
CMakeFiles/acces_dio_test.dir/aiousb.cpp.o: ../aiousb.cpp
CMakeFiles/acces_dio_test.dir/aiousb.cpp.o: CMakeFiles/acces_dio_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Documents/DIODO_Test/access_wrapper/test_dio/buiild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/acces_dio_test.dir/aiousb.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/acces_dio_test.dir/aiousb.cpp.o -MF CMakeFiles/acces_dio_test.dir/aiousb.cpp.o.d -o CMakeFiles/acces_dio_test.dir/aiousb.cpp.o -c /root/Documents/DIODO_Test/access_wrapper/test_dio/aiousb.cpp

CMakeFiles/acces_dio_test.dir/aiousb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acces_dio_test.dir/aiousb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Documents/DIODO_Test/access_wrapper/test_dio/aiousb.cpp > CMakeFiles/acces_dio_test.dir/aiousb.cpp.i

CMakeFiles/acces_dio_test.dir/aiousb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acces_dio_test.dir/aiousb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Documents/DIODO_Test/access_wrapper/test_dio/aiousb.cpp -o CMakeFiles/acces_dio_test.dir/aiousb.cpp.s

CMakeFiles/acces_dio_test.dir/io_access.cpp.o: CMakeFiles/acces_dio_test.dir/flags.make
CMakeFiles/acces_dio_test.dir/io_access.cpp.o: ../io_access.cpp
CMakeFiles/acces_dio_test.dir/io_access.cpp.o: CMakeFiles/acces_dio_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Documents/DIODO_Test/access_wrapper/test_dio/buiild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/acces_dio_test.dir/io_access.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/acces_dio_test.dir/io_access.cpp.o -MF CMakeFiles/acces_dio_test.dir/io_access.cpp.o.d -o CMakeFiles/acces_dio_test.dir/io_access.cpp.o -c /root/Documents/DIODO_Test/access_wrapper/test_dio/io_access.cpp

CMakeFiles/acces_dio_test.dir/io_access.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acces_dio_test.dir/io_access.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Documents/DIODO_Test/access_wrapper/test_dio/io_access.cpp > CMakeFiles/acces_dio_test.dir/io_access.cpp.i

CMakeFiles/acces_dio_test.dir/io_access.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acces_dio_test.dir/io_access.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Documents/DIODO_Test/access_wrapper/test_dio/io_access.cpp -o CMakeFiles/acces_dio_test.dir/io_access.cpp.s

CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o: CMakeFiles/acces_dio_test.dir/flags.make
CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o: ../read_write_dio.cpp
CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o: CMakeFiles/acces_dio_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Documents/DIODO_Test/access_wrapper/test_dio/buiild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o -MF CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o.d -o CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o -c /root/Documents/DIODO_Test/access_wrapper/test_dio/read_write_dio.cpp

CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Documents/DIODO_Test/access_wrapper/test_dio/read_write_dio.cpp > CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.i

CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Documents/DIODO_Test/access_wrapper/test_dio/read_write_dio.cpp -o CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.s

CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o: CMakeFiles/acces_dio_test.dir/flags.make
CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o: ../adc-threads.cpp
CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o: CMakeFiles/acces_dio_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Documents/DIODO_Test/access_wrapper/test_dio/buiild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o -MF CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o.d -o CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o -c /root/Documents/DIODO_Test/access_wrapper/test_dio/adc-threads.cpp

CMakeFiles/acces_dio_test.dir/adc-threads.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acces_dio_test.dir/adc-threads.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Documents/DIODO_Test/access_wrapper/test_dio/adc-threads.cpp > CMakeFiles/acces_dio_test.dir/adc-threads.cpp.i

CMakeFiles/acces_dio_test.dir/adc-threads.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acces_dio_test.dir/adc-threads.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Documents/DIODO_Test/access_wrapper/test_dio/adc-threads.cpp -o CMakeFiles/acces_dio_test.dir/adc-threads.cpp.s

# Object files for target acces_dio_test
acces_dio_test_OBJECTS = \
"CMakeFiles/acces_dio_test.dir/main.cpp.o" \
"CMakeFiles/acces_dio_test.dir/aiousb.cpp.o" \
"CMakeFiles/acces_dio_test.dir/io_access.cpp.o" \
"CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o" \
"CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o"

# External object files for target acces_dio_test
acces_dio_test_EXTERNAL_OBJECTS =

acces_dio_test: CMakeFiles/acces_dio_test.dir/main.cpp.o
acces_dio_test: CMakeFiles/acces_dio_test.dir/aiousb.cpp.o
acces_dio_test: CMakeFiles/acces_dio_test.dir/io_access.cpp.o
acces_dio_test: CMakeFiles/acces_dio_test.dir/read_write_dio.cpp.o
acces_dio_test: CMakeFiles/acces_dio_test.dir/adc-threads.cpp.o
acces_dio_test: CMakeFiles/acces_dio_test.dir/build.make
acces_dio_test: CMakeFiles/acces_dio_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/Documents/DIODO_Test/access_wrapper/test_dio/buiild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable acces_dio_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/acces_dio_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/acces_dio_test.dir/build: acces_dio_test
.PHONY : CMakeFiles/acces_dio_test.dir/build

CMakeFiles/acces_dio_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/acces_dio_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/acces_dio_test.dir/clean

CMakeFiles/acces_dio_test.dir/depend:
	cd /root/Documents/DIODO_Test/access_wrapper/test_dio/buiild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Documents/DIODO_Test/access_wrapper/test_dio /root/Documents/DIODO_Test/access_wrapper/test_dio /root/Documents/DIODO_Test/access_wrapper/test_dio/buiild /root/Documents/DIODO_Test/access_wrapper/test_dio/buiild /root/Documents/DIODO_Test/access_wrapper/test_dio/buiild/CMakeFiles/acces_dio_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/acces_dio_test.dir/depend

