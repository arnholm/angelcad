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


#ifndef _includedh_aatc_container_map
#define _includedh_aatc_container_map



#include "aatc_common.hpp"
#include "aatc_container_mapped_templated_shared.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {



		namespace mapped {
			namespace templated {



				namespace detail {
					namespace container_native_with_functors {
						typedef aatc_acit_map<
							common::primunion,
							common::primunion,
							container::shared::containerfunctor_map::Comp
						> map;
					};
				};//namespace detail



				class map : public shared::Containerbase <
					detail::container_native_with_functors::map,
					container::listing::CONTAINER::MAP,
					container::listing::tags_of_container::map ,
					shared::base_container_wrapper::Singleparam<
						detail::container_native_with_functors::map,
						container::shared::containerfunctor_map::Comp
					>
				> {
				public:
					map(asITypeInfo* typeinfo);
					map(const map& other);
					map& operator=(const map& other);



					map& swap(map& other);

					void insert(void* key, void* value);
					void erase(void* key);

					void* find_value(void* key);
					void* find_value(void* key, bool& success);
					bool contains(void* key);

					Iterator find_iterator(void* key);
					bool erase_iterator(const Iterator& it);
					config::t::sizetype erase_iterator(const Iterator& it_range_begin, const Iterator& it_range_end);

					void* operator[](void* key);
				};



			};//namespace templated
		};//namespace mapped
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif