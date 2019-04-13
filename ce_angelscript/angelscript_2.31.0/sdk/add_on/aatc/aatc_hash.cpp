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



#include "aatc_common.hpp"
#include "aatc_hash.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace hash {



		config::t::hash hashfunctor<config::t::float32>::operator()(const config::t::float32& a) const {
			aatc::common::primunion pu;
			pu.f32 = a;
			return pu.ui64;
		}
		config::t::hash hashfunctor<config::t::float64>::operator()(const config::t::float64& a) const {
			aatc::common::primunion pu;
			pu.f64 = a;
			return pu.ui64;
		}
		config::t::hash hashfunctor<config::t::string>::operator()(const config::t::string& a) const {
			return hashfunc::djb2(a);
		}

		namespace hashfunc {
			config::t::hash djb2(const config::t::string& a) {
				config::t::hash hash = 5381;
				for (int i = 0; i < a.size(); i++) {
					hash = ((hash << 5) + hash) + a[i];
				}
				return hash;
			}
		};



	};//namespace hash
};//namespace aatc
END_AS_NAMESPACE