cmake_minimum_required(VERSION 3.10)
project(acces_dio)



set ( CMAKE_CXX_FLAGS "-pthread")


find_library(LIBRT rt)  

add_executable(acces_dio_test main.cpp  aiousb.cpp io_access.cpp read_write_dio.cpp adc-threads.cpp )
#target_link_libraries(acces_dio_test ${AIOUSB_LIBS})

add_library(acces_dio  SHARED aiousb.cpp io_access.cpp read_write_dio.cpp adc-threads.cpp)
#target_link_libraries(acces_dio ${AIOUSB_LIBS})

set_property(TARGET acces_dio_test acces_dio PROPERTY POSITION_INDEPENDENT_CODE ON)
set(NO_HOTPLUG 1)

if (AIOUSB_DEBUG)
  target_compile_definitions (acces_dio_test PRIVATE AIOUSB_DEBUG=1)
  target_compile_definitions (acces_dio PRIVATE AIOUSB_DEBUG=1)
else ()
  target_compile_definitions (acces_dio_test PRIVATE AIOUSB_DEBUG=0)
  target_compile_definitions (acces_dio PRIVATE AIOUSB_DEBUG=0)
endif (AIOUSB_DEBUG)

if (NO_HOTPLUG)
  target_compile_definitions(acces_dio_test PRIVATE NO_HOTPLUG=1)
  target_compile_definitions(acces_dio PRIVATE NO_HOTPLUG=1)
else()
  target_compile_definitions(acces_dio_test PRIVATE NO_HOTPLUG=0)
  target_compile_definitions(acces_dio PRIVATE NO_HOTPLUG=0)
endif(NO_HOTPLUG)
# Set the install directory for the library
#install(TARGETS test_shared DESTINATION build)

#if(LIBRT)
#target_link_libraries(Winch_Control ${LIBRT}) 
#endif()

#add_executable(Winch_Control_slave shared_memory_slave.c shared_memory.c)
#if(LIBRT)
#target_link_libraries(Winch_Control_slave ${LIBRT}) 
#endif()

