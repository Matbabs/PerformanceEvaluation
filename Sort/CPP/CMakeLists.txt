cmake_minimum_required(VERSION 3.16)
project(CPP)

set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR})

find_package( Boost 1.71 COMPONENTS program_options REQUIRED )
find_package(Boost COMPONENTS thread system REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

add_executable(block_indirect_sort preprocessing.cpp block_indirect_sort.cpp)
target_link_libraries( block_indirect_sort LINK_PUBLIC ${Boost_LIBRARIES} )

add_executable(sample_sort preprocessing.cpp block_indirect_sort.cpp)
target_link_libraries( sample_sort LINK_PUBLIC ${Boost_LIBRARIES} )

add_executable(parallel_stable_sort preprocessing.cpp parallel_stable_sort.cpp)
target_link_libraries( parallel_stable_sort LINK_PUBLIC ${Boost_LIBRARIES} )

add_executable(singlethread preprocessing.cpp singlethread.cpp)
target_link_libraries( singlethread LINK_PUBLIC ${Boost_LIBRARIES} )