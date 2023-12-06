cmake_minimum_required(VERSION 3.10)
project(Winch_Control)

set ( CMAKE_C_FLAGS "-pthread")

find_library(LIBRT rt)                                                                                                                                                                                                                                                                                      

include_directories(../)
add_executable(Winch_Control shared_memory_main.c shared_memory.c)
if(LIBRT)
target_link_libraries(Winch_Control ${LIBRT}) 
endif()

add_executable(Winch_Control_slave shared_memory_slave.c shared_memory.c)
if(LIBRT)
target_link_libraries(Winch_Control_slave ${LIBRT}) 
endif()