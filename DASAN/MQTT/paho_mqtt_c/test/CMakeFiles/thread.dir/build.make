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
include test/CMakeFiles/thread.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/thread.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/thread.dir/flags.make

test/CMakeFiles/thread.dir/thread.c.o: test/CMakeFiles/thread.dir/flags.make
test/CMakeFiles/thread.dir/thread.c.o: test/thread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/CMakeFiles/thread.dir/thread.c.o"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/thread.dir/thread.c.o   -c /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/thread.c

test/CMakeFiles/thread.dir/thread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/thread.dir/thread.c.i"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/thread.c > CMakeFiles/thread.dir/thread.c.i

test/CMakeFiles/thread.dir/thread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/thread.dir/thread.c.s"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/thread.c -o CMakeFiles/thread.dir/thread.c.s

test/CMakeFiles/thread.dir/thread.c.o.requires:

.PHONY : test/CMakeFiles/thread.dir/thread.c.o.requires

test/CMakeFiles/thread.dir/thread.c.o.provides: test/CMakeFiles/thread.dir/thread.c.o.requires
	$(MAKE) -f test/CMakeFiles/thread.dir/build.make test/CMakeFiles/thread.dir/thread.c.o.provides.build
.PHONY : test/CMakeFiles/thread.dir/thread.c.o.provides

test/CMakeFiles/thread.dir/thread.c.o.provides.build: test/CMakeFiles/thread.dir/thread.c.o


test/CMakeFiles/thread.dir/__/src/Thread.c.o: test/CMakeFiles/thread.dir/flags.make
test/CMakeFiles/thread.dir/__/src/Thread.c.o: src/Thread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object test/CMakeFiles/thread.dir/__/src/Thread.c.o"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/thread.dir/__/src/Thread.c.o   -c /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/src/Thread.c

test/CMakeFiles/thread.dir/__/src/Thread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/thread.dir/__/src/Thread.c.i"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/src/Thread.c > CMakeFiles/thread.dir/__/src/Thread.c.i

test/CMakeFiles/thread.dir/__/src/Thread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/thread.dir/__/src/Thread.c.s"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/src/Thread.c -o CMakeFiles/thread.dir/__/src/Thread.c.s

test/CMakeFiles/thread.dir/__/src/Thread.c.o.requires:

.PHONY : test/CMakeFiles/thread.dir/__/src/Thread.c.o.requires

test/CMakeFiles/thread.dir/__/src/Thread.c.o.provides: test/CMakeFiles/thread.dir/__/src/Thread.c.o.requires
	$(MAKE) -f test/CMakeFiles/thread.dir/build.make test/CMakeFiles/thread.dir/__/src/Thread.c.o.provides.build
.PHONY : test/CMakeFiles/thread.dir/__/src/Thread.c.o.provides

test/CMakeFiles/thread.dir/__/src/Thread.c.o.provides.build: test/CMakeFiles/thread.dir/__/src/Thread.c.o


# Object files for target thread
thread_OBJECTS = \
"CMakeFiles/thread.dir/thread.c.o" \
"CMakeFiles/thread.dir/__/src/Thread.c.o"

# External object files for target thread
thread_EXTERNAL_OBJECTS =

test/thread: test/CMakeFiles/thread.dir/thread.c.o
test/thread: test/CMakeFiles/thread.dir/__/src/Thread.c.o
test/thread: test/CMakeFiles/thread.dir/build.make
test/thread: test/CMakeFiles/thread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable thread"
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/thread.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/thread.dir/build: test/thread

.PHONY : test/CMakeFiles/thread.dir/build

test/CMakeFiles/thread.dir/requires: test/CMakeFiles/thread.dir/thread.c.o.requires
test/CMakeFiles/thread.dir/requires: test/CMakeFiles/thread.dir/__/src/Thread.c.o.requires

.PHONY : test/CMakeFiles/thread.dir/requires

test/CMakeFiles/thread.dir/clean:
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test && $(CMAKE_COMMAND) -P CMakeFiles/thread.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/thread.dir/clean

test/CMakeFiles/thread.dir/depend:
	cd /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test /home/longvh/working/linux_project/DASAN/MQTT/paho_mqtt_c/test/CMakeFiles/thread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/thread.dir/depend

