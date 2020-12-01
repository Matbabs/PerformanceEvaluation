cmake_minimum_required(VERSION 3.16)
project(CPP)

set(CMAKE_CXX_STANDARD 20)

find_package( Boost 1.71 COMPONENTS program_options REQUIRED )
find_package(Boost COMPONENTS thread system REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )


add_executable(multithread multithread.cpp)
target_link_libraries( multithread LINK_PUBLIC ${Boost_LIBRARIES} )

add_executable(singlethread singlethread.cpp)
target_link_libraries( singlethread LINK_PUBLIC ${Boost_LIBRARIES} )