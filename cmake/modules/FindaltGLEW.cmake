# - Find the OpenGL Extension Wrangler Library (GLEW)
# This module defines the following variables:
#  GLEW_INCLUDE_DIRS - include directories for GLEW
#  GLEW_LIBRARIES - libraries to link against GLEW
#  GLEW_FOUND - true if GLEW has been found and can be used

#=============================================================================
# (modified from FindGLEW.cmake by Andrew Catlender to make it work better
# on Windows when building GLEW from source)
#=============================================================================

if (WIN32)
  find_path( GLEW_INCLUDE_DIR NAMES GL/glew.h
		PATHS  ${GLEW_ROOT_PATH}/include )
  find_library( GLEW_LIBRARY NAMES GLEW glew32 glew glew32s
    PATHS
    ${OPENGL_LIBRARY_DIR}
		${GLEW_ROOT_PATH}/lib/Release/${ALT_PLATFORM}
    )
else ()
	find_path(GLEW_INCLUDE_DIR GL/glew.h)
	find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)
endif()

set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
set(GLEW_LIBRARIES ${GLEW_LIBRARY})

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(GLEW
                                  REQUIRED_VARS GLEW_INCLUDE_DIR GLEW_LIBRARY)

mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARY)
