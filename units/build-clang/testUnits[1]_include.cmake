<<<<<<< HEAD
if(EXISTS "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/testUnits[1]_tests.cmake")
  include("/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/testUnits[1]_tests.cmake")
=======
if(EXISTS "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/testUnits[1]_tests.cmake")
  include("/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/testUnits[1]_tests.cmake")
>>>>>>> 8cdadb6496d044ad7bece3f83df068fab6a7b582
else()
  add_test(testUnits_NOT_BUILT testUnits_NOT_BUILT)
endif()
