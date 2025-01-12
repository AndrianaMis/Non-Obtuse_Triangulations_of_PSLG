# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/erginadimitraina/Project_part3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erginadimitraina/Project_part3

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/erginadimitraina/Project_part3/CMakeFiles /home/erginadimitraina/Project_part3//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/erginadimitraina/Project_part3/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named CGAL_Qt5_moc_and_resources

# Build rule for target.
CGAL_Qt5_moc_and_resources: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 CGAL_Qt5_moc_and_resources
.PHONY : CGAL_Qt5_moc_and_resources

# fast build rule for target.
CGAL_Qt5_moc_and_resources/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build
.PHONY : CGAL_Qt5_moc_and_resources/fast

#=============================================================================
# Target rules for targets named example

# Build rule for target.
example: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 example
.PHONY : example

# fast build rule for target.
example/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/build
.PHONY : example/fast

#=============================================================================
# Target rules for targets named CGAL_Qt5_moc_and_resources_autogen

# Build rule for target.
CGAL_Qt5_moc_and_resources_autogen: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 CGAL_Qt5_moc_and_resources_autogen
.PHONY : CGAL_Qt5_moc_and_resources_autogen

# fast build rule for target.
CGAL_Qt5_moc_and_resources_autogen/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources_autogen.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources_autogen.dir/build
.PHONY : CGAL_Qt5_moc_and_resources_autogen/fast

CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.o: CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.o
.PHONY : CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.o

# target to build an object file
CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.o
.PHONY : CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.o

CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.i: CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.i
.PHONY : CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.i

# target to preprocess a source file
CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.i
.PHONY : CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.i

CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.s: CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.s
.PHONY : CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.s

# target to generate assembly for a file
CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.s
.PHONY : CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.cpp.s

ex.o: ex.cpp.o
.PHONY : ex.o

# target to build an object file
ex.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/ex.cpp.o
.PHONY : ex.cpp.o

ex.i: ex.cpp.i
.PHONY : ex.i

# target to preprocess a source file
ex.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/ex.cpp.i
.PHONY : ex.cpp.i

ex.s: ex.cpp.s
.PHONY : ex.s

# target to generate assembly for a file
ex.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/ex.cpp.s
.PHONY : ex.cpp.s

qrc_CGAL.o: qrc_CGAL.cpp.o
.PHONY : qrc_CGAL.o

# target to build an object file
qrc_CGAL.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_CGAL.cpp.o
.PHONY : qrc_CGAL.cpp.o

qrc_CGAL.i: qrc_CGAL.cpp.i
.PHONY : qrc_CGAL.i

# target to preprocess a source file
qrc_CGAL.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_CGAL.cpp.i
.PHONY : qrc_CGAL.cpp.i

qrc_CGAL.s: qrc_CGAL.cpp.s
.PHONY : qrc_CGAL.s

# target to generate assembly for a file
qrc_CGAL.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_CGAL.cpp.s
.PHONY : qrc_CGAL.cpp.s

qrc_File.o: qrc_File.cpp.o
.PHONY : qrc_File.o

# target to build an object file
qrc_File.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_File.cpp.o
.PHONY : qrc_File.cpp.o

qrc_File.i: qrc_File.cpp.i
.PHONY : qrc_File.i

# target to preprocess a source file
qrc_File.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_File.cpp.i
.PHONY : qrc_File.cpp.i

qrc_File.s: qrc_File.cpp.s
.PHONY : qrc_File.s

# target to generate assembly for a file
qrc_File.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_File.cpp.s
.PHONY : qrc_File.cpp.s

qrc_Input.o: qrc_Input.cpp.o
.PHONY : qrc_Input.o

# target to build an object file
qrc_Input.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_Input.cpp.o
.PHONY : qrc_Input.cpp.o

qrc_Input.i: qrc_Input.cpp.i
.PHONY : qrc_Input.i

# target to preprocess a source file
qrc_Input.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_Input.cpp.i
.PHONY : qrc_Input.cpp.i

qrc_Input.s: qrc_Input.cpp.s
.PHONY : qrc_Input.s

# target to generate assembly for a file
qrc_Input.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_Input.cpp.s
.PHONY : qrc_Input.cpp.s

qrc_Triangulation_2.o: qrc_Triangulation_2.cpp.o
.PHONY : qrc_Triangulation_2.o

# target to build an object file
qrc_Triangulation_2.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_Triangulation_2.cpp.o
.PHONY : qrc_Triangulation_2.cpp.o

qrc_Triangulation_2.i: qrc_Triangulation_2.cpp.i
.PHONY : qrc_Triangulation_2.i

# target to preprocess a source file
qrc_Triangulation_2.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_Triangulation_2.cpp.i
.PHONY : qrc_Triangulation_2.cpp.i

qrc_Triangulation_2.s: qrc_Triangulation_2.cpp.s
.PHONY : qrc_Triangulation_2.s

# target to generate assembly for a file
qrc_Triangulation_2.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/CGAL_Qt5_moc_and_resources.dir/build.make CMakeFiles/CGAL_Qt5_moc_and_resources.dir/qrc_Triangulation_2.cpp.s
.PHONY : qrc_Triangulation_2.cpp.s

utils/algorithms.o: utils/algorithms.cpp.o
.PHONY : utils/algorithms.o

# target to build an object file
utils/algorithms.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/algorithms.cpp.o
.PHONY : utils/algorithms.cpp.o

utils/algorithms.i: utils/algorithms.cpp.i
.PHONY : utils/algorithms.i

# target to preprocess a source file
utils/algorithms.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/algorithms.cpp.i
.PHONY : utils/algorithms.cpp.i

utils/algorithms.s: utils/algorithms.cpp.s
.PHONY : utils/algorithms.s

# target to generate assembly for a file
utils/algorithms.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/algorithms.cpp.s
.PHONY : utils/algorithms.cpp.s

utils/new.o: utils/new.cpp.o
.PHONY : utils/new.o

# target to build an object file
utils/new.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/new.cpp.o
.PHONY : utils/new.cpp.o

utils/new.i: utils/new.cpp.i
.PHONY : utils/new.i

# target to preprocess a source file
utils/new.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/new.cpp.i
.PHONY : utils/new.cpp.i

utils/new.s: utils/new.cpp.s
.PHONY : utils/new.s

# target to generate assembly for a file
utils/new.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/new.cpp.s
.PHONY : utils/new.cpp.s

utils/utils.o: utils/utils.cpp.o
.PHONY : utils/utils.o

# target to build an object file
utils/utils.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/utils.cpp.o
.PHONY : utils/utils.cpp.o

utils/utils.i: utils/utils.cpp.i
.PHONY : utils/utils.i

# target to preprocess a source file
utils/utils.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/utils.cpp.i
.PHONY : utils/utils.cpp.i

utils/utils.s: utils/utils.cpp.s
.PHONY : utils/utils.s

# target to generate assembly for a file
utils/utils.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/example.dir/build.make CMakeFiles/example.dir/utils/utils.cpp.s
.PHONY : utils/utils.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... CGAL_Qt5_moc_and_resources_autogen"
	@echo "... CGAL_Qt5_moc_and_resources"
	@echo "... example"
	@echo "... CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.o"
	@echo "... CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.i"
	@echo "... CGAL_Qt5_moc_and_resources_autogen/mocs_compilation.s"
	@echo "... ex.o"
	@echo "... ex.i"
	@echo "... ex.s"
	@echo "... qrc_CGAL.o"
	@echo "... qrc_CGAL.i"
	@echo "... qrc_CGAL.s"
	@echo "... qrc_File.o"
	@echo "... qrc_File.i"
	@echo "... qrc_File.s"
	@echo "... qrc_Input.o"
	@echo "... qrc_Input.i"
	@echo "... qrc_Input.s"
	@echo "... qrc_Triangulation_2.o"
	@echo "... qrc_Triangulation_2.i"
	@echo "... qrc_Triangulation_2.s"
	@echo "... utils/algorithms.o"
	@echo "... utils/algorithms.i"
	@echo "... utils/algorithms.s"
	@echo "... utils/new.o"
	@echo "... utils/new.i"
	@echo "... utils/new.s"
	@echo "... utils/utils.o"
	@echo "... utils/utils.i"
	@echo "... utils/utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

