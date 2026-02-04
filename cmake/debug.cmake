option(CMAKE_DEBUG_OUTPUT "Enable extra debug output in CMake" OFF)

# detect term
if(NOT DEFINED _DBG_COLORS_ENABLED)
  if("$ENV{TERM}" MATCHES "xterm|vt100|color|ansi|cygwin|linux")
    set(_DBG_COLORS_ENABLED TRUE)
  else()
    set(_DBG_COLORS_ENABLED FALSE)
  endif()
endif()

if(_DBG_COLORS_ENABLED)
  set(_DBG_COLOR_RESET "\\033[0m")
  set(_DBG_COLOR_GREEN "\\033[32m")
  set(_DBG_COLOR_YELLOW "\\033[33m")
  set(_DBG_COLOR_RED "\\033[31m")
  set(_DBG_COLOR_BLUE "\\033[34m")
  set(_DBG_COLOR_CYAN "\\033[36m")
else()
  set(_DBG_COLOR_RESET "")
  set(_DBG_COLOR_GREEN "")
  set(_DBG_COLOR_YELLOW "")
  set(_DBG_COLOR_RED "")
  set(_DBG_COLOR_BLUE "")
  set(_DBG_COLOR_CYAN "")
endif()

#
macro(_debug_base prefix color msg)
  if(CMAKE_DEBUG_OUTPUT)
    message(STATUS "${${color}}[${prefix}]${_DBG_COLOR_RESET} ${msg} (${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE})")
  endif()
endmacro()

macro(debug_info msg)
  _debug_base("INFO" _DBG_COLOR_GREEN "${msg}")
endmacro()

macro(debug_verbose msg)
  _debug_base("VERBOSE" _DBG_COLOR_CYAN "${msg}")
endmacro()

macro(debug_warning msg)
  message(WARNING "${_DBG_COLOR_YELLOW}[WARNING]${_DBG_COLOR_RESET} ${msg} (${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE})")
endmacro()

macro(debug_error msg)
  message(SEND_ERROR "${_DBG_COLOR_RED}[ERROR]${_DBG_COLOR_RESET} ${msg} (${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE})")
endmacro()

macro(debug_assert condition message)
  if(NOT (${condition}))
    message(FATAL_ERROR "${_DBG_COLOR_RED}[ASSERTION FAILED]${_DBG_COLOR_RESET} ${message} (${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE})")
  endif()
endmacro()

# ----------------------------------------------------------------------------
# Variable and list printing
macro(debug_var var)
  if(CMAKE_DEBUG_OUTPUT)
    if(DEFINED ${var})
      debug_info("${var} = [${${var}}]")
    else()
      debug_info("${var} is NOT DEFINED")
    endif()
  endif()
endmacro()

macro(debug_list var)
  if(CMAKE_DEBUG_OUTPUT)
    if(DEFINED ${var})
      debug_info("List ${var}:")
      foreach(item IN LISTS ${var})
        message(STATUS "  - ${item}")
      endforeach()
    else()
      debug_info("${var} is NOT DEFINED (list)")
    endif()
  endif()
endmacro()

macro(debug_match str pattern)
  if(CMAKE_DEBUG_OUTPUT)
    string(REGEX MATCH "${pattern}" _dbg_match_result "${str}")
    if(_dbg_match_result)
      debug_info("Matched pattern '${pattern}' in string '${str}'")
    endif()
  endif()
endmacro()

macro(debug_section name)
  if(CMAKE_DEBUG_OUTPUT)
    message(STATUS "${_DBG_COLOR_BLUE}====== [${name}] ======${_DBG_COLOR_RESET}")
  endif()
endmacro()

# ----------------------------------------------------------------------------
# Manual indented timing with nesting support
set(_DBG_INDENT "")

macro(debug_time_block_start name)
  if(CMAKE_DEBUG_OUTPUT)
    debug_info("${_DBG_INDENT}Starting ${name}...")
    string(TIMESTAMP "_dbg_start_${name}" "%s")
    set(_DBG_INDENT "${_DBG_INDENT}  ")  # increase indent
  endif()
endmacro()

macro(debug_time_block_end name)
  if(CMAKE_DEBUG_OUTPUT)
    string(TIMESTAMP "_dbg_end_${name}" "%s")
    math(EXPR "_dbg_duration_${name}" "${_dbg_end_${name}} - ${_dbg_start_${name}}")
    string(LENGTH "${_DBG_INDENT}" _indent_len)
    if(_indent_len GREATER 1)
      string(SUBSTRING "${_DBG_INDENT}" 2 -1 _DBG_INDENT)  # decrease indent
    endif()
    debug_info("${_DBG_INDENT}${name} finished in ${_dbg_duration_${name}} seconds.")
  endif()
endmacro()

# ----------------------------------------------------------------------------
# Stack-based manual timing (requires explicit block start and end)
set(_DBG_TIME_STACK "")

macro(debug_time_block name)
  if(CMAKE_DEBUG_OUTPUT)
    debug_time_block_start("${name}")
    list(PREPEND _DBG_TIME_STACK "${name}")
  endif()
endmacro()

macro(debug_time_block_end)
  if(CMAKE_DEBUG_OUTPUT)
    list(GET _DBG_TIME_STACK 0 _dbg_top_name)
    debug_time_block_end("${_dbg_top_name}")
    list(POP_FRONT _DBG_TIME_STACK)
  endif()
endmacro()

# ----------------------------------------------------------------------------
# Scoped timing blocks for automatic closing (no indenting needed)
function(debug_time_scope name)
  if(CMAKE_DEBUG_OUTPUT)
    debug_info("Starting ${name}...")
    string(TIMESTAMP "_dbg_start_${name}" "%s")
    list(PREPEND _DBG_TIME_STACK "${name}")
    set(_dbg_scope_name "${name}" PARENT_SCOPE)
  endif()
endfunction()

macro(debug_time_scope_end)
  if(CMAKE_DEBUG_OUTPUT)
    string(TIMESTAMP "_dbg_end_${_dbg_scope_name}" "%s")
    math(EXPR "_dbg_duration" "${_dbg_end_${_dbg_scope_name}} - ${_dbg_start_${_dbg_scope_name}}")
    debug_info("${_dbg_scope_name} finished in ${_dbg_duration} seconds.")
    list(POP_FRONT _DBG_TIME_STACK)
  endif()
endmacro()

macro(debug_with_time name)
  debug_time_scope("${name}")
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_FILE}")
  set(CMAKE_CURRENT_FUNCTION_EXIT_BEHAVIOR
    "${CMAKE_CURRENT_FUNCTION_EXIT_BEHAVIOR};debug_time_scope_end"
  )
endmacro()
