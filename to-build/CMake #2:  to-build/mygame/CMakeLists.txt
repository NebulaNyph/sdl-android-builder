cmake_minimum_required(VERSION 3.21)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)

PROJECT(MyRavGame)

if (ANDROID)
   string(REPLACE "-Wl,--gc-sections" "" CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
   string(REPLACE "-Wl,--no-undefined" "" CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
endif()

add_subdirectory("RavEngine" EXCLUDE_FROM_ALL)

file(GLOB SOURCES "*.cpp" "*.hpp" "*.h")
if (ANDROID)
   set(EXECUTABLE_NAME main)
   add_library("${EXECUTABLE_NAME}" SHARED)
else()
   set(EXECUTABLE_NAME "${PROJECT_NAME}")
   add_executable("${EXECUTABLE_NAME}")
endif()
target_sources(${EXECUTABLE_NAME} PRIVATE ${SOURCES})

target_link_libraries("${EXECUTABLE_NAME}" PUBLIC "RavEngine")
target_compile_features("${EXECUTABLE_NAME}" PRIVATE cxx_std_20)

if (ANDROID)
   set_target_properties(${EXECUTABLE_NAME} PROPERTIES
           DEBUG_POSTFIX ""
   )
endif()
