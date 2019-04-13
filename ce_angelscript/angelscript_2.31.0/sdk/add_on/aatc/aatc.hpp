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


#ifndef _includedh_aatc_aatc
#define _includedh_aatc_aatc

#include "aatc_config.hpp"
#include "aatc_container_listing.hpp"



BEGIN_AS_NAMESPACE

namespace aatc {



	/*!
	Just call this if you want to have every container available and dont care about engine specific settings.
	*/
	void RegisterAllContainers(asIScriptEngine* engine);



	/*!\brief The initializer class used for engine specific registration settings*/
	class Initializer {
	public:

		/*!
			This array will default to all false.
		*/
		bool include_container[container::listing::CONTAINER::_COUNT];

		Initializer(asIScriptEngine* engine);

		/*!
			Call this after setting your settings.
		*/
		void Go();


	private:
		asIScriptEngine* engine;
	};



	#if aatc_CONFIG_USE_ASADDON_SERIALIZER
		namespace serializer {
			void Register(asIScriptEngine* engine, CSerializer* serializer);
			void Cleanup(asIScriptEngine* engine, CSerializer* serializer);
		};
	#endif



};//namespace aatc
END_AS_NAMESPACE
#endif