###############################################################################
#
# Macro to print some message to stdout, useful for debugging purposes.
#
MACRO(DBG_MSG _MSG)
FOREACH(_MSG_STRING ${_MSG})
  MESSAGE(STATUS "${CMAKE_CURRENT_LIST_FILE}(${CMAKE_CURRENT_LIST_LINE}): ${_MSG_STRING}")
ENDFOREACH()
ENDMACRO(DBG_MSG)
#
###############################################################################


###############################################################################
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
#
###############################################################################


###############################################################################
#
# The name of our project is "test". CMakeLists files in this project can
# refer to the root source directory of the project as ${test_SOURCE_DIR} and
# to the root binary directory of the project as ${test_BINARY_DIR}.
#
cmake_minimum_required (VERSION 2.6)
project (test)
# Additional cmake modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#
###############################################################################


###############################################################################
#
# Compiler flags
#
set(SUPPORT_EXCEPTIONS 1)
set(OPENGL_SUPERBIBLE_50 0)

# Generic settings
#set(LINK_FLAGS "-g")
#set(CMAKE_CXX_FLAGS "-g")
set (CMAKE_CXX_FLAGS "")
set (CMAKE_CXX_WARNING_LEVEL 4)
if (OPENGL_SUPERBIBLE_50)
	add_definitions(-DUSE_OPENGL_SUPERBIBLE=1)
else()
	add_definitions(-DUSE_OPENGL_SUPERBIBLE=0)
endif (OPENGL_SUPERBIBLE_50)

# MSVC specific
if (MSVC)
	if (SUPPORT_EXCEPTIONS)
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	endif (SUPPORT_EXCEPTIONS)
endif (MSVC)

# GNU specific
if (CMAKE_COMPILER_IS_GNUCXX)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
	if (NOT SUPPORT_EXCEPTIONS)
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
	endif (NOT SUPPORT_EXCEPTIONS)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute")
	if (UNIX)
		# Boost libraries under Windows throw a lot of shadow errors, but not under Linux
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
	endif (UNIX)
	#	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -pedantic-errors")
endif (CMAKE_COMPILER_IS_GNUCXX)
#
###############################################################################


###############################################################################
#
# Packages
#
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
if (CMAKE_COMPILER_IS_GNUCXX)
find_package(Boost 1.55.0 REQUIRED COMPONENTS filesystem system thread)
else()
find_package(Boost 1.55.0 REQUIRED COMPONENTS chrono date_time filesystem system thread)
endif (CMAKE_COMPILER_IS_GNUCXX)
if (Boost_FOUND)
	if (NOT SUPPORT_EXCEPTIONS)
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_NO_EXCEPTIONS")
	endif (NOT SUPPORT_EXCEPTIONS)
endif (Boost_FOUND)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
if (WIN32)
	set(GLUT_INCLUDE_DIR "D:/MyCode/SDKs/glut/include")
	set(GLUT_LIBRARY "D:/MyCode/SDKs/glut/lib/glut32.lib")
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
#
###############################################################################


###############################################################################
#
# Start OpenGL SuperBible 5.0 stuff
#
if (OPENGL_SUPERBIBLE_50)
	set(OPENGL_SUPERBIBLE_50_INCLUDES "${test_SOURCE_DIR}/GLTools/include" "${test_SOURCE_DIR}/GLTools/include/GL")
endif (OPENGL_SUPERBIBLE_50)
#
# End OpenGL SuperBible 5.0 stuff
#
###############################################################################


###############################################################################
#
# Platform include paths
#
set(PLATFORM_INCLUDES "${test_SOURCE_DIR}/engine/independent" "${test_SOURCE_DIR}/unit_tests")
file(GLOB_RECURSE PLATFORM_INDEPENDENT_HEADERS
 	"${test_SOURCE_DIR}/engine/independent/*.h"
 	"${test_SOURCE_DIR}/engine/independent/*.inl"
	)
if (WIN32)
	set(PLATFORM_INCLUDES ${PLATFORM_INCLUDES} "${test_SOURCE_DIR}/engine/windows")
	file(GLOB_RECURSE PLATFORM_SPECIFIC_HEADERS "${test_SOURCE_DIR}/engine/windows/*.h" "${test_SOURCE_DIR}/engine/windows/*.inl")
endif (WIN32)
if (UNIX)
	set(PLATFORM_INCLUDES ${PLATFORM_INCLUDES} "${test_SOURCE_DIR}/engine/linux")
	file(GLOB_RECURSE PLATFORM_SPECIFIC_HEADERS "${test_SOURCE_DIR}/engine/linux/*.h" "${test_SOURCE_DIR}/engine/linux/*.inl")
endif (UNIX)
#
# Set up include and library paths
#
include_directories(${PLATFORM_INCLUDES} ${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${OPENAL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${OPENGL_SUPERBIBLE_50_INCLUDES})
set(LIBS ${LIBS} ${Boost_LIBRARIES} ${OPENGL_LIBRARY} ${ZLIB_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARY} ${OPENAL_LIBRARY} ${FREETYPE_LIBRARIES})
#
###############################################################################


###############################################################################
#
# Debug messages to print out the current include/source/libs paths
#
#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#DBG_MSG("INCLUDE_DIRECTORIES = [${dirs}]")
#DBG_MSG("LIBS = [${LIBS}]")
#DBG_MSG("PLATFORM_INCLUDES = [${PLATFORM_INCLUDES}]")
#
###############################################################################


###############################################################################
#
# Platform sources
#
set(PLATFORM_INDEPENDENT_SOURCES
	#engine/independent/common/filesystem.cpp
	#engine/independent/common/glfw.cpp
	#engine/independent/common/log.cpp
	#engine/independent/common/profiling.cpp
	#engine/independent/common/system.cpp
	#engine/independent/graphics/debugfont.cpp
	#engine/independent/graphics/renderer.cpp
	#engine/independent/input/keyboard.cpp
	engine/independent/common/stdafx.cpp
	engine/independent/system/commandline.cpp
	engine/independent/system/console.cpp
	engine/independent/system/log.cpp
	engine/independent/time/time.cpp
	engine/independent/time/timer.cpp
	engine/independent/time/timevalue.cpp
	engine/independent/utility/debug.cpp
	)
source_group(Independent FILES ${PLATFORM_INDEPENDENT_SOURCES} ${PLATFORM_INDEPENDENT_HEADERS})
#
if (WIN32)
	set(PLATFORM_SPECIFIC_SOURCES
		#engine/windows/common/platform_system.cpp
		engine/windows/time/platform_time.cpp
		)
	source_group(Win32 FILES ${PLATFORM_SPECIFIC_SOURCES} ${PLATFORM_SPECIFIC_HEADERS})
endif (WIN32)
#
if (UNIX)
	set(PLATFORM_SPECIFIC_SOURCES
		#engine/linux/common/platform_system.cpp
		engine/linux/time/platform_time.cpp
		)
	source_group(Linux FILES ${PLATFORM_SPECIFIC_SOURCES} ${PLATFORM_SPECIFIC_HEADERS})
endif (UNIX)
#
set(UNIT_TEST_SOURCES
	unit_tests/unittest.cpp
	unit_tests/cvartest.cpp
	unit_tests/logtest.cpp
	unit_tests/timetest.cpp
	unit_tests/typetest.cpp
	)
file(GLOB_RECURSE UNIT_TEST_HEADERS "${test_SOURCE_DIR}/unit_tests/*.h" "${test_SOURCE_DIR}/unit_tests/*.inl")
source_group(UnitTests FILES ${UNIT_TEST_SOURCES} ${UNIT_TEST_HEADERS})
#
if (OPENGL_SUPERBIBLE_50)
	set(OPENGL_SUPERBIBLE_50_SOURCES
		# Start OpenGL SuperBible 5.0 stuff
		#GLTools/src/openglsuperbible_uber.cpp
		GLSB/examples.cpp
		# End OpenGL SuperBible 5.0 stuff
		)
endif (OPENGL_SUPERBIBLE_50)
#
###############################################################################


###############################################################################
#
# Build the 'generate_version' executable
#
add_executable (
	generate_version
 	tools/build/generate_version/main.cpp
 	engine/independent/common/stdafx.cpp
	)
target_link_libraries (generate_version ${Boost_LIBRARIES})
#
get_target_property(GENERATE_VERSION_EXE generate_version LOCATION)
add_custom_command(
	OUTPUT "${test_SOURCE_DIR}/engine/independent/common/version.cpp"
	COMMAND "${GENERATE_VERSION_EXE}" --template-file "${test_SOURCE_DIR}/engine/independent/common/version.cpp.in" --build-number-file "${test_SOURCE_DIR}/engine/independent/common/build_number" --output-file "${test_SOURCE_DIR}/engine/independent/common/version.cpp"
	DEPENDS "${GENERATE_VERSION_EXE}" "${test_SOURCE_DIR}/engine/independent/common/version.cpp.in" ${PLATFORM_INDEPENDENT_SOURCES} ${PLATFORM_SPECIFIC_SOURCES}
	)
#
###############################################################################


###############################################################################
#
# Build the 'unit_test' executable
#
add_executable (
	unit_test
 	unit_tests/main.cpp
	engine/independent/common/version.cpp
 	${PLATFORM_INDEPENDENT_SOURCES}
	${PLATFORM_INDEPENDENT_HEADERS}
 	${PLATFORM_SPECIFIC_SOURCES}
	${PLATFORM_SPECIFIC_HEADERS}
	${UNIT_TEST_SOURCES}
	${UNIT_TEST_HEADERS}
	)
target_link_libraries (unit_test ${LIBS})

get_target_property(UNIT_TEST_EXE unit_test LOCATION)
add_custom_command(
	OUTPUT "${test_SOURCE_DIR}/unit_test_results.txt"
	COMMAND "${UNIT_TEST_EXE}" > "${test_SOURCE_DIR}/unit_test_results.txt"
	DEPENDS "${UNIT_TEST_EXE}" ${PLATFORM_INDEPENDENT_SOURCES} ${PLATFORM_SPECIFIC_SOURCES} ${UNIT_TEST_SOURCES}
	)
#
###############################################################################


###############################################################################
#
# Build rules for the executable
#
add_executable (
	test
 	main.cpp
	engine/independent/common/version.cpp
	unit_test_results.txt
 	${PLATFORM_INDEPENDENT_SOURCES}
	${PLATFORM_INDEPENDENT_HEADERS}
 	${PLATFORM_SPECIFIC_SOURCES}
	${PLATFORM_SPECIFIC_HEADERS}
 	${OPENGL_SUPERBIBLE_50_SOURCES}
	)
target_link_libraries (test ${LIBS})
add_dependencies(test unit_test)
#
###############################################################################

