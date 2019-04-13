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


#ifndef _includedh_aatc_hash
#define _includedh_aatc_hash

#include "aatc.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace hash {



		/*!\brief The functor that unordered containers use for hashing.

			You should specialize this for your c++ classes before making
			tempspecs of unordered containers of them.
		*/
		template<class T> class hashfunctor {
		public:
			config::t::hash operator()(const T& a) const {
				return (config::t::hash)a;
			}
		};
		template<> class hashfunctor<config::t::float32> {
		public:
			config::t::hash operator()(const config::t::float32& a) const;
		};
		template<> class hashfunctor<config::t::float64> {
		public:
			config::t::hash operator()(const config::t::float64& a) const;
		};
		template<> class hashfunctor<config::t::string> {
		public:
			config::t::hash operator()(const config::t::string& a) const;
		};



		namespace hashfunc {
			config::t::hash djb2(const config::t::string& a);
		};



		namespace detail {
			template<typename T> config::t::hash function_wrapping_a_functor(const T& me) {
				hashfunctor<T> functor;
				return functor(me);
			}
		};

		/*
			Use this to register your c++ classes for hashing in containers that don't have a tempspec available.
			Because you can't register functors with RegisterObjectMethod.
		*/

		template<typename T_your_cpp_type> void Register(asIScriptEngine* engine, const char* name_your_type_in_script) {
			char textbuf[common::RegistrationState::bufsize];
			common::RegistrationState::Format_static(textbuf, common::RegistrationState::bufsize, "%s %s()", config::scriptname::t::hash_actual, config::scriptname::method::content::hash);
			int error = engine->RegisterObjectMethod(name_your_type_in_script, textbuf, asFUNCTION(detail::function_wrapping_a_functor<T_your_cpp_type>), asCALL_CDECL_OBJLAST); assert(error >= 0);
		}



	};//namespace hash
};//namespace aatc
END_AS_NAMESPACE



#endif