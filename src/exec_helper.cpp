
// The MIT License (MIT)
//
// Copyright (c) 2016 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <string>

#include "libexecstream/exec-stream.h"
#include "libexecstream/display_queue.h"

namespace daw {
	int display_output( std::string exec, std::string args  ) {
		daw::display_queue disp;
		exec_stream_t prog;
		prog.set_binary_mode( exec_stream_t::s_all );
		prog.set_wait_timeout( exec_stream_t::s_in|exec_stream_t::s_out|exec_stream_t::s_err, std::numeric_limits<exec_stream_t::timeout_t>::max( ) );
		prog.start( std::move( exec ), std::move( args ) );
		auto const disp_out = [&]( ) {
			std::string line;
			while( std::getline( prog.out( ), line ).good( ) ) {
				disp.add_item( daw::display_queue::stream_type_t::out, line );
			}
		};
		auto const disp_err = [&]( ) {
			std::string line;
			while( std::getline( prog.err( ), line ).good( ) ) {
				disp.add_item( daw::display_queue::stream_type_t::err, line );
			}
		};
		std::thread th_out{ disp_out }; 
		std::thread th_err{ disp_err }; 
		th_out.join( );
		th_err.join( );
		disp.stop( );
		std::cout << std::flush;
		std::cerr << std::flush;
		prog.close( );
		return prog.exit_code( );
	}
}    // namespace daw

