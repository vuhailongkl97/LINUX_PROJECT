# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c

# Include any dependencies generated for this target.
include test/CMakeFiles/test_issue373.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_issue373.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_issue373.dir/flags.make

test/CMakeFiles/test_issue373.dir/test_issue373.c.o: test/CMakeFiles/test_issue373.dir/flags.make
test/CMakeFiles/test_issue373.dir/test_issue373.c.o: test/test_issue373.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/CMakeFiles/test_issue373.dir/test_issue373.c.o"
	cd /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_issue373.dir/test_issue373.c.o   -c /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test/test_issue373.c

test/CMakeFiles/test_issue373.dir/test_issue373.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_issue373.dir/test_issue373.c.i"
	cd /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test/test_issue373.c > CMakeFiles/test_issue373.dir/test_issue373.c.i

test/CMakeFiles/test_issue373.dir/test_issue373.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_issue373.dir/test_issue373.c.s"
	cd /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test/test_issue373.c -o CMakeFiles/test_issue373.dir/test_issue373.c.s

test/CMakeFiles/test_issue373.dir/test_issue373.c.o.requires:

.PHONY : test/CMakeFiles/test_issue373.dir/test_issue373.c.o.requires

test/CMakeFiles/test_issue373.dir/test_issue373.c.o.provides: test/CMakeFiles/test_issue373.dir/test_issue373.c.o.requires
	$(MAKE) -f test/CMakeFiles/test_issue373.dir/build.make test/CMakeFiles/test_issue373.dir/test_issue373.c.o.provides.build
.PHONY : test/CMakeFiles/test_issue373.dir/test_issue373.c.o.provides

test/CMakeFiles/test_issue373.dir/test_issue373.c.o.provides.build: test/CMakeFiles/test_issue373.dir/test_issue373.c.o


# Object files for target test_issue373
test_issue373_OBJECTS = \
"CMakeFiles/test_issue373.dir/test_issue373.c.o"

# External object files for target test_issue373
test_issue373_EXTERNAL_OBJECTS =

test/test_issue373: test/CMakeFiles/test_issue373.dir/test_issue373.c.o
test/test_issue373: test/CMakeFiles/test_issue373.dir/build.make
test/test_issue373: src/libpaho-mqtt3a.so.1.3.1
test/test_issue373: test/CMakeFiles/test_issue373.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_issue373"
	cd /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_issue373.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_issue373.dir/build: test/test_issue373

.PHONY : test/CMakeFiles/test_issue373.dir/build

test/CMakeFiles/test_issue373.dir/requires: test/CMakeFiles/test_issue373.dir/test_issue373.c.o.requires

.PHONY : test/CMakeFiles/test_issue373.dir/requires

test/CMakeFiles/test_issue373.dir/clean:
	cd /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test && $(CMAKE_COMMAND) -P CMakeFiles/test_issue373.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_issue373.dir/clean

test/CMakeFiles/test_issue373.dir/depend:
	cd /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test /home/longvh/linux_project/DASAN/MQTT/paho.mqtt.c/test/CMakeFiles/test_issue373.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_issue373.dir/depend

