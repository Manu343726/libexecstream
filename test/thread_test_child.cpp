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

int main( int, char ** ) {
	std::thread th1 = std::thread( []( ){
		for( size_t n = 0; n<10000; ++n ) {
			std::cout << "O: The value currently is " << n << '\n';
		}
	} );

	std::thread th2 = std::thread( []( ){
		for( size_t n = 10000; n<20000; ++n ) {
			std::cerr << "E: The value currently is " << n << '\n';
		}
	} );
	th1.join( );
	th2.join( );
	return EXIT_SUCCESS;
}
