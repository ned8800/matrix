# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sanya/PROJECT_FILMS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sanya/PROJECT_FILMS

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sanya/PROJECT_FILMS/CMakeFiles /home/sanya/PROJECT_FILMS/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sanya/PROJECT_FILMS/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named server

# Build rule for target.
server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 server
.PHONY : server

# fast build rule for target.
server/fast:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/build
.PHONY : server/fast

prj/src/connection.o: prj/src/connection.cpp.o

.PHONY : prj/src/connection.o

# target to build an object file
prj/src/connection.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/connection.cpp.o
.PHONY : prj/src/connection.cpp.o

prj/src/connection.i: prj/src/connection.cpp.i

.PHONY : prj/src/connection.i

# target to preprocess a source file
prj/src/connection.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/connection.cpp.i
.PHONY : prj/src/connection.cpp.i

prj/src/connection.s: prj/src/connection.cpp.s

.PHONY : prj/src/connection.s

# target to generate assembly for a file
prj/src/connection.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/connection.cpp.s
.PHONY : prj/src/connection.cpp.s

prj/src/connection_manager.o: prj/src/connection_manager.cpp.o

.PHONY : prj/src/connection_manager.o

# target to build an object file
prj/src/connection_manager.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/connection_manager.cpp.o
.PHONY : prj/src/connection_manager.cpp.o

prj/src/connection_manager.i: prj/src/connection_manager.cpp.i

.PHONY : prj/src/connection_manager.i

# target to preprocess a source file
prj/src/connection_manager.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/connection_manager.cpp.i
.PHONY : prj/src/connection_manager.cpp.i

prj/src/connection_manager.s: prj/src/connection_manager.cpp.s

.PHONY : prj/src/connection_manager.s

# target to generate assembly for a file
prj/src/connection_manager.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/connection_manager.cpp.s
.PHONY : prj/src/connection_manager.cpp.s

prj/src/database.o: prj/src/database.cpp.o

.PHONY : prj/src/database.o

# target to build an object file
prj/src/database.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/database.cpp.o
.PHONY : prj/src/database.cpp.o

prj/src/database.i: prj/src/database.cpp.i

.PHONY : prj/src/database.i

# target to preprocess a source file
prj/src/database.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/database.cpp.i
.PHONY : prj/src/database.cpp.i

prj/src/database.s: prj/src/database.cpp.s

.PHONY : prj/src/database.s

# target to generate assembly for a file
prj/src/database.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/database.cpp.s
.PHONY : prj/src/database.cpp.s

prj/src/database_manager.o: prj/src/database_manager.cpp.o

.PHONY : prj/src/database_manager.o

# target to build an object file
prj/src/database_manager.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/database_manager.cpp.o
.PHONY : prj/src/database_manager.cpp.o

prj/src/database_manager.i: prj/src/database_manager.cpp.i

.PHONY : prj/src/database_manager.i

# target to preprocess a source file
prj/src/database_manager.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/database_manager.cpp.i
.PHONY : prj/src/database_manager.cpp.i

prj/src/database_manager.s: prj/src/database_manager.cpp.s

.PHONY : prj/src/database_manager.s

# target to generate assembly for a file
prj/src/database_manager.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/database_manager.cpp.s
.PHONY : prj/src/database_manager.cpp.s

prj/src/main.o: prj/src/main.cpp.o

.PHONY : prj/src/main.o

# target to build an object file
prj/src/main.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/main.cpp.o
.PHONY : prj/src/main.cpp.o

prj/src/main.i: prj/src/main.cpp.i

.PHONY : prj/src/main.i

# target to preprocess a source file
prj/src/main.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/main.cpp.i
.PHONY : prj/src/main.cpp.i

prj/src/main.s: prj/src/main.cpp.s

.PHONY : prj/src/main.s

# target to generate assembly for a file
prj/src/main.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/main.cpp.s
.PHONY : prj/src/main.cpp.s

prj/src/mime_types.o: prj/src/mime_types.cpp.o

.PHONY : prj/src/mime_types.o

# target to build an object file
prj/src/mime_types.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/mime_types.cpp.o
.PHONY : prj/src/mime_types.cpp.o

prj/src/mime_types.i: prj/src/mime_types.cpp.i

.PHONY : prj/src/mime_types.i

# target to preprocess a source file
prj/src/mime_types.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/mime_types.cpp.i
.PHONY : prj/src/mime_types.cpp.i

prj/src/mime_types.s: prj/src/mime_types.cpp.s

.PHONY : prj/src/mime_types.s

# target to generate assembly for a file
prj/src/mime_types.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/mime_types.cpp.s
.PHONY : prj/src/mime_types.cpp.s

prj/src/reply.o: prj/src/reply.cpp.o

.PHONY : prj/src/reply.o

# target to build an object file
prj/src/reply.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/reply.cpp.o
.PHONY : prj/src/reply.cpp.o

prj/src/reply.i: prj/src/reply.cpp.i

.PHONY : prj/src/reply.i

# target to preprocess a source file
prj/src/reply.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/reply.cpp.i
.PHONY : prj/src/reply.cpp.i

prj/src/reply.s: prj/src/reply.cpp.s

.PHONY : prj/src/reply.s

# target to generate assembly for a file
prj/src/reply.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/reply.cpp.s
.PHONY : prj/src/reply.cpp.s

prj/src/request_handler.o: prj/src/request_handler.cpp.o

.PHONY : prj/src/request_handler.o

# target to build an object file
prj/src/request_handler.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/request_handler.cpp.o
.PHONY : prj/src/request_handler.cpp.o

prj/src/request_handler.i: prj/src/request_handler.cpp.i

.PHONY : prj/src/request_handler.i

# target to preprocess a source file
prj/src/request_handler.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/request_handler.cpp.i
.PHONY : prj/src/request_handler.cpp.i

prj/src/request_handler.s: prj/src/request_handler.cpp.s

.PHONY : prj/src/request_handler.s

# target to generate assembly for a file
prj/src/request_handler.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/request_handler.cpp.s
.PHONY : prj/src/request_handler.cpp.s

prj/src/request_parser.o: prj/src/request_parser.cpp.o

.PHONY : prj/src/request_parser.o

# target to build an object file
prj/src/request_parser.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/request_parser.cpp.o
.PHONY : prj/src/request_parser.cpp.o

prj/src/request_parser.i: prj/src/request_parser.cpp.i

.PHONY : prj/src/request_parser.i

# target to preprocess a source file
prj/src/request_parser.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/request_parser.cpp.i
.PHONY : prj/src/request_parser.cpp.i

prj/src/request_parser.s: prj/src/request_parser.cpp.s

.PHONY : prj/src/request_parser.s

# target to generate assembly for a file
prj/src/request_parser.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/request_parser.cpp.s
.PHONY : prj/src/request_parser.cpp.s

prj/src/server.o: prj/src/server.cpp.o

.PHONY : prj/src/server.o

# target to build an object file
prj/src/server.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/server.cpp.o
.PHONY : prj/src/server.cpp.o

prj/src/server.i: prj/src/server.cpp.i

.PHONY : prj/src/server.i

# target to preprocess a source file
prj/src/server.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/server.cpp.i
.PHONY : prj/src/server.cpp.i

prj/src/server.s: prj/src/server.cpp.s

.PHONY : prj/src/server.s

# target to generate assembly for a file
prj/src/server.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/prj/src/server.cpp.s
.PHONY : prj/src/server.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... server"
	@echo "... prj/src/connection.o"
	@echo "... prj/src/connection.i"
	@echo "... prj/src/connection.s"
	@echo "... prj/src/connection_manager.o"
	@echo "... prj/src/connection_manager.i"
	@echo "... prj/src/connection_manager.s"
	@echo "... prj/src/database.o"
	@echo "... prj/src/database.i"
	@echo "... prj/src/database.s"
	@echo "... prj/src/database_manager.o"
	@echo "... prj/src/database_manager.i"
	@echo "... prj/src/database_manager.s"
	@echo "... prj/src/main.o"
	@echo "... prj/src/main.i"
	@echo "... prj/src/main.s"
	@echo "... prj/src/mime_types.o"
	@echo "... prj/src/mime_types.i"
	@echo "... prj/src/mime_types.s"
	@echo "... prj/src/reply.o"
	@echo "... prj/src/reply.i"
	@echo "... prj/src/reply.s"
	@echo "... prj/src/request_handler.o"
	@echo "... prj/src/request_handler.i"
	@echo "... prj/src/request_handler.s"
	@echo "... prj/src/request_parser.o"
	@echo "... prj/src/request_parser.i"
	@echo "... prj/src/request_parser.s"
	@echo "... prj/src/server.o"
	@echo "... prj/src/server.i"
	@echo "... prj/src/server.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
