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


#ifndef _includedh_aatc_serializer
#define _includedh_aatc_serializer

#include "aatc_config.hpp"
#if aatc_CONFIG_USE_ASADDON_SERIALIZER

#include "aatc.hpp"
#include "aatc_common.hpp"
#include "aatc_enginestorage.hpp"
#include "aatc_container_shared.hpp"
#include aatc_serializer_addonpath

BEGIN_AS_NAMESPACE
namespace aatc {
	namespace serializer {



		namespace engine_registration {
			template<typename T> bool container_basicbase_is_thistype(container::shared::container_basicbase* base) {
				return dynamic_cast<T*>(base) != nullptr;
			}
			template<typename T> void store(container::shared::container_basicbase* base, CSerializedValue* val_root) {
				T* container = static_cast<T*>(base);
				if (container) {
					val_root->SetUserData(new T(*container));
				}
			}
			template<typename T> void restore(container::shared::container_basicbase* base, CSerializedValue* val_root) {
				T* container = static_cast<T*>(base);
				if (container) {
					T* buffer = (T*)val_root->GetUserData();
					*container = *buffer;
				}
			}
			template<typename T> void cleanup(container::shared::container_basicbase* base, CSerializedValue* val_root) {
				T* buffer = (T*)val_root->GetUserData();
				delete buffer;
			}

			template<typename T_container, int containertype_id> void Register_els_helpers_for_tempspec(enginestorage::engine_level_storage* els, const char* n_content) {
				els->serializer_tempspec_helpers[containertype_id].push_back(enginestorage::engine_level_storage::serializer_helper());
				enginestorage::engine_level_storage::serializer_helper& sh = els->serializer_tempspec_helpers[containertype_id].back();

				sh.funcptr_is_thistype = container_basicbase_is_thistype<T_container>;
				sh.container_content_name = n_content;
				sh.funcptr_process_store = store<T_container>;
				sh.funcptr_process_restore = restore<T_container>;
				sh.funcptr_process_cleanup = cleanup<T_container>;
			}
		};//namespace engine_registration




		class serializer_specific_storage{
		public:
			class Container_1tp{
			public:
				container::shared::container_basicbase* container;
				int containertype_id;
				std::vector<void*> objects;
			};
			class Container_map{
			public:
				container::shared::container_basicbase* container;
				int containertype_id;
				std::vector<common::primunion_pair> objects;
			};

			struct Containertype_metadata {
				void (*store_handle_in_container_1tp)(container::shared::container_basicbase* base, void* item);
				void (*store_handle_in_container_map)(container::shared::container_basicbase* base, common::primunion_pair& item);
			};

			std::list<Container_1tp> containers_1tp;
			std::list<Container_map> containers_map;

			Containertype_metadata containertype_metadatas[container::listing::CONTAINER::_COUNT];
		};

		//global for now, while as addon serializer does not have serializer-object-specific userdata
		extern serializer_specific_storage* aatc_serializer_specific_storage_global;



	};//namespace serializer
};//namespace aatc
END_AS_NAMESPACE
#endif
#endif