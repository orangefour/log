find_package(Qt5 COMPONENTS Core REQUIRED)

add_subdirectory(spdlog)

file(GLOB SOURCES *.cpp)
add_library(log ${SOURCES})
target_link_libraries(log spdlog)
target_include_directories(log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
qt5_use_modules(log Core)
