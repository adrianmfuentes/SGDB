# CMake generated Testfile for 
# Source directory: C:/Users/34644/Documents/GitHub/SGDB
# Build directory: C:/Users/34644/Documents/GitHub/SGDB/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(SGDBTests "C:/Users/34644/Documents/GitHub/SGDB/build/Debug/sgdb_test.exe")
  set_tests_properties(SGDBTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/34644/Documents/GitHub/SGDB/CMakeLists.txt;28;add_test;C:/Users/34644/Documents/GitHub/SGDB/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(SGDBTests "C:/Users/34644/Documents/GitHub/SGDB/build/Release/sgdb_test.exe")
  set_tests_properties(SGDBTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/34644/Documents/GitHub/SGDB/CMakeLists.txt;28;add_test;C:/Users/34644/Documents/GitHub/SGDB/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(SGDBTests "C:/Users/34644/Documents/GitHub/SGDB/build/MinSizeRel/sgdb_test.exe")
  set_tests_properties(SGDBTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/34644/Documents/GitHub/SGDB/CMakeLists.txt;28;add_test;C:/Users/34644/Documents/GitHub/SGDB/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(SGDBTests "C:/Users/34644/Documents/GitHub/SGDB/build/RelWithDebInfo/sgdb_test.exe")
  set_tests_properties(SGDBTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/34644/Documents/GitHub/SGDB/CMakeLists.txt;28;add_test;C:/Users/34644/Documents/GitHub/SGDB/CMakeLists.txt;0;")
else()
  add_test(SGDBTests NOT_AVAILABLE)
endif()
subdirs("googletest")
