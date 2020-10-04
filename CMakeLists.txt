find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
add_subdirectory(spdlog)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SOURCES *.cpp)
add_library(log ${SOURCES})
target_link_libraries(log spdlog)
target_include_directories(log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
qt5_use_modules(log Core)
