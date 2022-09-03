find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
add_subdirectory(spdlog)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SOURCES *.cpp)
add_library(log ${SOURCES})
target_link_libraries(log spdlog Qt6::Core)
target_include_directories(log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
