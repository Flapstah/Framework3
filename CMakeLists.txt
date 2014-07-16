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
# The name of our project is "game". CMakeLists files in this project can
# refer to the root source directory of the project as ${game_SOURCE_DIR} and
# to the root binary directory of the project as ${game_BINARY_DIR}.
#
cmake_minimum_required(VERSION 2.8)
project(game)
include("cmake/flapstah.cmake")

# Additional cmake modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(GLUT_ROOT_PATH "D:/MyCode/SDKs/freeglut-2.8.1")
set(GLEW_ROOT_PATH "D:/MyCode/SDKs/glew")
#
###############################################################################


###############################################################################
#
# Compiler flags
#
set(SUPPORT_EXCEPTIONS 1)

# Generic settings
#set(LINK_FLAGS "-g")
#set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_WARNING_LEVEL 4)

# MSVC specific
if(MSVC)
	if(SUPPORT_EXCEPTIONS)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	endif(SUPPORT_EXCEPTIONS)
endif(MSVC)

# GNU specific
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
	if(NOT SUPPORT_EXCEPTIONS)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
	endif(NOT SUPPORT_EXCEPTIONS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute")
	if(UNIX)
		# Boost libraries under Windows throw a lot of shadow errors, but not under Linux
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
	endif(UNIX)
	#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -pedantic-errors")
endif(CMAKE_COMPILER_IS_GNUCXX)
#
###############################################################################


###############################################################################
#
# Additional CMAKE repos
#

# GLFW includes OpenGL
add_subdirectory(${game_SOURCE_DIR}/SDKs/glfw)
set(GLFW_INCLUDE_DIRS "${game_SOURCE_DIR}/SDKs/glfw/include")
#
###############################################################################


###############################################################################
#
# Packages
#
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
if(CMAKE_COMPILER_IS_GNUCXX)
find_package(Boost 1.55.0 REQUIRED COMPONENTS filesystem system thread)
else()
find_package(Boost 1.55.0 REQUIRED COMPONENTS chrono date_time filesystem system thread)
endif(CMAKE_COMPILER_IS_GNUCXX)
if(Boost_FOUND)
	if(NOT SUPPORT_EXCEPTIONS)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_NO_EXCEPTIONS")
	endif(NOT SUPPORT_EXCEPTIONS)
endif(Boost_FOUND)
find_package(OpenGL)
#find_package(altGLEW REQUIRED)
#find_package(freeGLUT REQUIRED)
find_package(ZLIB REQUIRED)
if(WIN32)
	#set(OPENAL_INCLUDE_DIR "D:/msysgit/local/include")
	#set(OPENAL_LIBRARY "D:/msysgit/local/lib/OpenAL32.lib")
	#set(FREETYPE_INCLUDE_DIRS "D:/msysgit/local/include;D:/msysgit/local/include/freetype2")
	#set(FREETYPE_LIBRARIES "D:/msysgit/local/lib/libfreetype.a")
endif(WIN32)
if(UNIX)
	find_package(X11 REQUIRED)
	set (X11_LIBRARIES "${X11_LIBRARIES};${X11_Xxf86vm_LIB};${X11_Xrandr_LIB};${X11_Xi_LIB};${X11_Xcursor_LIB}")
	#find_package(GLUT REQUIRED)
	#find_package(OpenAL REQUIRED)
	#find_package(Freetype REQUIRED)
endif(UNIX)
#
###############################################################################


###############################################################################
#
# Engine platform independent:
#
FILE_LIST_RECURSE(ENGINE_PLATFORM_INDEPENDENT_BASE "engine/independent/base")
FILE_LIST_RECURSE(ENGINE_PLATFORM_INDEPENDENT_COMMON "engine/independent/common")
list(REMOVE_ITEM ENGINE_PLATFORM_INDEPENDENT_COMMON_SOURCES "${game_SOURCE_DIR}/engine/independent/common/version.cpp")
FILE_LIST_RECURSE(ENGINE_PLATFORM_INDEPENDENT_SYSTEM "engine/independent/system")
FILE_LIST_RECURSE(ENGINE_PLATFORM_INDEPENDENT_TIME "engine/independent/time")
FILE_LIST_RECURSE(ENGINE_PLATFORM_INDEPENDENT_UTILITY "engine/independent/utility")
FILE_LIST_RECURSE(ENGINE_PLATFORM_INDEPENDENT_VIDEO "engine/independent/video")
#
# Engine Windows specific:
#
FILE_LIST_RECURSE(ENGINE_WINDOWS_COMMON "engine/windows/common")
FILE_LIST_RECURSE(ENGINE_WINDOWS_TIME "engine/windows/time")
#
# Engine Linux specific:
#
FILE_LIST_RECURSE(ENGINE_LINUX_COMMON "engine/linux/common")
FILE_LIST_RECURSE(ENGINE_LINUX_TIME "engine/linux/time")
#
###############################################################################


###############################################################################
#
# Unit test (all files)
#
FILE_LIST_RECURSE(UNIT_TEST "engine/unit_test")
#
# Unit test (just the control files)
#
FILE_LIST_NO_RECURSE(UNIT_TEST_CONTROL "engine/unit_test")
#
# Unit test (just the test files)
#
FILE_LIST_RECURSE(UNIT_TEST_TESTS "engine/unit_test/tests")
###############################################################################


###############################################################################
#
# Create a cross-platform group for the platform specific files
#
set(ENGINE_PLATFORM_INDEPENDENT_HEADERS
	${ENGINE_PLATFORM_INDEPENDENT_COMMON_HEADERS}
	${ENGINE_PLATFORM_INDEPENDENT_BASE_HEADERS}
	${ENGINE_PLATFORM_INDEPENDENT_SYSTEM_HEADERS}
	${ENGINE_PLATFORM_INDEPENDENT_TIME_HEADERS}
	${ENGINE_PLATFORM_INDEPENDENT_UTILITY_HEADERS}
	${ENGINE_PLATFORM_INDEPENDENT_VIDEO_HEADERS}
	)
set(ENGINE_PLATFORM_INDEPENDENT_SOURCES
	${ENGINE_PLATFORM_INDEPENDENT_BASE_SOURCES}
	${ENGINE_PLATFORM_INDEPENDENT_COMMON_SOURCES}
	${ENGINE_PLATFORM_INDEPENDENT_SYSTEM_SOURCES}
	${ENGINE_PLATFORM_INDEPENDENT_TIME_SOURCES}
	${ENGINE_PLATFORM_INDEPENDENT_UTILITY_SOURCES}
	${ENGINE_PLATFORM_INDEPENDENT_VIDEO_SOURCES}
	)
if(WIN32)
	set(ENGINE_PLATFORM_DEPENDENT_HEADERS
		${ENGINE_WINDOWS_COMMON_HEADERS}
		${ENGINE_WINDOWS_TIME_HEADERS}
		)
	set(ENGINE_PLATFORM_DEPENDENT_SOURCES
		${ENGINE_WINDOWS_COMMON_SOURCES}
		${ENGINE_WINDOWS_TIME_SOURCES}
		)
	set(ENGINE_PLATFORM_DEPENDENT_COMMON ${ENGINE_WINDOWS_COMMON_HEADERS} ${ENGINE_WINDOWS_COMMON_SOURCES})
	set(ENGINE_PLATFORM_DEPENDENT_TIME ${ENGINE_WINDOWS_TIME_HEADERS} ${ENGINE_WINDOWS_TIME_SOURCES})
endif(WIN32)
if(UNIX)
	set(ENGINE_PLATFORM_DEPENDENT_SOURCES
		${ENGINE_LINUX_COMMON_HEADERS}
		${ENGINE_LINUX_TIME_HEADERS}
		)
	set(ENGINE_PLATFORM_DEPENDENT_SOURCES
		${ENGINE_LINUX_COMMON_SOURCES}
		${ENGINE_LINUX_TIME_SOURCES}
		)
	set(ENGINE_PLATFORM_DEPENDENT_COMMON ${ENGINE_LINUX_COMMON_HEADERS} ${ENGINE_LINUX_COMMON_SOURCES})
	set(ENGINE_PLATFORM_DEPENDENT_TIME ${ENGINE_LINUX_TIME_HEADERS} ${ENGINE_LINUX_TIME_SOURCES})
endif(UNIX)
#
###############################################################################


###############################################################################
#
# Collect all the sources and headers into groups
#
# Common
#
set(ENGINE_BASE_SOURCES
	${ENGINE_PLATFORM_INDEPENDENT_BASE}
	${ENGINE_PLATFORM_DEPENDENT_BASE}
	)
set(ENGINE_COMMON_SOURCES
	${ENGINE_PLATFORM_INDEPENDENT_COMMON}
	${ENGINE_PLATFORM_DEPENDENT_COMMON}
	)
set(ENGINE_SYSTEM_SOURCES
	${ENGINE_PLATFORM_INDEPENDENT_SYSTEM}
	${ENGINE_PLATFORM_DEPENDENT_SYSTEM}
	)
set(ENGINE_TIME_SOURCES
	${ENGINE_PLATFORM_INDEPENDENT_TIME}
	${ENGINE_PLATFORM_DEPENDENT_TIME}
	)
set(ENGINE_UTILITY_SOURCES
	${ENGINE_PLATFORM_INDEPENDENT_UTILITY}
	${ENGINE_PLATFORM_DEPENDENT_UTILITY}
	)
set(ENGINE_VIDEO_SOURCES
	${ENGINE_PLATFORM_INDEPENDENT_VIDEO}
	${ENGINE_PLATFORM_DEPENDENT_VIDEO}
	)
#
# Debug builds will build static libraries for all engine components to improve
# iteration speed.
# Release builds will build a monolithic executable from all the individual
# source files to get the best compiler optimisations across the executable
#
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_definitions(-DDEBUG)
	add_library(EngineBase STATIC ${ENGINE_BASE_SOURCES})
	add_library(EngineCommon STATIC ${ENGINE_COMMON_SOURCES})
	add_library(EngineSystem STATIC ${ENGINE_SYSTEM_SOURCES})
	add_library(EngineTime STATIC ${ENGINE_TIME_SOURCES})
	add_library(EngineUtility STATIC ${ENGINE_UTILITY_SOURCES})
	add_library(EngineVideo STATIC ${ENGINE_VIDEO_SOURCES})
	target_link_libraries(EngineVideo glfw ${OPENGL_LIBRARIES} ${X11_LIBRARIES})
	set(LIBS ${LIBS} 
		EngineBase
		EngineCommon
		EngineSystem
		EngineTime
		EngineUtility
		EngineVideo
		)
else()
	add_definitions(-DRELEASE)
	add_library(Engine STATIC ${ENGINE_BASE_SOURCES} ${ENGINE_COMMON_SOURCES} ${ENGINE_SYSTEM_SOURCES} ${ENGINE_TIME_SOURCES} ${ENGINE_UTILITY_SOURCES} ${ENGINE_VIDEO_SOURCES})
	target_link_libraries(Engine glfw ${OPENGL_LIBRARIES} ${X11_LIBRARIES})
	set(LIBS ${LIBS} 
			Engine
			)
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

set(ENGINE_HEADERS
	${ENGINE_PLATFORM_INDEPENDENT_HEADERS}
	${ENGINE_PLATFORM_DEPENDENT_HEADERS}
	)
set(ENGINE_SOURCES
	${ENGINE_PLATFORM_INDEPENDENT_SOURCES}
	${ENGINE_PLATFORM_DEPENDENT_SOURCES}
	)
#
###############################################################################


###############################################################################
#
# Source groups for IDE projects
#
source_group(Engine\\Independent\\Base FILES ${ENGINE_INDEPENDENT_BASE_HEADERS} ${ENGINE_INDEPENDENT_BASE_SOURCES})
source_group(Engine\\Independent\\Common FILES ${ENGINE_INDEPENDENT_COMMON_HEADERS} ${ENGINE_INDEPENDENT_COMMON_SOURCES})
source_group(Engine\\Independent\\System FILES ${ENGINE_INDEPENDENT_SYSTEM_HEADERS} ${ENGINE_INDEPENDENT_SYSTEM_SOURCES})
source_group(Engine\\Independent\\Time FILES ${ENGINE_INDEPENDENT_TIME_HEADERS} ${ENGINE_INDEPENDENT_TIME_SOURCES})
source_group(Engine\\Independent\\Utility FILES ${ENGINE_INDEPENDENT_UTILITY_HEADERS} ${ENGINE_INDEPENDENT_UTILITY_SOURCES})
source_group(Engine\\Independent\\Video FILES ${ENGINE_INDEPENDENT_VIDEO_HEADERS} ${ENGINE_INDEPENDENT_VIDEO_SOURCES})
source_group(Engine\\Windows\\Common FILES ${ENGINE_WINDOWS_COMMON_HEADERS} ${ENGINE_WINDOWS_COMMON_SOURCES})
source_group(Engine\\Windows\\Time FILES ${ENGINE_WINDOWS_TIME_HEADERS} ${ENGINE_WINDOWS_TIME_SOURCES})
source_group(Engine\\Linux\\Common FILES ${ENGINE_LINUX_COMMON_HEADERS} ${ENGINE_LINUX_COMMON_SOURCES})
source_group(Engine\\Linux\\Time FILES ${ENGINE_LINUX_TIME_HEADERS} ${ENGINE_LINUX_TIME_SOURCES})
source_group(UnitTests FILES ${UNIT_TEST_CONTROL_SOURCES} ${UNIT_TEST_CONTROL_HEADERS})
source_group(UnitTests\\Tests FILES ${UNIT_TEST_TESTS_SOURCES} ${UNIT_TEST_TESTS_HEADERS})
#
###############################################################################


###############################################################################
#
# Platform include paths
#
set(PROJECT_INDEPENDENT_INCLUDE_DIRS
	"${game_SOURCE_DIR}/engine/independent"
	"${game_SOURCE_DIR}/engine/tools"
	"${game_SOURCE_DIR}/engine/unit_test"
	)
if(WIN32)
	set(PROJECT_DEPENDENT_INCLUDE_DIRS
	"${game_SOURCE_DIR}/engine/windows")
endif(WIN32)
if(UNIX)
	set(PROJECT_DEPENDENT_INCLUDE_DIRS
	"${game_SOURCE_DIR}/engine/linux")
endif(UNIX)
#
# Set up include and library paths
#
# N.B. The Boost include directories are treated as system includes because
# there are compiler warnings issued under Windows release builds with gcc.
# I don't think there's anything I can do about them since it's code I don't
# own or maintain, and treating as a system include supresses the warnings.
#
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_INDEPENDENT_INCLUDE_DIRS} ${PROJECT_DEPENDENT_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS} ${OPENAL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES} ${ZLIB_LIBRARIES} ${GLEW_LIBRARY} ${GLUT_LIBRARY} ${OPENAL_LIBRARY} ${FREETYPE_LIBRARIES})
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
# Build the 'generate_version' executable
#
add_executable(
	generate-version
 	engine/tools/generate_version/main.cpp
 	engine/independent/common/stdafx.cpp
	)
target_link_libraries(generate-version ${Boost_LIBRARIES})
#
add_custom_command(
	OUTPUT "${game_SOURCE_DIR}/engine/independent/common/version.cpp"
	COMMAND generate-version --template-file "${game_SOURCE_DIR}/engine/independent/common/version.cpp.in" --build-number-file "${game_SOURCE_DIR}/engine/independent/common/build_number" --output-file "${game_SOURCE_DIR}/engine/independent/common/version.cpp"
	DEPENDS generate-version "${game_SOURCE_DIR}/engine/independent/common/version.cpp.in" ${ENGINE_HEADERS} ${ENGINE_SOURCES}
	)
#
###############################################################################


###############################################################################
#
# Build the 'unit-test' executable
#
add_executable(
	unit-test
 	engine/unit_test/main.cpp
	engine/independent/common/version.cpp
	${ENGINE_HEADERS}
	${UNIT_TEST_HEADERS}
	${UNIT_TEST_SOURCES}
	)
target_link_libraries(unit-test ${LIBS})

add_custom_command(
	OUTPUT "${game_SOURCE_DIR}/unit-test.log"
	COMMAND unit-test --root "${game_SOURCE_DIR}" --log "unit-test.log"
	DEPENDS unit-test ${PROJECT_INDEPENDENT_SOURCES} ${PROJECT_DEPENDENT_SOURCES} ${UNIT_TEST_SOURCES} ${UNIT_TEST_HEADERS} ${ENGINE_SOURCES}
	)
#
###############################################################################


###############################################################################
#
# Build rules for the executable
#
add_executable(
	game
 	main.cpp
	engine/independent/common/version.cpp
	unit-test.log
	${ENGINE_HEADERS}
	)
target_link_libraries(game glfw ${LIBS})
add_dependencies(game unit-test)
#
###############################################################################

