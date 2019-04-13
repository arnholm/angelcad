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



#ifndef _includedh_aatc_config
#define _includedh_aatc_config



#include <stdio.h>
#include <stdint.h>
#include <assert.h>


// #include "angelscript.h"
#ifndef ANGELSCRIPT_H
// Avoid having to inform include path if header is already include before
#include <angelscript.h>
#endif


#include <algorithm>
#include <atomic>
#include <mutex>

#include <string>

#include <vector>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>



BEGIN_AS_NAMESPACE
namespace aatc {



//enable this if you're using the official as addon: serializer
#define aatc_CONFIG_USE_ASADDON_SERIALIZER 0
#define aatc_CONFIG_USE_ASADDON_SERIALIZER_also_register_string_usertype 1
#define aatc_serializer_addonpath "serializer/serializer.h"




/*
	Check for missing required methods (opEquals,opCmp,hash) in runtime, takes one bitwise-and operation and a branch
	per angelscript function call to a function that requires script functions, not much but something.
	With this enabled, missing methods will cause nothing to happen and raise an exception (if exceptions are enabled),
	without this missing methods will probably crash.
*/
#define aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME 1
#define aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_EXCEPTIONS 1

/*
	If any methods are missing, raise an exception during container constructor.
	Good for error checking with minimal runtime performance hit.
	Some methods might be missing but never called, in those cases this will be nothing but trouble.
*/
#define aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_MISSINGFUNCTIONS_ZERO_TOLERANCE 0
/*
	If missing methods are detected and the container's subtype is a handle,
	force the container into directcomp mode where script methods are not needed instead of raising an exception.
*/
#define aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_MISSINGFUNCTIONS_ZERO_TOLERANCE_USE_DIRECTCOMP 1

/*
	Every operation that changes a container increments a version number.
	If you try to access an iterator and it's version number differs from the container's, an exception will be thrown.
	Without this, illegal access will crash.
	This obviously reduces runtime performance.
*/
#define aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS 1



#if defined AS_64BIT_PTR
	#define aatc_ENABLE_HASHTYPE_BITS 64
#else
	#define aatc_ENABLE_HASHTYPE_BITS 32
#endif

//use script typedef for convenience in script?
#define aatc_ENABLE_REGISTER_TYPEDEF_HASH_TYPE 1





/*
	Actual container classes to use.
	ait  = actual implementation type
	acit = actual container implementation type
*/
#define aatc_ait_storage_map std::unordered_map
#define aatc_ait_storage_pair std::pair
#define aatc_acit_vector std::vector
#define aatc_acit_list std::list
#define aatc_acit_deque std::deque
#define aatc_acit_set std::set
#define aatc_acit_unordered_set std::unordered_set
#define aatc_acit_map std::map
#define aatc_acit_unordered_map std::unordered_map





namespace config {
	/*
	Directly compare handles as pointers in c++ instead of comparing the script objects by calling script functions.
	Blazing c++ speed but no script flexibility. Good for "stupid" pools of handles.
	This option is but a default, all container objects can have this set individually.
	*/
	static const int DEFAULT_HANDLEMODE_DIRECTCOMP = 0;



	namespace t {
		//primitive typedefs, set these appropriately for your platform if stdint doesnt work
		typedef ::uint8_t	uint8;
		typedef ::uint16_t	uint16;
		typedef ::uint32_t	uint32;
		typedef ::uint64_t	uint64;
		typedef ::int8_t	int8;
		typedef ::int16_t	int16;
		typedef ::int32_t	int32;
		typedef ::int64_t	int64;
		typedef float		float32;
		typedef double	float64;

		//use whatever you use in script (users of angelscript addon scriptstdstring should use std::string here)
		typedef ::std::string string;

		typedef int32 sizetype;
		typedef int32 astypeid;



		#if aatc_ENABLE_HASHTYPE_BITS == 32
			typedef uint32 hash;
		#elif aatc_ENABLE_HASHTYPE_BITS == 64
			typedef uint64 hash;
		#endif
	};//namespace t



	namespace scriptname {
		namespace t {
			static const char* size = "int";
			static const char* hash = "aatc_hash_t";

			#if aatc_ENABLE_HASHTYPE_BITS == 32
				static const char* hash_actual = "uint";
			#elif aatc_ENABLE_HASHTYPE_BITS == 64
				static const char* hash_actual = "uint64";
			#endif
		};//namespace t

		namespace container {
			static const char* vector = "vector";
			static const char* list = "list";
			static const char* deque = "deque";
			static const char* set = "set";
			static const char* unordered_set = "unordered_set";
			static const char* map = "map";
			static const char* unordered_map = "unordered_map";
		};//namespace container

		static const char* iterator_suffix = "_iterator";
		static const char* funcpointer = "aatc_funcpointer";
		static const char* funcdef_cmp_prefix = "aatc_funcdef_cmp_";

		namespace method {
			namespace content {
				static const char* hash = "hash";
			};//namespace content

			namespace container {
				static const char* set_directcomp = "SetDirectcomp";

				static const char* clear = "clear";
				static const char* size = "size";
				static const char* count = "count";
				static const char* empty = "empty";
				static const char* swap = "swap";

				static const char* front = "front";
				static const char* back = "back";
				static const char* push_front = "push_front";
				static const char* push_back = "push_back";
				static const char* pop_front = "pop_front";
				static const char* pop_back = "pop_back";
				static const char* reserve = "reserve";
				static const char* insert = "insert";
				static const char* erase = "erase";
				static const char* sort = "sort";
				static const char* sort_scriptfunc = sort;
				static const char* sort_aatcfuncptr = sort;
				static const char* contains = "contains";
				static const char* find = "find";
				static const char* erase_position = erase;
				static const char* erase_position_range = erase_position;
				static const char* erase_value = "erase_value";
				static const char* insert_position_before = insert;

				static const char* operator_index = "opIndex";

				static const char* begin = "begin";
				static const char* end = "end";
				static const char* find_iterator = "find_iterator";
				static const char* erase_iterator = erase;
				static const char* erase_iterator_range = erase_iterator;
				static const char* insert_iterator = insert;
			};//namespace container

			namespace iterator {
				static const char* access_property = "value";
				static const char* access_property_key = "key";
				static const char* access_property_value = "value";
				static const char* access_function = "current";
				static const char* access_function_key = "current_key";
				static const char* access_function_value = "current_value";
				static const char* is_end = "IsEnd";
				static const char* is_valid = "IsValid";
			};//namespace iterator
		};//namespace method
	};//namespace scriptname



	namespace detail {
		/*
			ID that the engine level userdata will use.
			Must not collide with other angelscript addons using engine level userdata;
		*/
		static const int engine_userdata_id = 8899;

		/*
			Random magical optimization numbers ahead.
		*/
		//this number was used by boost, so it must be legit ... right?
		static const int DEFAULT_CONTAINER_UNORDERED_SET_DEFAULTBUCKETCOUNT = 11;
		static const int DEFAULT_CONTAINER_UNORDERED_MAP_DEFAULTBUCKETCOUNT = 11;
	};//namespace detail



	namespace errormessage {
		namespace iterator {
			/*
				Happens when trying to access or set an iterator and the container has been modified after iterator construction.
			*/
			static const char* container_modified = "Invalid iterator. Container has been modified during iteration.";

			/*
				Used by the container if it tries to use an invalid iterator.

				Example of erasing twice with the same iterator:
				vector<int> myvec;
				//add 1 2 3 4 5 to vector
				auto it = myvec.find_iterator(3);
				myvec.erase(it);//no problem
				myvec.erase(it);//this line will cause this exception, because the first erase changed the container state and invalidated all iterators
			*/
			static const char* is_invalid = "Invalid iterator.";
		};//namespace iterator
	};//namespace errormessage
};//namespace config



namespace common { class std_Spinlock; };
namespace config {
	typedef common::std_Spinlock ait_fastlock;
};








/*
	Pimp your error messages here.
*/
#define aatc_errormessage_funcpointer_nothandle "Type '%s' not input as a handle."

#define aatc_errormessage_container_missingfunctions_formatting_param1 name_content
#define aatc_errormessage_container_missingfunctions_formatting_param2 name_container
#define aatc_errormessage_container_missingfunctions_formatting_param3 name_operation
#define aatc_errormessage_container_missingfunctions_formatting "Type '%s' has no method required for container's '%s::%s' method."

#define aatc_errormessage_container_access_empty_formatting_param1 name_container
#define aatc_errormessage_container_access_empty_formatting_param2 name_content
#define aatc_errormessage_container_access_empty_formatting_param3 name_operation
#define aatc_errormessage_container_access_empty_formatting "%s<%s>::%s called but the container is empty."

#define aatc_errormessage_container_access_bounds_formatting_param1 name_container
#define aatc_errormessage_container_access_bounds_formatting_param2 name_content
#define aatc_errormessage_container_access_bounds_formatting_param3 name_operation
#define aatc_errormessage_container_access_bounds_formatting_param4 index
#define aatc_errormessage_container_access_bounds_formatting_param5 size
#define aatc_errormessage_container_access_bounds_formatting "%s<%s>::%s(%i) is out of bounds. Size = %i."




};//namespace aatc
END_AS_NAMESPACE



#endif
