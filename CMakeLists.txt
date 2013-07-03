# Macro to print some message to stdout, useful for debugging purpose.
MACRO(DBG_MSG _MSG)
FOREACH(_MSG_STRING ${_MSG})
  MESSAGE(STATUS "${CMAKE_CURRENT_LIST_FILE}(${CMAKE_CURRENT_LIST_LINE}): ${_MSG_STRING}")
ENDFOREACH()
ENDMACRO(DBG_MSG)


#
# Build type
#
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their definition
# and dump it in the cache along with proper documentation, otherwise set CMAKE_BUILD_TYPE
# to Debug prior to calling PROJECT()
#
set(CMAKE_BUILD_TYPE_DOCUMENTATION "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release")
IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING ${CMAKE_BUILD_TYPE_DOCUMENTATION})
ELSE()
   SET(CMAKE_BUILD_TYPE Debug CACHE STRING ${CMAKE_BUILD_TYPE_DOCUMENTATION})
ENDIF()


# The name of our project is "test". CMakeLists files in this project can
# refer to the root source directory of the project as ${test_SOURCE_DIR} and
# to the root binary directory of the project as ${test_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (test)


# Additional cmake modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


# Compiler flags
#set(LINK_FLAGS "-g")
#set(CMAKE_CXX_FLAGS "-g")
set (CMAKE_CXX_FLAGS "")
set (CMAKE_CXX_WARNING_LEVEL 4)

set(OPENGL_SUPERBIBLE_50 0)

if (MSVC)
	add_definitions(-D_HAS_EXCEPTIONS=0)
	if (OPENGL_SUPERBIBLE_50)
		add_definitions(-DUSE_OPENGL_SUPERBIBLE=1)
	else()
		add_definitions(-DUSE_OPENGL_SUPERBIBLE=0)
	endif (OPENGL_SUPERBIBLE_50)
endif (MSVC)

if (CMAKE_COMPILER_IS_GNUCXX)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wunused -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute")
	#	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -pedantic-errors")
	if (OPENGL_SUPERBIBLE_50)
		add_definitions(-DUSE_OPENGL_SUPERBIBLE=1)
	else()
		add_definitions(-DUSE_OPENGL_SUPERBIBLE=0)
	endif (OPENGL_SUPERBIBLE_50)
endif (CMAKE_COMPILER_IS_GNUCXX)


# Packages
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.53.0 REQUIRED COMPONENTS filesystem)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
if (WIN32)
	set(GLUT_INCLUDE_DIR "D:/msysgit/local/include")
	set(GLUT_LIBRARY "D:/msysgit/local/lib/glut32.lib")
	# Can't seem to use find_package for GLFW or OpenAL on my Windows 7 box...
	#set(OPENAL_INCLUDE_DIR "D:/msysgit/local/include")
	#set(OPENAL_LIBRARY "D:/msysgit/local/lib/OpenAL32.lib")
	#set(FREETYPE_INCLUDE_DIRS "D:/msysgit/local/include;D:/msysgit/local/include/freetype2")
	#set(FREETYPE_LIBRARIES "D:/msysgit/local/lib/libfreetype.a")
	#set(GLFW_INCLUDE_DIR "D:/msysgit/local/include")
	#if (MSYS)
	#	set(GLFW_LIBRARY "D:/msysgit/local/lib/libglfw.a")
	#endif (MSYS)
	#if (MSVC)
	#	set(GLFW_LIBRARY "D:/msysgit/local/lib/glfw.lib")
	#endif (MSVC)
endif (WIN32)
if (UNIX)
	find_package(GLUT REQUIRED)
	#find_package(GLFW REQUIRED)
	#find_package(OpenAL REQUIRED)
	#find_package(Freetype REQUIRED)
endif (UNIX)


# Start OpenGL SuperBible 5.0 stuff
if (OPENGL_SUPERBIBLE_50)
	set(OPENGL_SUPERBIBLE_50_INCLUDES "${test_SOURCE_DIR}/GLTools/include" "${test_SOURCE_DIR}/GLTools/include/GL")
endif (OPENGL_SUPERBIBLE_50)
# End OpenGL SuperBible 5.0 stuff


# Platform include paths
set(PLATFORM_INCLUDES "${test_SOURCE_DIR}/engine/independent" "${test_SOURCE_DIR}/unit_tests")
if (WIN32)
	set(PLATFORM_INCLUDES ${PLATFORM_INCLUDES} "${test_SOURCE_DIR}/engine/windows")
endif (WIN32)
if (UNIX)
	set(PLATFORM_INCLUDES ${PLATFORM_INCLUDES} "${test_SOURCE_DIR}/engine/linux")
endif (UNIX)


# Set up include and library paths
include_directories(${PLATFORM_INCLUDES} ${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${OPENAL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${OPENGL_SUPERBIBLE_50_INCLUDES})
set(LIBS ${LIBS} ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${ZLIB_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARY} ${OPENAL_LIBRARY} ${FREETYPE_LIBRARIES})


#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#DBG_MSG("INCLUDE_DIRECTORIES = [${dirs}]")
#DBG_MSG("LIBS = [${LIBS}]")
#DBG_MSG("PLATFORM_INCLUDES = [${PLATFORM_INCLUDES}]")


# Platform sources
set(PLATFORM_INDEPENDENT_SOURCES
	#engine/independent/common/console.cpp
	#engine/independent/common/filesystem.cpp
	#engine/independent/common/glfw.cpp
	#engine/independent/common/log.cpp
	#engine/independent/common/profiling.cpp
	engine/independent/common/stdafx.cpp
	#engine/independent/common/system.cpp
	#engine/independent/graphics/debugfont.cpp
	#engine/independent/graphics/renderer.cpp
	#engine/independent/input/keyboard.cpp
	engine/independent/common/commandargs.cpp
	engine/independent/time/time.cpp
	engine/independent/time/timer.cpp
	engine/independent/time/timevalue.cpp
	unit_tests/unittest.cpp
	unit_tests/timetest.cpp
	unit_tests/typetest.cpp
	)
if (OPENGL_SUPERBIBLE_50)
	set(OPENGL_SUPERBIBLE_50_SOURCES
	# Start OpenGL SuperBible 5.0 stuff
	#GLTools/src/openglsuperbible_uber.cpp
	GLSB/examples.cpp
	# End OpenGL SuperBible 5.0 stuff
	)
endif (OPENGL_SUPERBIBLE_50)
if (WIN32)
set(PLATFORM_SPECIFIC_SOURCES
	#engine/windows/common/platform_system.cpp
	engine/windows/time/platform_time.cpp
	)
endif (WIN32)
if (UNIX)
set(PLATFORM_SPECIFIC_SOURCES
	#engine/linux/common/platform_system.cpp
	engine/linux/time/platform_time.cpp
	)
endif (UNIX)

# Build rules for the executable
add_executable (test main.cpp ${PLATFORM_INDEPENDENT_SOURCES} ${PLATFORM_SPECIFIC_SOURCES} ${OPENGL_SUPERBIBLE_50_SOURCES})
target_link_libraries (test ${LIBS})

