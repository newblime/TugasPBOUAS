cmake_minimum_required(VERSION 3.0.0)
project(TugasPBOUAS VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file( GLOB LIB_SOURCES ./*.cpp )
add_executable(TugasPBOUAS ${LIB_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
