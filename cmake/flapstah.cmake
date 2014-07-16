###############################################################################
# Flapstah's CMAKE macros and helpers
###############################################################################

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
# Find lib before dll
#
IF(WIN32)
	SET(CMAKE_FIND_LIBRARY_SUFFIXES .a .lib .dll .dll.a)

	# Helpers for finding packages (might be useful for creating modules)
	math(EXPR BITS "8 * ${CMAKE_SIZEOF_VOID_P}")
	if (BITS MATCHES "64")
		set(PLATFORM "x64")
		set(ALT_PLATFORM "Win64")
	else (BITS MATCHES "64")
		set(PLATFORM "x86")
		set(ALT_PLATFORM "Win32")
	endif (BITS MATCHES "64")
ENDIF(WIN32)
#
###############################################################################

###############################################################################
#
# Macros to create file lists for building executables
#
# Both versions will generate XXX_SOURCES and XXX_HEADERS lists from the given
# location.  The RECURSE variant will recurse any subdirectories; the
# NO_RECURSE variant will only search the specified directory.  The macro will
# also generate a _NAME list with is a combination of source and header lists.
#
MACRO(FILE_LIST_RECURSE _NAME _LOCATION)
	file(GLOB_RECURSE ${_NAME}_HEADERS
		"${game_SOURCE_DIR}/${_LOCATION}/*.h"
		"${game_SOURCE_DIR}/${_LOCATION}/*.inl"
		)
	file(GLOB_RECURSE ${_NAME}_SOURCES
		"${game_SOURCE_DIR}/${_LOCATION}/*.cpp"
		)
	set(${_NAME} ${${_NAME}_HEADERS} ${${_NAME}_SOURCES})
ENDMACRO(FILE_LIST_RECURSE)

MACRO(FILE_LIST_NO_RECURSE _NAME _LOCATION)
	file(GLOB ${_NAME}_HEADERS
		"${game_SOURCE_DIR}/${_LOCATION}/*.h"
		"${game_SOURCE_DIR}/${_LOCATION}/*.inl"
		)
	file(GLOB ${_NAME}_SOURCES
		"${game_SOURCE_DIR}/${_LOCATION}/*.cpp"
		)
	set(${_NAME} ${${_NAME}_HEADERS} ${${_NAME}_SOURCES})
ENDMACRO(FILE_LIST_NO_RECURSE)
#
###############################################################################


