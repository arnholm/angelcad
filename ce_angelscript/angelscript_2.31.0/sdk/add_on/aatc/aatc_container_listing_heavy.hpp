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


#ifndef _includedh_aatc_container_listing_heavy
#define _includedh_aatc_container_listing_heavy



//include all containers
#include "aatc_container_vector.hpp"
#include "aatc_container_list.hpp"
#include "aatc_container_deque.hpp"
#include "aatc_container_set.hpp"
#include "aatc_container_unordered_set.hpp"
#include "aatc_container_map.hpp"
#include "aatc_container_unordered_map.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace listing {
			namespace heavy {



				typedef std::tuple<
					container::templated::vector,
					container::templated::list,
					container::templated::deque,
					container::templated::set,
					container::templated::unordered_set,
					container::mapped::templated::map,
					container::mapped::templated::unordered_map
				> tuple_templated_container_types;
				static const int tuple_templated_container_types_size = std::tuple_size<tuple_templated_container_types>::value;



			};//namespace heavy
		};//namespace listing
		namespace tempspec {



			template<typename T_content> void RegisterAll_for_type(asIScriptEngine* engine, const char* scriptname_content) {
				common::RegistrationState rs(engine);

				container::tempspec::vector<T_content>::Register(rs, scriptname_content);
				container::tempspec::list<T_content>::Register(rs, scriptname_content);
				container::tempspec::deque<T_content>::Register(rs, scriptname_content);
				container::tempspec::set<T_content>::Register(rs, scriptname_content);
				container::tempspec::unordered_set<T_content>::Register(rs, scriptname_content);
			}



		};//namespace tempspec
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif