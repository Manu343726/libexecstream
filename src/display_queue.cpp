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

#include "libexecstream/display_queue.h"

namespace daw {
	display_queue::q_item::q_item( stream_type_t type, std::string item ) noexcept:
		stream_type{ type },
		line{ std::move( item ) } { }

	void display_queue::q_item::display( ) const {
		switch( stream_type ) {
			case stream_type_t::err:
				std::cerr << line << '\n';
				break;
			case stream_type_t::out:
				std::cout << line << '\n';
				break;
		}
	}

	display_queue::display_queue( ):
		m_mutex{ },
		items{ },
		m_continue{ true } { }

	void display_queue::add_item( stream_type_t type, std::string item ) {
		std::unique_lock<std::mutex> lock{ m_mutex };
		items.emplace_back( type, std::move( item ) ); 
		m_has_data.notify_all( );
	}

	void display_queue::display_items( ) {
		if( !items.empty( ) ) {
			for( auto const & item : items ) {
				item.display( );
			}
			items.clear( );
		}
	}

	void display_queue::start( ) {
		std::thread bkgrnd( [&]( ) {
			std::unique_lock<std::mutex> lock{ m_mutex };
			while( m_continue ) {
				m_has_data.wait_for( lock, std::chrono::seconds( 6000 ) );
				display_items( );
			}
		} );
		bkgrnd.detach( );
	}

	void display_queue::stop( ) {
		m_continue = false;
		display_items( );
	}

	display_queue::~display_queue( ) noexcept {
		try {
			stop( );
		} catch( ... ) { }
	}
}
