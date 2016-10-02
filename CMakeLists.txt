project( libexecstream_prj )
cmake_minimum_required( VERSION 2.8 )

option( LIBEXECSTREAM_SHARED "Build shared library" ON )

if( LIBEXECSTREAM_SHARED )
    set( libtype SHARED )
else( )
    set( libtype )
endif( )

find_package( Threads REQUIRED )

add_library( execstream ${libtype} src/exec-stream.cpp )
target_include_directories( execstream PUBLIC "${CMAKE_SOURCE_DIR}/include" )
target_link_libraries( execstream PUBLIC ${CMAKE_THREAD_LIBS_INIT} )

if( NOT MSVC )
    target_compile_options( execstream PRIVATE -fPIC )
endif( )

install( TARGETS execstream DESTINATION lib )
install( DIRECTORY include/ DESTINATION include )


add_executable( execstream_test_bin test/exec-stream-test.cpp ${HEADER_FILES} )
target_link_libraries( execstream_test_bin execstream ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
add_test( execstram_test, execstream_test_bin )
