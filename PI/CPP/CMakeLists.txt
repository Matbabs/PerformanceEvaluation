cmake_minimum_required(VERSION 3.16)
project(CPP)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES_MULTITHREAD multithread.cpp preprocessing.cpp)
set(SOURCES_SINGLETHREAD singlethread.cpp preprocessing.cpp)
include_directories(${PROJECT_SOURCE_DIR})

find_package( Boost 1.71 COMPONENTS program_options REQUIRED )
find_package(Boost COMPONENTS thread system REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )


add_executable(multithread ${SOURCES_MULTITHREAD})
target_link_libraries( multithread LINK_PUBLIC ${Boost_LIBRARIES} )

add_executable(singlethread ${SOURCES_SINGLETHREAD})
target_link_libraries( singlethread LINK_PUBLIC ${Boost_LIBRARIES} )