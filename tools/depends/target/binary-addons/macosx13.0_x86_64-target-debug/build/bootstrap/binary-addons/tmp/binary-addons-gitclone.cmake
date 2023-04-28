
if(NOT "/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons-stamp/binary-addons-gitinfo.txt" IS_NEWER_THAN "/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons-stamp/binary-addons-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons-stamp/binary-addons-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/xbmc/repo-binary-addons.git" "binary-addons"
    WORKING_DIRECTORY "/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/xbmc/repo-binary-addons.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout Omega --
  WORKING_DIRECTORY "/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'Omega'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons-stamp/binary-addons-gitinfo.txt"
    "/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons-stamp/binary-addons-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/Users/redd/kodi/tools/depends/target/binary-addons/macosx13.0_x86_64-target-debug/build/bootstrap/binary-addons/src/binary-addons-stamp/binary-addons-gitclone-lastrun.txt'")
endif()

