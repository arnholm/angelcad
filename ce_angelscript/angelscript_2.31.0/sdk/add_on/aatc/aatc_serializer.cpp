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


#include "aatc_config.hpp"
#if aatc_CONFIG_USE_ASADDON_SERIALIZER

#include "aatc_serializer.hpp"

#include "aatc_templatemagic.hpp"

#include "aatc_container_listing_heavy.hpp"






BEGIN_AS_NAMESPACE
namespace aatc {
	namespace serializer {

		serializer_specific_storage* aatc_serializer_specific_storage_global = nullptr;



		namespace usertype {



			namespace detail {
				namespace container_method {



					template<typename T_container, typename tag_insertfunc> struct restore_insert {};
					template<typename T_container> struct restore_insert<T_container, container::shared::tag::serializer_insert_value_func::insert> {
						void operator()(T_container* container, void* item)const {
							container->container.insert(item);
						}
					};
					template<typename T_container> struct restore_insert<T_container, container::shared::tag::serializer_insert_value_func::push_back> {
						void operator()(T_container* container, void* item)const {
							container->container.push_back(item);
						}
					};



					template<typename T_container, typename tag_is_map> struct Store {};
					template<typename T_container> struct Store<T_container, container::shared::tag::is_map::is_not_map> {
						void operator()(asIScriptEngine* engine, CSerializedValue* val_root, void* ptr)const {
							container::shared::container_basicbase* container_base = (container::shared::container_basicbase*)ptr;

							T_container* container_template = dynamic_cast<T_container*>(container_base);

							if (container_template) {
								if (container_template->handlemode) {
									for (auto it = container_template->container.begin(); it != container_template->container.end(); it++) {
										const void* ptr_to_object = *it;
										const void** ptr_to_ptr_to_object = &ptr_to_object;
										val_root->m_children.push_back(new CSerializedValue(val_root, "", "", const_cast<void*>((void*)ptr_to_ptr_to_object), container_template->astypeid_content));
									}
								} else {
									for (auto it = container_template->container.begin(); it != container_template->container.end(); it++) {
										val_root->m_children.push_back(new CSerializedValue(val_root, "", "", const_cast<void*>(*it), container_template->astypeid_content));
									}
								}
							} else {
								enginestorage::engine_level_storage* els = enginestorage::Get_ELS(container_base->engine);

								auto itend = els->serializer_tempspec_helpers[T_container::containertype_id].end();
								for (auto it = els->serializer_tempspec_helpers[T_container::containertype_id].begin(); it != itend; it++) {
									if (it->funcptr_is_thistype(container_base)) {
										it->funcptr_process_store(container_base, val_root);
										break;
									}
								}
							}
						}
					};
					template<typename T_container> struct Store<T_container, container::shared::tag::is_map::is_map> {
						void operator()(asIScriptEngine* engine, CSerializedValue* val_root, void* ptr)const {
							container::shared::container_basicbase* container_base = (container::shared::container_basicbase*)ptr;
							T_container* container = dynamic_cast<T_container*>(container_base);

							for (auto it = container->container.begin(); it != container->container.end(); it++) {
								auto& itpair = *it;

								switch (container->datahandlingid_key) {
								case common::DATAHANDLINGTYPE::HANDLE:
								{
									const void* ptr_to_object = itpair.first.ptr;
									const void** ptr_to_ptr_to_object = &ptr_to_object;
									val_root->m_children.push_back(new CSerializedValue(val_root, "", "", const_cast<void*>((void*)ptr_to_ptr_to_object), container->astypeid_key));
									break;
								}
								case common::DATAHANDLINGTYPE::STRING:
								case common::DATAHANDLINGTYPE::OBJECT:
								{
									val_root->m_children.push_back(new CSerializedValue(val_root, "", "", const_cast<void*>(itpair.first.ptr), container->astypeid_key));
									break;
								}
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									val_root->m_children.push_back(new CSerializedValue(val_root, "", "", const_cast<void*>(itpair.first.Get_Ptr_To_Primitive_Type_const(container->primitiveid_key)), container->astypeid_key));
									break;
								}
								};

								switch (container->datahandlingid_value) {
								case common::DATAHANDLINGTYPE::HANDLE:
								{
									const void* ptr_to_object = itpair.second.ptr;
									const void** ptr_to_ptr_to_object = &ptr_to_object;
									val_root->m_children.push_back(new CSerializedValue(val_root, "", "", const_cast<void*>((void*)ptr_to_ptr_to_object), container->astypeid_value));
									break;
								}
								case common::DATAHANDLINGTYPE::STRING:
								case common::DATAHANDLINGTYPE::OBJECT:
								{
									val_root->m_children.push_back(new CSerializedValue(val_root, "", "", const_cast<void*>(itpair.second.ptr), container->astypeid_value));
									break;
								}
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									val_root->m_children.push_back(new CSerializedValue(val_root, "", "", const_cast<void*>(itpair.second.Get_Ptr_To_Primitive_Type_const(container->primitiveid_value)), container->astypeid_value));
									break;
								}
								};
							}
						}
					};


					template<typename T_container, typename tag_is_map> struct Restore {};
					template<typename T_container> struct Restore<T_container, container::shared::tag::is_map::is_not_map> {
						typedef typename T_container::container_tags container_tags;
						typedef typename container_tags::serializer_insert_value_func container_tags__serializer_insert_value_func;

						void operator()(asIScriptEngine* engine, CSerializedValue* val_root, void* ptr)const {
							container::shared::container_basicbase* container_base = (container::shared::container_basicbase*)ptr;

							if (!container_base->engine) {
								container_base->engine = engine;
							}

							T_container* container_template = dynamic_cast<T_container*>(container_base);

							if (container_template) {
								container_template->container.clear();

								if (container_template->handlemode) {
									const std::size_t size = val_root->m_children.size();

									aatc_serializer_specific_storage_global->containers_1tp.push_back(serializer_specific_storage::Container_1tp());
									serializer_specific_storage::Container_1tp* handle_storage = &(aatc_serializer_specific_storage_global->containers_1tp.back());

									handle_storage->container = container_base;
									handle_storage->containertype_id = T_container::containertype_id;
									handle_storage->objects.assign(size, nullptr);

									for (std::size_t i = 0; i < size; i++) {
										val_root->m_children[i]->Restore(&(handle_storage->objects.data()[i]), container_template->astypeid_content);
									}
								} else {
									const std::size_t size = val_root->m_children.size();
									for (std::size_t i = 0; i < size; i++) {
										void* serialized_object = nullptr;
										serialized_object = container_base->engine->CreateScriptObject(container_template->objtype_content);
										val_root->m_children[i]->Restore(serialized_object, container_template->astypeid_content);
										detail::container_method::restore_insert<T_container, container_tags__serializer_insert_value_func> f; f(container_template, serialized_object);
										//functor_add<T_container, cond_is_associative> add; add(container_template, serialized_object);
									}
								}
							} else {
								enginestorage::engine_level_storage* els = enginestorage::Get_ELS(container_base->engine);

								auto itend = els->serializer_tempspec_helpers[T_container::containertype_id].end();
								for (auto it = els->serializer_tempspec_helpers[T_container::containertype_id].begin(); it != itend; it++) {
									if (it->funcptr_is_thistype(container_base)) {
										it->funcptr_process_restore(container_base, val_root);
										break;
									}
								}
							}
						}
					};
					template<typename T_container> struct Restore<T_container, container::shared::tag::is_map::is_map> {
						void operator()(asIScriptEngine* engine, CSerializedValue* val_root, void* ptr)const {
							container::shared::container_basicbase* container_base = (container::shared::container_basicbase*)ptr;
							T_container* container = dynamic_cast<T_container*>(container_base);

							const std::size_t size = val_root->m_children.size() / 2;

							serializer_specific_storage* storage = aatc_serializer_specific_storage_global;

							storage->containers_map.push_back(serializer_specific_storage::Container_map());
							serializer_specific_storage::Container_map& storage_container = storage->containers_map.back();

							storage_container.container = container_base;
							storage_container.containertype_id = T_container::containertype_id;
							storage_container.objects.assign(size, common::primunion_pair());

							for (std::size_t i = 0; i < size; i++) {
								CSerializedValue* val_key = val_root->m_children[i * 2];
								CSerializedValue* val_value = val_root->m_children[i * 2 + 1];

								common::primunion_pair& insertpair = storage_container.objects[i];

								switch (container->datahandlingid_key) {
								case common::DATAHANDLINGTYPE::HANDLE:
								{
									val_key->Restore(&(insertpair.first.ptr), container->astypeid_key);
									break;
								}
								case common::DATAHANDLINGTYPE::STRING:
								case common::DATAHANDLINGTYPE::OBJECT:
								{
									void* serialized_object = nullptr;
									serialized_object = container_base->engine->CreateScriptObject(container->typeinfo_key);
									val_key->Restore(serialized_object, container->astypeid_key);
									insertpair.first.ptr = serialized_object;
									break;
								}
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									void* ptr_to_prim = insertpair.first.Get_Ptr_To_Primitive_Type(container->primitiveid_key);
									val_key->Restore(ptr_to_prim, container->astypeid_key);
									break;
								}
								};

								switch (container->datahandlingid_value) {
								case common::DATAHANDLINGTYPE::HANDLE:
								{
									val_value->Restore(&(insertpair.second.ptr), container->astypeid_value);
									break;
								}
								case common::DATAHANDLINGTYPE::STRING:
								case common::DATAHANDLINGTYPE::OBJECT:
								{
									void* serialized_object = nullptr;
									serialized_object = container_base->engine->CreateScriptObject(container->typeinfo_value);
									val_value->Restore(serialized_object, container->astypeid_value);
									insertpair.second.ptr = serialized_object;
									break;
								}
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									void* ptr_to_prim = insertpair.second.Get_Ptr_To_Primitive_Type(container->primitiveid_value);
									val_value->Restore(ptr_to_prim, container->astypeid_value);
									break;
								}
								};
							}
						}
					};

					template<typename T_container, typename tag_is_map> struct CleanupUserData {};
					template<typename T_container> struct CleanupUserData<T_container, container::shared::tag::is_map::is_not_map> {
						void operator()(asIScriptEngine* engine, CSerializedValue* val)const {
							container::shared::container_basicbase* container_base = (container::shared::container_basicbase*)val->GetUserData();

							if (container_base) {//templates wont have this
								enginestorage::engine_level_storage* els = enginestorage::Get_ELS(container_base->engine);

								auto itend = els->serializer_tempspec_helpers[T_container::containertype_id].end();
								for (auto it = els->serializer_tempspec_helpers[T_container::containertype_id].begin(); it != itend; it++) {
									if (it->funcptr_is_thistype(container_base)) {
										it->funcptr_process_cleanup(container_base, val);
										break;
									}
								}
							}
						}
					};
					template<typename T_container> struct CleanupUserData<T_container, container::shared::tag::is_map::is_map> {
						void operator()(asIScriptEngine* engine, CSerializedValue* val)const {

						}
					};



				}//namespace container_method
			}//namespace detail



			template<typename T_container> struct Container : public CUserType {
				typedef typename T_container::container_tags container_tags;
				typedef typename container_tags::is_map container_tags__is_map;



				asIScriptEngine* engine;

				Container(asIScriptEngine* _engine) :
					engine(_engine)
				{}

				void Store(CSerializedValue* val_root, void* ptr) {
					detail::container_method::Store<T_container, container_tags__is_map> f; f(engine, val_root, ptr);
				}
				void Restore(CSerializedValue* val_root, void* ptr) {
					detail::container_method::Restore<T_container, container_tags__is_map> f; f(engine, val_root, ptr);
				}
				void CleanupUserData(CSerializedValue* val) {
					detail::container_method::CleanupUserData<T_container, container_tags__is_map> f; f(engine, val);
				}
			};



			#if aatc_CONFIG_USE_ASADDON_SERIALIZER_also_register_string_usertype
				struct String : public CUserType{
					void Store(CSerializedValue *val, void *ptr){
						val->SetUserData(new config::t::string(*(config::t::string*)ptr));
					}
					void Restore(CSerializedValue *val, void *ptr){
						config::t::string* buffer = (config::t::string*)val->GetUserData();
						*(config::t::string*)ptr = *buffer;
					}
					void CleanupUserData(CSerializedValue *val){
						config::t::string *buffer = (config::t::string*)val->GetUserData();
						delete buffer;
					}
				};
			#endif



		};//namespace usertype



		namespace detail {
			namespace staticiterate {



				template<int i> struct actual_serializer_AddUserType {
					typedef typename std::tuple_element<i, container::listing::heavy::tuple_templated_container_types>::type T_container;

					void operator()(asIScriptEngine* engine, CSerializer* serializer) {
						serializer->AddUserType(new usertype::Container<T_container>(engine), T_container::container_tags::scriptname_container);
					}
				};

				template<int i> class init_serializer_storage_container_metadata {
				public:
					typedef typename std::tuple_element<i, container::listing::heavy::tuple_templated_container_types>::type T_container;
					typedef typename T_container::container_tags container_tags;
					typedef typename container_tags::serializer_insert_value_func container_tags__serializer_insert_value_func;
					typedef typename container_tags::is_map container_tags__is_map;

					void operator()(serializer_specific_storage* storage) {
						tagselect_is_map<T_container, container_tags__serializer_insert_value_func, container_tags__is_map> f;  f(storage);
					}


					template<typename T_container, typename tag_insertfunc, typename tag_is_map> class tagselect_is_map {};
					template<typename T_container, typename tag_insertfunc> class tagselect_is_map<T_container, tag_insertfunc, container::shared::tag::is_map::is_map> {
					public:
						void operator()(serializer_specific_storage* storage)const {
							storage->containertype_metadatas[T_container::containertype_id].store_handle_in_container_map = final_static_wrapper;
						}

						static void final_static_wrapper(container::shared::container_basicbase* container, common::primunion_pair& item) {
							static_cast<T_container*>(container)->container.insert(item);
						}
					};
					template<typename T_container, typename tag_insertfunc> class tagselect_is_map<T_container, tag_insertfunc, container::shared::tag::is_map::is_not_map> {
					public:
						void operator()(serializer_specific_storage* storage)const {
							is_1tp_tagselect_insertfunc<T_container, tag_insertfunc> f;  f(storage);
						}
					};

					template<typename T_container, typename tag_insertfunc> class is_1tp_tagselect_insertfunc {};
					template<typename T_container> struct is_1tp_tagselect_insertfunc<T_container, container::shared::tag::serializer_insert_value_func::insert> {
						void operator()(serializer_specific_storage* storage)const {
							storage->containertype_metadatas[T_container::containertype_id].store_handle_in_container_1tp = final_static_wrapper;
						}

						static void final_static_wrapper(container::shared::container_basicbase* container, void* item) {
							static_cast<T_container*>(container)->container.insert(item);
						}
					};
					template<typename T_container> struct is_1tp_tagselect_insertfunc<T_container, container::shared::tag::serializer_insert_value_func::push_back> {
						void operator()(serializer_specific_storage* storage)const {
							storage->containertype_metadatas[T_container::containertype_id].store_handle_in_container_1tp = final_static_wrapper;
						}

						static void final_static_wrapper(container::shared::container_basicbase* container, void* item) {
							static_cast<T_container*>(container)->container.push_back(item);
						}
					};
				};



			};//namespace staticiterate
		};//namespace detail



		void Register(asIScriptEngine* engine, CSerializer* serializer){
			aatc_serializer_specific_storage_global = new serializer_specific_storage;

			serializer_specific_storage* storage = aatc_serializer_specific_storage_global;

			#if aatc_CONFIG_USE_ASADDON_SERIALIZER_also_register_string_usertype
				serializer->AddUserType(new usertype::String(), "string");
			#endif

			//serializer->AddUserType(new usertype::Container<container::templated::vector>(engine), config::scriptname::container::vector);
			//serializer->AddUserType(new usertype::Container<container::templated::list>(engine), config::scriptname::container::list);
			//serializer->AddUserType(new usertype::Container<container::templated::set>(engine), config::scriptname::container::set);
			//serializer->AddUserType(new usertype::Container<container::templated::unordered_set>(engine), config::scriptname::container::unordered_set);
			//serializer->AddUserType(new usertype::Container<container::mapped::templated::map>(engine), config::scriptname::container::map);
			//serializer->AddUserType(new usertype::Container<container::mapped::templated::unordered_map>(engine), config::scriptname::container::unordered_map);

			{ templatemagic::staticiterate_1arg<
				0,
				container::listing::heavy::tuple_templated_container_types_size - 1,
				detail::staticiterate::init_serializer_storage_container_metadata,

				serializer_specific_storage*
			> f; f(storage); }

			{ templatemagic::staticiterate_2arg<
				0,
				container::listing::heavy::tuple_templated_container_types_size - 1,
				detail::staticiterate::actual_serializer_AddUserType,

				asIScriptEngine*,
				CSerializer*
			> f; f(engine, serializer); }
		}

		void Cleanup(asIScriptEngine* engine, CSerializer* serializer){
			serializer_specific_storage* storage = aatc_serializer_specific_storage_global;

			if(storage){
				for(auto it = storage->containers_1tp.begin(); it != storage->containers_1tp.end(); it++){
					serializer_specific_storage::Container_1tp& cont = *it;
					for(auto it = cont.objects.begin(); it != cont.objects.end(); it++){
						storage->containertype_metadatas[cont.containertype_id].store_handle_in_container_1tp(cont.container, *it);
					}
				}
				for(auto it = storage->containers_map.begin(); it != storage->containers_map.end(); it++){
					serializer_specific_storage::Container_map& cont = *it;
					for(auto it = cont.objects.begin(); it != cont.objects.end(); it++){
						storage->containertype_metadatas[cont.containertype_id].store_handle_in_container_map(cont.container, *it);
					}
				}

				delete storage;
			}
		}



	};//namespace serializer
};//namespace aatc
END_AS_NAMESPACE
#endif