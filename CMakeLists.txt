project( libexecstream_prj )
cmake_minimum_required( VERSION 2.8 )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL 'MSVC' )
	add_compile_options( -D_WIN32_WINNT=0x0601 ) 
else( )
	find_package( Threads REQUIRED )
	if( THREADS_HAVE_PTHREAD_ARG )
		set( COMPILER_SPECIFIC_LIBS, "-lpthread" )
	endif( )

	if( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
		add_compile_options(-std=c++14 -Weverything -Wno-c++98-compat -g -Wno-covered-switch-default -Wno-padded -Wno-exit-time-destructors -Wno-c++98-compat-pedantic -Wno-unused-parameter -Wno-missing-noreturn -Wno-missing-prototypes -Wno-disabled-macro-expansion)
	elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
		add_compile_options(-std=c++14 -g -Wall -Wno-deprecated-declarations)
	endif( )
endif( )

option( LIBEXECSTREAM_SHARED "Build shared library" OFF )

if( LIBEXECSTREAM_SHARED )
    set( libtype SHARED )
else( )
    set( libtype )
endif( )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL 'MSVC' )
	add_compile_options( -D_WIN32_WINNT=0x0601 ) 
else( )
	find_package( Threads REQUIRED )
	if( THREADS_HAVE_PTHREAD_ARG )
		set( COMPILER_SPECIFIC_LIBS, "-lpthread" )
	endif()
endif()

add_library( execstream ${libtype} src/exec-stream.cpp )
target_include_directories( execstream PUBLIC "${CMAKE_SOURCE_DIR}/include" )
target_link_libraries( execstream PUBLIC ${CMAKE_THREAD_LIBS_INIT} )

if( NOT MSVC )
    target_compile_options( execstream PRIVATE -fPIC )
endif( )

install( TARGETS execstream DESTINATION lib )
install( DIRECTORY include/ DESTINATION include )


add_executable( exec-stream-test test/exec-stream-test.cpp ${HEADER_FILES} )
target_link_libraries( exec-stream-test execstream ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${COMPILER_SPECIFIC_LIBS} )
add_test( execstram_test, exec-stream-test )
