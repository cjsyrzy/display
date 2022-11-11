cmake_minimum_required(VERSION 3.0.0)
project(display VERSION 0.1.0)
# set(CMAKE_C_STANDARD 11)#C11
# set(CMAKE_CXX_STANDARD 17)#C17
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(CTest)
# enable_testing()

# add_definitions(-DWINVER=0x0602 -D_WIN32_WINNT=0x0602)
# add_compile_definitions(WINVER=0x0602 _WIN32_WINNT=0x0602)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

# add_subdirectory(lv_drivers)
# list(APPEND EXTRA_LIBS lv_drivers)

# add_subdirectory(lv_demos)
# list(APPEND EXTRA_LIBS lv_demos)

add_subdirectory(lvgl)
list(APPEND EXTRA_LIBS lvgl)

add_executable(display main.c)
# link library
target_link_libraries(display PUBLIC ${EXTRA_LIBS})
target_include_directories(display
                           PRIVATE ${PROJECT_SOURCE_DIR})