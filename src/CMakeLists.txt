
if(LIBEXECSTREAM_SHARED)
    set(libtype SHARED)
else()
    set(libtype)
endif()

find_package(Threads REQUIRED)

add_library(libexecstream exec-stream.cpp ${libtype})
target_include_directories(libexecstream PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(libexecstream PUBLIC ${CMAKE_THREAD_LIBS_INIT})
