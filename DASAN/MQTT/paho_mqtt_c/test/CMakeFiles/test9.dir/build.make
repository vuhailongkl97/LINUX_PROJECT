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
CMAKE_SOURCE_DIR = /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c

# Include any dependencies generated for this target.
include test/CMakeFiles/test9.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test9.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test9.dir/flags.make

test/CMakeFiles/test9.dir/test9.c.o: test/CMakeFiles/test9.dir/flags.make
test/CMakeFiles/test9.dir/test9.c.o: test/test9.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/CMakeFiles/test9.dir/test9.c.o"
	cd /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test9.dir/test9.c.o   -c /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/test9.c

test/CMakeFiles/test9.dir/test9.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test9.dir/test9.c.i"
	cd /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/test9.c > CMakeFiles/test9.dir/test9.c.i

test/CMakeFiles/test9.dir/test9.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test9.dir/test9.c.s"
	cd /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/test9.c -o CMakeFiles/test9.dir/test9.c.s

test/CMakeFiles/test9.dir/test9.c.o.requires:

.PHONY : test/CMakeFiles/test9.dir/test9.c.o.requires

test/CMakeFiles/test9.dir/test9.c.o.provides: test/CMakeFiles/test9.dir/test9.c.o.requires
	$(MAKE) -f test/CMakeFiles/test9.dir/build.make test/CMakeFiles/test9.dir/test9.c.o.provides.build
.PHONY : test/CMakeFiles/test9.dir/test9.c.o.provides

test/CMakeFiles/test9.dir/test9.c.o.provides.build: test/CMakeFiles/test9.dir/test9.c.o


# Object files for target test9
test9_OBJECTS = \
"CMakeFiles/test9.dir/test9.c.o"

# External object files for target test9
test9_EXTERNAL_OBJECTS =

test/test9: test/CMakeFiles/test9.dir/test9.c.o
test/test9: test/CMakeFiles/test9.dir/build.make
test/test9: src/libpaho-mqtt3a.so.1.3.1
test/test9: test/CMakeFiles/test9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test9"
	cd /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test9.dir/build: test/test9

.PHONY : test/CMakeFiles/test9.dir/build

test/CMakeFiles/test9.dir/requires: test/CMakeFiles/test9.dir/test9.c.o.requires

.PHONY : test/CMakeFiles/test9.dir/requires

test/CMakeFiles/test9.dir/clean:
	cd /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && $(CMAKE_COMMAND) -P CMakeFiles/test9.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test9.dir/clean

test/CMakeFiles/test9.dir/depend:
	cd /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test /home/longkl/Desktop/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/CMakeFiles/test9.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test9.dir/depend

