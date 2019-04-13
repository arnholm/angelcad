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


#ifndef _includedh_aatc_container_listing
#define _includedh_aatc_container_listing



#include "aatc_common.hpp"
#include "aatc_container_shared.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace listing {



			enum CONTAINER {
				VECTOR,
				LIST,
				DEQUE,
				SET,
				UNORDERED_SET,
				MAP,
				UNORDERED_MAP,

				_COUNT
			};



			namespace tags_of_container {
				struct vector : public shared::tagbase {
					typedef shared::tag::iterator_access::access_is_mutable iterator_access;
					typedef shared::tag::serializer_insert_value_func::push_back serializer_insert_value_func;
					typedef shared::tag::is_map::is_not_map is_map;
					typedef shared::tag::is_associative::is_not_associative is_associative;

					static const char* scriptname_container;
				};

				struct list : public shared::tagbase {
					typedef shared::tag::iterator_access::access_is_mutable iterator_access;
					typedef shared::tag::serializer_insert_value_func::push_back serializer_insert_value_func;
					typedef shared::tag::is_map::is_not_map is_map;
					typedef shared::tag::is_associative::is_not_associative is_associative;

					static const char* scriptname_container;
				};

				struct deque : public shared::tagbase {
					typedef shared::tag::iterator_access::access_is_mutable iterator_access;
					typedef shared::tag::serializer_insert_value_func::push_back serializer_insert_value_func;
					typedef shared::tag::is_map::is_not_map is_map;
					typedef shared::tag::is_associative::is_not_associative is_associative;

					static const char* scriptname_container;
				};

				struct set : public shared::tagbase {
					typedef shared::tag::iterator_access::access_is_const iterator_access;
					typedef shared::tag::serializer_insert_value_func::insert serializer_insert_value_func;
					typedef shared::tag::is_map::is_not_map is_map;
					typedef shared::tag::is_associative::is_associative is_associative;

					static const char* scriptname_container;
				};
				struct unordered_set : public shared::tagbase {
					typedef shared::tag::iterator_access::access_is_const iterator_access;
					typedef shared::tag::serializer_insert_value_func::insert serializer_insert_value_func;
					typedef shared::tag::is_map::is_not_map is_map;
					typedef shared::tag::is_associative::is_associative is_associative;

					static const char* scriptname_container;
				};

				struct map : public shared::tagbase {
					typedef shared::tag::iterator_access::access_is_const iterator_access;
					typedef shared::tag::serializer_insert_value_func::insert serializer_insert_value_func;
					typedef shared::tag::is_map::is_map is_map;
					typedef shared::tag::is_associative::is_associative is_associative;

					static const char* scriptname_container;
				};
				struct unordered_map : public shared::tagbase {
					typedef shared::tag::iterator_access::access_is_const iterator_access;
					typedef shared::tag::serializer_insert_value_func::insert serializer_insert_value_func;
					typedef shared::tag::is_map::is_map is_map;
					typedef shared::tag::is_associative::is_associative is_associative;

					static const char* scriptname_container;
				};
			};



			template<int CONTAINER_ID> void register_container(asIScriptEngine* engine) {}
			template<int CONTAINER_ID> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template(enginestorage::template_specific_storage* tss) { return 0; }



			template<> void register_container<CONTAINER::VECTOR>(asIScriptEngine* engine);
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::VECTOR>(enginestorage::template_specific_storage* tss);

			template<> void register_container<CONTAINER::LIST>(asIScriptEngine* engine);
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::LIST>(enginestorage::template_specific_storage* tss);

			template<> void register_container<CONTAINER::DEQUE>(asIScriptEngine* engine);
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::DEQUE>(enginestorage::template_specific_storage* tss);

			template<> void register_container<CONTAINER::SET>(asIScriptEngine* engine);
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::SET>(enginestorage::template_specific_storage* tss);

			template<> void register_container<CONTAINER::UNORDERED_SET>(asIScriptEngine* engine);
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::UNORDERED_SET>(enginestorage::template_specific_storage* tss);

			template<> void register_container<CONTAINER::MAP>(asIScriptEngine* engine);
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::MAP>(enginestorage::template_specific_storage* tss);

			template<> void register_container<CONTAINER::UNORDERED_MAP>(asIScriptEngine* engine);
			template<> common::container_operations_bitmask_type errorcheck_missing_functions_make_bitfield_for_template<CONTAINER::UNORDERED_MAP>(enginestorage::template_specific_storage* tss);



		};//namespace listing
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif