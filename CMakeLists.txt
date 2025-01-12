# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.1...3.23)

project( example )



find_package(CGAL REQUIRED COMPONENTS Qt5 Core)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

 
# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )


if ( NOT CGAL_FOUND )

  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()  

endif()


# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )

  message(STATUS "This project requires the Boost library, and will not be compiled.")

  return()  

endif()

# include for local directory

# include for local package


# Creating entries for target: example
# ############################
include_directories(utils)
set(SOURCES
    ex.cpp
    utils/utils.cpp
    utils/algorithms.cpp
    utils/new.cpp
    )
add_executable( example  ${SOURCES} )

add_to_cached_list( CGAL_EXECUTABLE_TARGETS example )

find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_library(GMP_LIB NAMES gmp PATHS /usr/lib/x86_64-linux-gnu)
find_library(GMPXX_LIB NAMES gmpxx PATHS /usr/lib/x86_64-linux-gnu)
find_library(MPFR_LIB NAMES mpfr PATHS /usr/lib/x86_64-linux-gnu)

if (GMP_LIB AND GMPXX_LIB AND MPFR_LIB)
    message(STATUS "Found GMP: ${GMP_LIB}")
    message(STATUS "Found GMPXX: ${GMPXX_LIB}")
    message(STATUS "Found MPFR: ${MPFR_LIB}")
else()
    message(FATAL_ERROR "GMP or MPFR libraries not found")
endif()

target_link_libraries(example PRIVATE ${GMP_LIB} ${GMPXX_LIB} ${MPFR_LIB})
# Link the executable to CGAL and third-party libraries
target_link_libraries(example PRIVATE CGAL::CGAL )

if((CGAL_Qt5_FOUND))
  message(STATUS "Found Qt5")
  add_definitions(-DCGAL_USE_BASIC_VIEWER)  #ENABLE VIEWER FUNCTIONALITY
  target_link_libraries(example PRIVATE CGAL::CGAL_Qt5  Qt5::Widgets )
else()
  message(FATAL_ERROR "CGAL Qt5 package not found!")
endif()