cmake_minimum_required(VERSION 3.29.3)
project(YadroTestProblem)
set(CMAKE_BUILD_TYPE Debug)

add_library(Tools src/Tools.cpp)
target_include_directories(Tools
    PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_library(Table src/Table.cpp)
target_include_directories(Table
    PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(Table 
    Tools)

add_library(InputEvents src/InputEvents.cpp)
target_include_directories(InputEvents
    PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(InputEvents 
    Tools Table OutputEvents)

add_library(OutputEvents src/OutputEvents.cpp)
target_include_directories(OutputEvents
    PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(OutputEvents
    Tools)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} 
    PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} 
    Tools Table InputEvents)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED True)