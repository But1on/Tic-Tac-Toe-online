# CMake generated Testfile for 
# Source directory: C:/Users/User/source/repos/Client12/Client12
# Build directory: C:/Users/User/source/repos/Client12/Client12/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(tests "C:/Users/User/source/repos/Client12/Client12/build/tests.exe" "-force-colors" "-d")
set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/source/repos/Client12/Client12/CMakeLists.txt;16;add_test;C:/Users/User/source/repos/Client12/Client12/CMakeLists.txt;0;")
subdirs("doctest")
