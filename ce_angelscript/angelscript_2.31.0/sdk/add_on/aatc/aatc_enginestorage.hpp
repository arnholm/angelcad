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


#ifndef _includedh_aatc_enginestorage
#define _includedh_aatc_enginestorage

#include "aatc_common.hpp"
#include "aatc_container_listing.hpp"

#include <set>



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace enginestorage {



		class template_specific_storage;
		class containertype_specific_storage;
		class engine_level_storage;


		/*!\brief Stores the function pointers of a specific container<datatype>. One per datatype per container type per engine.*/
		class template_specific_storage{
		public:
			containertype_specific_storage* ctss;

			asIScriptFunction* func_equals;
			asIScriptFunction* func_cmp;
			asIScriptFunction* func_hash;

			common::container_operations_bitmask_type missing_functions;

			template_specific_storage(containertype_specific_storage* ctss,config::t::uint32 id);
		};

		/*!\brief Stores dataz about a specific container type. One per container type per engine.*/
		class containertype_specific_storage{
		public:
			engine_level_storage* els;
			config::t::uint32 container_id;

			//typedef aatc_ait_storage_map<uint32, aatc_iterator_storage*> tmap_is;
			//typedef aatc_ait_storage_pair<uint32, aatc_iterator_storage*> tpair_is;
			//tmap_is iterator_storages;
			//config::ait_fastlock iterator_storages_lock;

			typedef aatc_ait_storage_map<config::t::uint32, template_specific_storage*> tmap_tss;
			typedef aatc_ait_storage_pair<config::t::uint32, template_specific_storage*> tpair_tss;
			tmap_tss template_specific_storages;
			config::ait_fastlock template_specific_storages_lock;

			common::container_operations_bitmask_type (*func_errorcheck_missing_functions_make_bitfield_for_template)(template_specific_storage* tss);

			//aatc_iterator_storage* GetIteratorStorage(uint32 id);
			template_specific_storage* GetTemplateSpecificStorage(config::t::uint32 id);

			~containertype_specific_storage();
		};


		/*!\brief Stores dataz about aatc containers. One per engine.*/
		class engine_level_storage{
		public:
			#if aatc_CONFIG_USE_ASADDON_SERIALIZER
				class serializer_helper{
				public:
					serializer::funcptr_t_container_basicbase_is_thistype funcptr_is_thistype;
					std::string container_content_name;
					serializer::funcptr_t_container_basicbase_process funcptr_process_store;
					serializer::funcptr_t_container_basicbase_process funcptr_process_restore;
					serializer::funcptr_t_container_basicbase_process funcptr_process_cleanup;
				};
			#endif

			asIScriptEngine* engine;

			containertype_specific_storage containertype_specific_storages[container::listing::CONTAINER::_COUNT];

			std::vector<asIScriptContext*> context_cache;
			config::ait_fastlock context_cache_lock;

			#if aatc_CONFIG_USE_ASADDON_SERIALIZER
				std::vector<serializer_helper> serializer_tempspec_helpers[container::listing::CONTAINER::_COUNT];
			#endif

			std::set<std::string> registered_funcdefs;


			engine_level_storage(asIScriptEngine* engine);
			~engine_level_storage();

			containertype_specific_storage* GetContainerTypeSpecificStorage(config::t::uint32 id);

			asIScriptContext* contextcache_Get();
			void contextcache_Return(asIScriptContext* a);

			void Clean();

			void RegisterFuncdefIfNeeded(std::string const& def);
		};

		//convenience, uses engine level storage, aatc must be initialized
		asIScriptContext* contextcache_Get();
		void contextcache_Return(asIScriptContext* c);
		engine_level_storage* Get_ELS(asIScriptEngine* engine);

		//call before engine destruction, as engine is supposed to automatically call this
		//because of SetEngineUserDataCleanupCallback(this function),
		//but that didnt work during testing
		void engine_cleanup(asIScriptEngine* engine);



	};//namespace enginestorage
};//namespace aatc
END_AS_NAMESPACE



#endif