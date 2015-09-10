# Locate the glfw library
# This module defines the following variables:
# GLFW_LIBRARY, the name of the library;
# GLFW_INCLUDE_DIR, where to find glfw include files.
# GLFW_FOUND, true if both the GLFW_LIBRARY and GLFW_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you could define an environment variable called
# GLFW_ROOT which points to the root of the glfw library installation. This is pretty useful
# on a Windows platform.
#
#
# Usage example to compile an "executable" target to the glfw library:
#
# FIND_PACKAGE (glfw REQUIRED)
# INCLUDE_DIRECTORIES (${GLFW_INCLUDE_DIR})
# ADD_EXECUTABLE (executable ${EXECUTABLE_SRCS})
# TARGET_LINK_LIBRARIES (executable ${GLFW_LIBRARY})
#
# TODO:
# Allow the user to select to link to a shared library or to a static library.

#Search for the include file...
find_path(GLFW_INCLUDE_DIR GL/glfw.h DOC "Path to GLFW include directory."
  HINTS
  $ENV{GLFW_ROOT_DIR}
  PATH_SUFFIXES include #For finding the include file under the root of the glfw expanded archive, typically on Windows.
  PATHS
  /usr/include/
  /usr/local/include/
  # By default headers are under GL subfolder
  /usr/include/GL
  /usr/local/include/GL
  ${GLFW_ROOT_DIR}/include/ # added by ptr
)

find_library(GLFW_LIBRARY DOC "Absolute path to GLFW library."
  NAMES glfw GLFW.lib
  HINTS
  $ENV{GLFW_ROOT_DIR}
  PATH_SUFFIXES lib/win32 #For finding the library file under the root of the glfw expanded archive, typically on Windows.
  PATHS
  /usr/local/lib
  /usr/lib
  ${GLFW_ROOT_DIR}/lib-msvc100/release # added by ptr
)

set(GLFW_FOUND 0)
if(GLFW_LIBRARY AND GLFW_INCLUDE_DIR)
  set(GLFW_FOUND 1)
  message(STATUS "Found GLFW: ${GLFW_LIBRARY} ${GLFW_INCLUDE_DIR}")
else()
	if(GLFW_FIND_REQUIRED)
		message(SEND_ERROR "GLFW not found!")
	else()
		message(STATUS "GLFW not found!")
	endif(GLFW_FIND_REQUIRED)
endif(GLFW_LIBRARY AND GLFW_INCLUDE_DIR)
