<<<<<<< HEAD
if(EXISTS "/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/testUnits[1]_tests.cmake")
  include("/home/samia/Documents/L3-CMI/PMP_Projects/units/build-clang/testUnits[1]_tests.cmake")
=======
if(EXISTS "/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/testUnits[1]_tests.cmake")
  include("/home/kilian/Bureau/Univ/PMP/PMP_Projects/units/build-clang/testUnits[1]_tests.cmake")
>>>>>>> 426b7249d2915e509a92cc46a7129bd99e855fcc
else()
  add_test(testUnits_NOT_BUILT testUnits_NOT_BUILT)
endif()
