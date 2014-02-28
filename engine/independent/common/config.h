#if !defined(__CONFIG_H__)
#define __CONFIG_H__

//==============================================================================

//------------------------------------------------------------------------------
// Use GLFW for the UI framework
//------------------------------------------------------------------------------
#define USE_GLFW 1

#define LOG_KEYBOARD_INPUT 0

#define DEFAULT_WINDOW_WIDTH (640)
#define DEFAULT_WINDOW_HEIGHT (400)
#define DEFAULT_WINDOW_TITLE "Framework Test"
#define DEFAULT_FRAMERATE (60.0)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Timer config
//------------------------------------------------------------------------------
#define TIMER_POOL_SIZE (16)
#define USE_DYNAMIC_TIMER_POOL 0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Console variables config
//------------------------------------------------------------------------------
#if defined(_DEBUG)
#define CONSOLE_HIDDEN_VARIABLES_ENABLED (0)
#define CONSOLE_DEVELOPMENT_VARIABLES_ENABLED (1)
#else
#define CONSOLE_HIDDEN_VARIABLES_ENABLED (1)
#define DEVELOPMENT_CONSOLE_VARIABLES_ENABLED (0)
#endif // defined(_DEBUG)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// File system config
//------------------------------------------------------------------------------
#define FILESYSTEM_MAX_HANDLES (16)
#if defined(_DEBUG)
#define FILESYSTEM_MAX_STORED_NAME_LENGTH (64)
#endif // defined(_DEBUG)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Log system config
//------------------------------------------------------------------------------
#define LOG_ROOT_NAME "Main"
#define LOG_BUFFER_SIZE (1024)
#define LOG_DEFAULT_DEBUG_LOG_LEVEL engine::CLog::eLL_DEBUG
#define LOG_DEFAULT_RELEASE_LOG_LEVEL engine::CLog::eLL_ERROR
//------------------------------------------------------------------------------

#define ENABLE_PROFILING 1

//==============================================================================
#endif // End [!defined(__CONFIG_H__)]
// [EOF]

