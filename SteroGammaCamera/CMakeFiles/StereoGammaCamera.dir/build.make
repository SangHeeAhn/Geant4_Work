# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/g4user/Geant4_Work/SteroGammaCamera

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/g4user/Geant4_Work/SteroGammaCamera

# Include any dependencies generated for this target.
include CMakeFiles/StereoGammaCamera.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/StereoGammaCamera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StereoGammaCamera.dir/flags.make

CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o: StereoGammaCamera.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/StereoGammaCamera.cc

CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/StereoGammaCamera.cc > CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.i

CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/StereoGammaCamera.cc -o CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.s

CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o


CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o: src/LXeGeneralPhysics.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeGeneralPhysics.cc

CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeGeneralPhysics.cc > CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.i

CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeGeneralPhysics.cc -o CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.s

CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o


CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o: src/LXeMuonPhysics.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeMuonPhysics.cc

CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeMuonPhysics.cc > CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.i

CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeMuonPhysics.cc -o CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.s

CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o


CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o: src/PhysicsList.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/PhysicsList.cc

CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/PhysicsList.cc > CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.i

CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/PhysicsList.cc -o CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.s

CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o


CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o: src/RunAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/RunAction.cc

CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/RunAction.cc > CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.i

CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/RunAction.cc -o CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.s

CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o


CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o: src/PolygonDataImport.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/PolygonDataImport.cc

CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/PolygonDataImport.cc > CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.i

CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/PolygonDataImport.cc -o CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.s

CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o


CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o: src/DetectorConstruction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/DetectorConstruction.cc

CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/DetectorConstruction.cc > CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.i

CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/DetectorConstruction.cc -o CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.s

CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o


CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o: src/LXePhysicsList.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/LXePhysicsList.cc

CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/LXePhysicsList.cc > CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.i

CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/LXePhysicsList.cc -o CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.s

CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o


CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o: src/LXeEMPhysics.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeEMPhysics.cc

CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeEMPhysics.cc > CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.i

CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/LXeEMPhysics.cc -o CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.s

CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o


CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o: src/PrimaryGeneratorAction.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/PrimaryGeneratorAction.cc

CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/PrimaryGeneratorAction.cc > CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.i

CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/PrimaryGeneratorAction.cc -o CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.s

CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o


CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o: src/SensitiveDetector.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/SensitiveDetector.cc

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/SensitiveDetector.cc > CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.i

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/SensitiveDetector.cc -o CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.s

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o


CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o: src/SensitiveDetectorOnScint.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/SensitiveDetectorOnScint.cc

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/SensitiveDetectorOnScint.cc > CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.i

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/SensitiveDetectorOnScint.cc -o CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.s

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o


CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o: CMakeFiles/StereoGammaCamera.dir/flags.make
CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o: src/ActionInitialization.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o -c /home/g4user/Geant4_Work/SteroGammaCamera/src/ActionInitialization.cc

CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/g4user/Geant4_Work/SteroGammaCamera/src/ActionInitialization.cc > CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.i

CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/g4user/Geant4_Work/SteroGammaCamera/src/ActionInitialization.cc -o CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.s

CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o.requires:

.PHONY : CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o.requires

CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o.provides: CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o.requires
	$(MAKE) -f CMakeFiles/StereoGammaCamera.dir/build.make CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o.provides.build
.PHONY : CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o.provides

CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o.provides.build: CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o


# Object files for target StereoGammaCamera
StereoGammaCamera_OBJECTS = \
"CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o" \
"CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o"

# External object files for target StereoGammaCamera
StereoGammaCamera_EXTERNAL_OBJECTS =

StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/build.make
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4Tree.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4GMocren.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4visHepRep.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4RayTracer.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4VRML.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4OpenGL.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4gl2ps.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4interfaces.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4persistency.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4analysis.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4error_propagation.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4readout.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4physicslists.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4parmodels.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4FR.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4vis_management.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4modeling.so
StereoGammaCamera: /usr/lib64/libSM.so
StereoGammaCamera: /usr/lib64/libICE.so
StereoGammaCamera: /usr/lib64/libX11.so
StereoGammaCamera: /usr/lib64/libXext.so
StereoGammaCamera: /usr/lib64/libGLU.so
StereoGammaCamera: /usr/lib64/libGL.so
StereoGammaCamera: /usr/lib64/libXmu.so
StereoGammaCamera: /usr/lib64/libQtOpenGL.so
StereoGammaCamera: /usr/lib64/libQtGui.so
StereoGammaCamera: /usr/lib64/libQtGui_debug.so
StereoGammaCamera: /usr/lib64/libQtCore.so
StereoGammaCamera: /usr/lib64/libQtCore_debug.so
StereoGammaCamera: /usr/lib64/libxerces-c.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4run.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4event.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4tracking.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4processes.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4zlib.so
StereoGammaCamera: /usr/lib64/libexpat.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4digits_hits.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4track.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4particles.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4geometry.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4materials.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4graphics_reps.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4intercoms.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4global.so
StereoGammaCamera: /opt/geant4/10.2.0/lib64/libG4clhep.so
StereoGammaCamera: CMakeFiles/StereoGammaCamera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable StereoGammaCamera"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StereoGammaCamera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StereoGammaCamera.dir/build: StereoGammaCamera

.PHONY : CMakeFiles/StereoGammaCamera.dir/build

CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/StereoGammaCamera.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/LXeGeneralPhysics.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/LXeMuonPhysics.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/PhysicsList.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/RunAction.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/PolygonDataImport.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/DetectorConstruction.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/LXePhysicsList.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/LXeEMPhysics.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/PrimaryGeneratorAction.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetector.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/SensitiveDetectorOnScint.cc.o.requires
CMakeFiles/StereoGammaCamera.dir/requires: CMakeFiles/StereoGammaCamera.dir/src/ActionInitialization.cc.o.requires

.PHONY : CMakeFiles/StereoGammaCamera.dir/requires

CMakeFiles/StereoGammaCamera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StereoGammaCamera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StereoGammaCamera.dir/clean

CMakeFiles/StereoGammaCamera.dir/depend:
	cd /home/g4user/Geant4_Work/SteroGammaCamera && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/g4user/Geant4_Work/SteroGammaCamera /home/g4user/Geant4_Work/SteroGammaCamera /home/g4user/Geant4_Work/SteroGammaCamera /home/g4user/Geant4_Work/SteroGammaCamera /home/g4user/Geant4_Work/SteroGammaCamera/CMakeFiles/StereoGammaCamera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StereoGammaCamera.dir/depend

