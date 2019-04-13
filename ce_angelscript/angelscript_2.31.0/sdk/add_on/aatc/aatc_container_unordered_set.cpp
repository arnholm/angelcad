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



#include "aatc_container_unordered_set.hpp"

#include "aatc_container_listing.hpp"
#include "aatc_container_templated_shared_method.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace listing {



			const char* container::listing::tags_of_container::unordered_set::scriptname_container = config::scriptname::container::unordered_set;



		}//namespace listing
		namespace templated {



			unordered_set::unordered_set(asITypeInfo* _typeinfo) :
				Containerbase(_typeinfo->GetEngine(), _typeinfo)
			{}
			unordered_set::unordered_set(const unordered_set& other) :
				Containerbase(other.engine, other.typeinfo_container)
			{
				(*this) = other;
			}
			unordered_set& unordered_set::operator=(const unordered_set& other) { Containerbase::operator=(other); return *this; }
			unordered_set& unordered_set::swap(unordered_set& other) { shared::method::swap(this, other); return *this; }


			void unordered_set::insert(void* value) { shared::method::native::insert_value(this, value); }

			bool unordered_set::erase(void* value) { return shared::method::native::erase_value(this, value); }
			void unordered_set::erase(const Iterator& position) { shared::method::native::erase_iterator(this, position); }
			config::t::sizetype unordered_set::erase(const Iterator& range_begin, const Iterator& range_end) { return shared::method::native::erase_iterator_range(this, range_begin, range_end); }

			unordered_set::Iterator unordered_set::find(void* value) { return shared::method::native::find_iterator(this, value); }
			bool unordered_set::contains(void* value) { return shared::method::native::contains(this, value); }



		};//namespace templated
		namespace listing {



			template<> void register_container<CONTAINER::UNORDERED_SET>(asIScriptEngine* engine) {
				common::RegistrationState rs(engine);

				{
					using namespace templated::shared;
					typedef templated::unordered_set T_container;

					register_containerbase<T_container>(rs);
					register_method::swap<T_container>(rs);



					register_method::native::insert_value<T_container>(rs);

					register_method::native::erase_value<T_container>(rs);
					register_method::native::erase_iterator<T_container>(rs);
					register_method::native::erase_iterator_range<T_container>(rs);

					register_method::native::find_iterator<T_container>(rs);
					register_method::native::contains<T_container>(rs);
				}

				container::shared::autoregister::register_all_tempspec_basics_for_container<tempspec::unordered_set>(engine);
			}
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::UNORDERED_SET>(enginestorage::template_specific_storage* tss) {
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