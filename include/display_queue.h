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

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <mutex>
#include <thread>
#include <vector>

namespace daw {
	struct display_queue {
		enum class stream_type_t { out, err };

	private:
		class q_item {
			stream_type_t stream_type;
			std::string line;
		public:
			q_item( stream_type_t type, std::string item ) noexcept;

			void display( ) const;
		};	// q_item

		std::mutex m_mutex;
		std::vector<q_item> items;	
		std::atomic<bool> m_continue;
		std::condition_variable m_has_data;

	public:
		display_queue( );
		void add_item( stream_type_t type, std::string item );
		void display_items( );
		void start( );
		void stop( );
		~display_queue( ) noexcept;

		display_queue( display_queue const & ) = delete;
		display_queue( display_queue && ) = default;
		display_queue & operator=( display_queue const & ) = delete;
		display_queue & operator=( display_queue && ) = default;
	};	// display_queue
}
