/*
The zlib/libpng License
http://opensource.org/licenses/zlib-license.php


Angelscript addon Template Containers
Copyright (c) 2014 Sami Vuorela

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1.	The origin of this software must not be misrepresented;
You must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2.	Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3.	This notice may not be removed or altered from any source distribution.


Sami Vuorela
samivuorela@gmail.com
*/



#include "aatc_container_deque.hpp"

#include "aatc_container_listing.hpp"
#include "aatc_container_templated_shared_method.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace listing {



			const char* container::listing::tags_of_container::deque::scriptname_container = config::scriptname::container::deque;



		}//namespace listing
		namespace templated {



			deque::deque(asITypeInfo* _typeinfo) :
				Containerbase(_typeinfo->GetEngine(), _typeinfo)
			{}
			deque::deque(const deque& other) :
				Containerbase(other.engine, other.typeinfo_container)
			{
				(*this) = other;
			}
			deque& deque::operator=(const deque& other) { Containerbase::operator=(other); return *this; }

			deque& deque::swap(deque& other) {
				shared::method::swap(this, other);
				return *this;
			}



			void deque::push_back(void* value) { shared::method::native::push_back(this, value); }
			void deque::pop_back() { shared::method::native::pop_back(this); }
			void deque::push_front(void* value) { shared::method::native::push_front(this, value); }
			void deque::pop_front() { shared::method::native::pop_front(this); }

			void* deque::back() { return shared::method::native::back(this); }
			void* deque::front() { return shared::method::native::front(this); }

			void* deque::operator[](config::t::sizetype position) { return shared::method::native::operator_index_position(this, position); }

			void deque::sort(bool ascending) { shared::method::genericcc::sort(this, ascending); }
			void deque::sort(common::script_Funcpointer* funcptr, bool ascending) { shared::method::genericcc::sort_aatcfuncptr(this,funcptr, ascending); }

			void deque::erase(config::t::sizetype position) { shared::method::genericcc::erase_position_constant(this, position); }
			void deque::erase(const Iterator& position) { shared::method::native::erase_iterator(this, position); }
			config::t::sizetype deque::erase(config::t::sizetype range_begin, config::t::sizetype range_end) { return shared::method::genericcc::erase_position_range_constant(this, range_begin, range_end); }
			config::t::sizetype deque::erase(const Iterator& range_begin, const Iterator& range_end) { return shared::method::native::erase_iterator_range(this, range_begin, range_end); }

			config::t::sizetype deque::erase_value(void* value, bool all) { return shared::method::genericcc::erase_value(this, value, all); }

			deque::Iterator deque::find(void* value) { return shared::method::genericcc::find_iterator(this, value); }

			void deque::insert(const Iterator& position, void* value) { shared::method::native::insert_iterator(this, position, value); }

			bool deque::contains(void* value) { return shared::method::genericcc::contains(this, value); }
			config::t::sizetype deque::count(void* value) { return shared::method::genericcc::count(this, value); }



		};//namespace templated
		namespace listing {



			template<> void register_container<CONTAINER::DEQUE>(asIScriptEngine* engine) {
				common::RegistrationState rs(engine);

				{
					using namespace templated::shared;
					typedef templated::deque T_container;

					register_containerbase<T_container>(rs);
					register_method::swap<T_container>(rs);



					register_method::native::push_back<T_container>(rs);
					register_method::native::pop_back<T_container>(rs);

					register_method::native::push_front<T_container>(rs);
					register_method::native::pop_front<T_container>(rs);

					register_method::native::back<T_container>(rs);
					register_method::native::front<T_container>(rs);

					register_method::native::operator_index_position<T_container>(rs);

					register_method::genericcc::sort<T_container>(rs);

					register_method::native::erase_iterator<T_container>(rs);
					register_method::genericcc::erase_position_constant<T_container>(rs);
					register_method::native::erase_iterator_range<T_container>(rs);
					register_method::genericcc::erase_position_range_constant<T_container>(rs);

					register_method::genericcc::erase_value<T_container>(rs);

					register_method::genericcc::find_iterator<T_container>(rs);

					register_method::native::insert_iterator<T_container>(rs);

					register_method::genericcc::contains<T_container>(rs);
					register_method::genericcc::count<T_container>(rs);
				}

				container::shared::autoregister::register_all_tempspec_basics_for_container<tempspec::deque>(engine);
			}
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::DEQUE>(enginestorage::template_specific_storage* tss) {
				common::container_operations_bitmask_type mask = 0;
				
				if (!tss->func_cmp) {
					mask |= common::CONTAINER_OPERATION::SORT;
				}
				if (!tss->func_equals) {
					mask |= common::CONTAINER_OPERATION::COUNT;
				}
				
				return mask;
			}



		};//namespace listing



	};//namespace container
};//namespace aatc

END_AS_NAMESPACE