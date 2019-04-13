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



#include "aatc_container_unordered_map.hpp"

#include "aatc_container_listing.hpp"
#include "aatc_container_mapped_templated_shared_method.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace listing {



			const char* container::listing::tags_of_container::unordered_map::scriptname_container = config::scriptname::container::unordered_map;



		}//namespace listing
		namespace mapped {
			namespace templated {



				unordered_map::unordered_map(asITypeInfo* _typeinfo) :
					Containerbase(_typeinfo->GetEngine(), _typeinfo)
				{}
				unordered_map::unordered_map(const unordered_map& other) :
					Containerbase(other.engine, other.typeinfo_container)
				{
					(*this) = other;
				}
				unordered_map& unordered_map::operator=(const unordered_map& other) { Containerbase::operator=(other); return *this; }

				unordered_map& unordered_map::swap(unordered_map& other) { shared::method::swap(this, other); return *this; }

				void unordered_map::insert(void* key, void* value) {shared::method::insert(this, key, value);}
				void unordered_map::erase(void* key) { shared::method::erase(this, key); }

				void* unordered_map::find_value(void* key) { return shared::method::find_value(this, key); }
				void* unordered_map::find_value(void* key, bool& success) { return shared::method::find_value(this, key, success); }
				bool unordered_map::contains(void* key) { return shared::method::contains(this, key); }

				unordered_map::Iterator unordered_map::find_iterator(void* key) { return shared::method::find_iterator(this, key); }
				bool unordered_map::erase_iterator(const Iterator& it) { return shared::method::erase_iterator(this, it); }
				config::t::sizetype unordered_map::erase_iterator(const Iterator& it_range_begin, const Iterator& it_range_end) { return shared::method::erase_iterator_range(this, it_range_begin, it_range_end); }

				void* unordered_map::operator[](void* key) { return shared::method::cpp_interface::operator_index(this, key); }



			};//namespace mapped
		};//namespace templated
		namespace listing {



			template<> void register_container<CONTAINER::UNORDERED_MAP>(asIScriptEngine* engine) {
				common::RegistrationState rs(engine);

				{
					using namespace mapped::templated::shared;
					typedef mapped::templated::unordered_map T_container;

					register_containerbase<T_container>(rs);
					register_method::swap<T_container>(rs);



					register_method::insert<T_container>(rs);
					register_method::erase<T_container>(rs);

					register_method::find<T_container>(rs);
					register_method::find_iterator<T_container>(rs);

					register_method::erase_iterator<T_container>(rs);
					register_method::erase_iterator_range<T_container>(rs);

					register_method::operator_index<T_container>(rs);
				}
			}
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::UNORDERED_MAP>(enginestorage::template_specific_storage* tss) {
				common::container_operations_bitmask_type mask = 0;

				if ((!tss->func_hash) || (!tss->func_equals)) {
					mask |= common::CONTAINER_OPERATION::ERASE_VALUE;
					mask |= common::CONTAINER_OPERATION::INSERT;
					mask |= common::CONTAINER_OPERATION::CONTAINS;
					mask |= common::CONTAINER_OPERATION::FIND;
				}
				
				return mask;
			}



		};//namespace listing



	};//namespace container
};//namespace aatc

END_AS_NAMESPACE