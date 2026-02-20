# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
<<<<<<< HEAD
  "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-src"
  "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-build"
  "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
=======
  "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-src"
  "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-build"
  "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
<<<<<<< HEAD
    file(MAKE_DIRECTORY "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
=======
    file(MAKE_DIRECTORY "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
endif()
