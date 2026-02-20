# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

<<<<<<< HEAD
if(EXISTS "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt" AND EXISTS "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitinfo.txt" AND
  "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt" IS_NEWER_THAN "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt'"
=======
if(EXISTS "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt" AND EXISTS "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitinfo.txt" AND
  "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt" IS_NEWER_THAN "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt'"
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
  )
  return()
endif()

execute_process(
<<<<<<< HEAD
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-src'")
=======
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-src'")
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/google/googletest.git" "googletest-src"
<<<<<<< HEAD
    WORKING_DIRECTORY "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps"
=======
    WORKING_DIRECTORY "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps"
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/google/googletest.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"
          checkout "52eb8108c5bdec04579160ae17225d66034bd723" --
<<<<<<< HEAD
  WORKING_DIRECTORY "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-src"
=======
  WORKING_DIRECTORY "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-src"
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '52eb8108c5bdec04579160ae17225d66034bd723'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git" 
            submodule update --recursive --init 
<<<<<<< HEAD
    WORKING_DIRECTORY "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-src"
=======
    WORKING_DIRECTORY "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-src"
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
<<<<<<< HEAD
  message(FATAL_ERROR "Failed to update submodules in: '/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-src'")
=======
  message(FATAL_ERROR "Failed to update submodules in: '/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-src'")
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
<<<<<<< HEAD
  COMMAND ${CMAKE_COMMAND} -E copy "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitinfo.txt" "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt'")
=======
  COMMAND ${CMAKE_COMMAND} -E copy "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitinfo.txt" "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/googletest-populate-gitclone-lastrun.txt'")
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
endif()
