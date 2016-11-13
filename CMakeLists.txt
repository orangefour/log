find_package(Qt5 COMPONENTS Network Quick Bluetooth Positioning REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp)
add_library(log SHARED ${SOURCES})
target_link_libraries(log spdlog)
target_include_directories(log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
qt5_use_modules(log Core)
