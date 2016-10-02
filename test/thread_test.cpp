//	MIT License
//
//	Copyright (c) 2016 Darrell Wright
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//

#include <thread>
#include <cstdlib>
#include <iostream>

#include "libexecstream/exec-stream.h"

int do_test( ) {
	exec_stream_t prog;
	prog.start( "./thread_test_child", "" );
	auto const disp_out = [&prog]( ) {
		std::string line;
		while( std::getline( prog.out( ), line ).good( ) ) {
			std::cout << line << '\n';
		}
	};
	auto const disp_err = [&prog]( ) {
		std::string line;
		while( std::getline( prog.err( ), line ).good( ) ) {
			std::cerr << line << std::endl;
		}
	};
	std::thread th_out{ disp_out }; 
	std::thread th_err{ disp_err }; 
	th_out.join( );
	th_err.join( );
	std::cout << std::flush;
	std::cerr << std::flush;
	prog.close( );
	return prog.exit_code( );
}

int main( int, char ** ) {
	auto result = do_test( );
	std::cout << "Test returned result: " << result << std::endl;
	return EXIT_SUCCESS;
}
