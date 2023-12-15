cmake_minimum_required(VERSION 3.10)
project(acces_dio)


#set ( CMAKE_C_FLAGS "-pthread")

#find_library(LIBRT rt)                                                                                               #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g3 -Wall  -fmessage-length=0 -v -fPIC")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -fPIC")
#set(-DBUILD_SHARED_LIBS=ON)                                                                                         

set(AIOUSB_LIBS ${AIOUSB_BINARY_DIR}/aiousb/libaiousb.a m pthread udev)


include_directories(../DIO)
include_directories(../include)
include_directories(../easylogging)
include_directories(../apcilib)
include_directories(../AIO)

add_library(acces_dio  SHARED io_access.cpp ../DIO/read_write_dio.cpp )
target_link_libraries(acces_dio ${AIOUSB_LIBS})

#add_executable(acces_dio_test main.cpp io_access.cpp ../DIO/read_write_dio.cpp aio_acces.cpp ../apcilib/apcilib.c #../AIO/read_write_aio.cpp)
#target_link_libraries(acces_dio_test ${AIOUSB_LIBS})

add_executable(acces_dio_test main.cpp  apcilib.c aio_acces.cpp  ../AIO/read_write_aio.cpp )
target_link_libraries(acces_dio_test ${AIOUSB_LIBS})

# Set the install directory for the library
#install(TARGETS test_shared DESTINATION build)

#if(LIBRT)
#target_link_libraries(Winch_Control ${LIBRT}) 
#endif()

#add_executable(Winch_Control_slave shared_memory_slave.c shared_memory.c)
#if(LIBRT)
#target_link_libraries(Winch_Control_slave ${LIBRT}) 
#endif()

