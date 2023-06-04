set(LIB_NAME "library")

add_library(${LIB_NAME} src/lib.cpp)

# We need this directory, and users of our library will need it too
target_include_directories(${LIB_NAME} PUBLIC ../../include PRIVATE ./include)

# All users of this library will need at least C++11
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})