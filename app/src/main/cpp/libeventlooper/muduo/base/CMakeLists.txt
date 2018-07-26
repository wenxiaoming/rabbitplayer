set(base_SRCS
  Condition.cc
  CountDownLatch.cc
  Date.cc
  FileUtil.cc
  Exception.cc
  Logging.cc
  LogStream.cc
  Timestamp.cc
  TimeZone.cc
  Thread.cc
  ThreadPool.cc
  )

add_library(muduo_base SHARED ${base_SRCS})#build shared lib
#add_library(muduo_base ${base_SRCS})#build static lib
#target_link_libraries(muduo_base pthread rt)

#add_library(muduo_base_cpp11 ${base_SRCS})
#target_link_libraries(muduo_base_cpp11 pthread rt)
#set_target_properties(muduo_base_cpp11 PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS muduo_base DESTINATION lib)
#install(TARGETS muduo_base_cpp11 DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/muduo/base)

if(NOT CMAKE_BUILD_NO_EXAMPLES)
  #add_subdirectory(tests)
endif()

target_link_libraries(muduo_base
                      android
                      log)