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
CMAKE_SOURCE_DIR = /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c

# Include any dependencies generated for this target.
include test/CMakeFiles/test11.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test11.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test11.dir/flags.make

test/CMakeFiles/test11.dir/test11.c.o: test/CMakeFiles/test11.dir/flags.make
test/CMakeFiles/test11.dir/test11.c.o: test/test11.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/CMakeFiles/test11.dir/test11.c.o"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test11.dir/test11.c.o   -c /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/test11.c

test/CMakeFiles/test11.dir/test11.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test11.dir/test11.c.i"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/test11.c > CMakeFiles/test11.dir/test11.c.i

test/CMakeFiles/test11.dir/test11.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test11.dir/test11.c.s"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/test11.c -o CMakeFiles/test11.dir/test11.c.s

test/CMakeFiles/test11.dir/test11.c.o.requires:

.PHONY : test/CMakeFiles/test11.dir/test11.c.o.requires

test/CMakeFiles/test11.dir/test11.c.o.provides: test/CMakeFiles/test11.dir/test11.c.o.requires
	$(MAKE) -f test/CMakeFiles/test11.dir/build.make test/CMakeFiles/test11.dir/test11.c.o.provides.build
.PHONY : test/CMakeFiles/test11.dir/test11.c.o.provides

test/CMakeFiles/test11.dir/test11.c.o.provides.build: test/CMakeFiles/test11.dir/test11.c.o


# Object files for target test11
test11_OBJECTS = \
"CMakeFiles/test11.dir/test11.c.o"

# External object files for target test11
test11_EXTERNAL_OBJECTS =

test/test11: test/CMakeFiles/test11.dir/test11.c.o
test/test11: test/CMakeFiles/test11.dir/build.make
test/test11: src/libpaho-mqtt3a.so.1.3.1
test/test11: test/CMakeFiles/test11.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test11"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test11.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test11.dir/build: test/test11

.PHONY : test/CMakeFiles/test11.dir/build

test/CMakeFiles/test11.dir/requires: test/CMakeFiles/test11.dir/test11.c.o.requires

.PHONY : test/CMakeFiles/test11.dir/requires

test/CMakeFiles/test11.dir/clean:
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && $(CMAKE_COMMAND) -P CMakeFiles/test11.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test11.dir/clean

test/CMakeFiles/test11.dir/depend:
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/CMakeFiles/test11.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test11.dir/depend

