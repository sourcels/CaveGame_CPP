cmake_minimum_required(VERSION 3.10)

project(CaveGameCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})

if(WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE 
        "-static" 
        "-static-libgcc" 
        "-static-libstdc++"
        "-mconsole"
    )

    target_link_libraries(${PROJECT_NAME} kernel32 user32 gdi32 winmm)
endif()