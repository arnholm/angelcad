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


#ifndef _includedh_aatc_container_mapped_templated_shared
#define _includedh_aatc_container_mapped_templated_shared



#include "aatc_common.hpp"
#include "aatc_enginestorage.hpp"
#include "aatc_container_shared.hpp"
#include "aatc_container_listing.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace mapped {
			namespace templated {
				namespace shared {



					//doxygen skip
					#ifndef DOXYGEN_SHOULD_SKIP_THIS

					//we need a wrapper around the base container so that we can
					//feed the constructor a fancy functor to handle internal functions that require script functions to be called
					namespace base_container_wrapper {
						template<
							typename T_container
						> class Basic : public T_container {
						public:
							Basic(asIScriptEngine* engine, container::shared::containerfunctor_map::Settings* settings) {}
						};

						template<
							typename T_container,
							typename T_param1
						> class Singleparam : public T_container {
						public:
							Singleparam(asIScriptEngine* _engine, container::shared::containerfunctor_map::Settings* settings) :
								T_container(T_param1(_engine, settings))
							{}
						};

						template<
							typename T_container,
							typename T_param1,
							typename T_param2,
							std::size_t default_bucket_count = config::detail::DEFAULT_CONTAINER_UNORDERED_MAP_DEFAULTBUCKETCOUNT
						> class Hashed : public T_container {
						public:
							Hashed(asIScriptEngine* _engine, container::shared::containerfunctor_map::Settings* settings) :
								T_container(default_bucket_count, T_param1(_engine, settings), T_param2(_engine, settings))
							{}
						};
					};

					#endif
					//doxygen skip



					namespace factory {
						template<typename T_container> T_container* Factory_default(asITypeInfo* objtype) {
							return new T_container(objtype);
						}
						template<typename T_container> T_container* Factory_copy(asITypeInfo* objtype, const T_container& other) {
							return new T_container(other);
						}
					}
					namespace asglue {
						template<typename T_container> T_container* Factory_default(asITypeInfo* objtype) {
							return factory::Factory_default<T_container>(objtype);
						}
						template<typename T_container> T_container* Factory_copy(asITypeInfo* objtype, T_container* other) {
							T_container* result = factory::Factory_copy<T_container>(objtype, *other);
							other->refcount_Release();
							return result;
						}
						template<typename T_container> T_container& Assign(T_container* t, T_container* other) {
							*t = *other;
							other->refcount_Release();
							return *t;
						}
					}



					/*!\brief Internal template monster

					*/
					template<
						typename T_container,
						int _containertype_id,
						typename T_container_tags = aatc::container::shared::tagbase,
						typename bcw = base_container_wrapper::Basic<T_container>
					>class Containerbase :
						public container::shared::container_basicbase,
						public common::basetype_refcounted_GC,
						public container::shared::containerfunctor_map::Settings
					{
					public:
						typedef T_container T_container_native;
						typedef typename T_container_native::iterator T_iterator_native;
						typedef typename T_container_native::const_iterator T_iterator_native_const;

						static const int containertype_id = _containertype_id;
						typedef T_container_tags container_tags;



						bcw container;

						enginestorage::engine_level_storage* els;

						common::DATAHANDLINGTYPE datahandlingid_value;
						common::PRIMITIVE_TYPE primitiveid_value;

						asITypeInfo* typeinfo_container;
						asITypeInfo* typeinfo_key;
						asITypeInfo* typeinfo_value;

						config::t::astypeid astypeid_key;
						config::t::astypeid astypeid_value;

						bool objectmode_key;
						bool objectmode_value;
						bool needref_key;
						bool needref_value;

						aatc::common::container_operations_bitmask_type missing_functions;

						bool directcomp_forced;
						bool need_errorcheck_missing_functions;

						Containerbase(asIScriptEngine* _engine, asITypeInfo* _typeinfo) :
							container::shared::container_basicbase(_engine),
							container(_engine, this),
							basetype_refcounted_GC(),
							typeinfo_container(_typeinfo),
							needref_key(1),
							needref_value(1),
							directcomp_forced(0),
							need_errorcheck_missing_functions(1),
							typeinfo_key(nullptr),
							typeinfo_value(nullptr)
						{
							engine = _engine;

							astypeid_key = typeinfo_container->GetSubTypeId(0);
							astypeid_value = typeinfo_container->GetSubTypeId(1);

							datahandlingid_key = common::Determine_Datahandlingtype(engine, astypeid_key);
							datahandlingid_value = common::Determine_Datahandlingtype(engine, astypeid_value);

							handlemode_directcomp = 0;

							switch (datahandlingid_key) {
							case common::DATAHANDLINGTYPE::PRIMITIVE:
							{
								primitiveid_key = common::Determine_Primitivetype(astypeid_key);
								need_errorcheck_missing_functions = 0;
								objectmode_key = 0;
								break;
							}
							case common::DATAHANDLINGTYPE::STRING:
							{
								need_errorcheck_missing_functions = 0;
								objectmode_key = 0;
								typeinfo_key = engine->GetTypeInfoById(engine->GetStringFactoryReturnTypeId());
								break;
							}
							default:
							{
								objectmode_key = 1;

								if (datahandlingid_key == common::DATAHANDLINGTYPE::HANDLE) {
									handlemode_directcomp = config::DEFAULT_HANDLEMODE_DIRECTCOMP;
								}

								if (handlemode_directcomp) {
									need_errorcheck_missing_functions = 0;
								}

								typeinfo_key = typeinfo_container->GetSubType(0);
								if (astypeid_key & asOBJ_NOCOUNT) { needref_key = 0; }
								break;
							}
							};
							switch (datahandlingid_value) {
							case common::DATAHANDLINGTYPE::PRIMITIVE:
							{
								objectmode_value = 0;
								primitiveid_value = common::Determine_Primitivetype(astypeid_value);
								break;
							}
							case common::DATAHANDLINGTYPE::STRING:
							{
								objectmode_value = 0;
								typeinfo_value = engine->GetTypeInfoById(engine->GetStringFactoryReturnTypeId());
								break;
							}
							default:
							{
								objectmode_value = 1;
								typeinfo_value = typeinfo_container->GetSubType(1);
								if (astypeid_value & asOBJ_NOCOUNT) { needref_value = 0; }
								break;
							}
							};

							els = enginestorage::Get_ELS(engine);
							enginestorage::containertype_specific_storage* ctss = els->GetContainerTypeSpecificStorage(containertype_id);

							enginestorage::template_specific_storage* tss = ctss->GetTemplateSpecificStorage(astypeid_key);
							func_equals = tss->func_equals;
							func_cmp = tss->func_cmp;
							func_hash = tss->func_hash;

							missing_functions = tss->missing_functions;

							if (need_errorcheck_missing_functions) {
#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_MISSINGFUNCTIONS_ZERO_TOLERANCE
								if (missing_functions) {
									bool bad = 1;

#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_MISSINGFUNCTIONS_ZERO_TOLERANCE_USE_DIRECTCOMP
									if (datahandlingid_key == common::DATAHANDLINGTYPE::HANDLE) {//force handlemode directcomp if anything is missing
										handlemode_directcomp = 1;
										directcomp_forced = 1;
										bad = 0;
									}
#endif

									if (bad) {
										char msg[1000];
										common::RegistrationState::Format_static(msg, 1000, "Type '%s' has missing methods required for container '%s'.", objtype_content->GetName(), typeinfo_container->GetName());
										asGetActiveContext()->SetException(msg);
									}
								}
#endif
							}


							engine->NotifyGarbageCollectorOfNewObject(this, typeinfo_container);
						}
						~Containerbase() {
							clear();
						}

						Containerbase& operator=(const Containerbase& other) {
							safety_iteratorversion_Increment();

							clear();//will delete script objects or decrement handles

							handlemode_directcomp = other.handlemode_directcomp;
							directcomp_forced = other.directcomp_forced;

							if (!objectmode_key) {//use simple copy without inserts
								container.operator=(other.container);

								if (datahandlingid_key == common::DATAHANDLINGTYPE::STRING) {
									T_iterator_native it = container.begin();
									T_iterator_native it_end = container.end();

									for (; it != it_end; it++) {
										void*& iii = const_cast<void*&>((*it).first.ptr);
										iii = engine->CreateScriptObjectCopy(iii, typeinfo_key);
									}
								}

								switch (datahandlingid_value) {
								case common::DATAHANDLINGTYPE::STRING:
								{
									T_iterator_native it = container.begin();
									T_iterator_native it_other = const_cast<bcw&>(other.container).begin();
									T_iterator_native it_end = container.end();

									for (; it != it_end;) {
										void*& iii = const_cast<void*&>((*it).second.ptr);
										void*& iii_other = const_cast<void*&>((*it_other).second.ptr);

										iii = engine->CreateScriptObjectCopy(iii_other, typeinfo_value);

										it++;
										it_other++;
									}
									break;
								}
								case common::DATAHANDLINGTYPE::HANDLE:
								{
									for (auto it = container.begin(); it != container.end(); it++) {
										engine->AddRefScriptObject((*it).second.ptr, typeinfo_value);
									}
									break;
								}
								case common::DATAHANDLINGTYPE::OBJECT:
								{
									T_iterator_native it = container.begin();
									T_iterator_native it_other = const_cast<bcw&>(other.container).begin();
									T_iterator_native it_end = container.end();

									for (; it != it_end;) {
										void*& iii = const_cast<void*&>((*it).second.ptr);
										void*& iii_other = const_cast<void*&>((*it_other).second.ptr);

										iii = engine->CreateScriptObjectCopy(iii_other, typeinfo_value);

										it++;
										it_other++;
									}
									break;
								}
								};
							} else {//copy by inserting everything, takes time
								for (auto it = other.container.begin(); it != other.container.end(); it++) {
									common::primunion& otherpu_key = const_cast<common::primunion&>((*it).first);
									common::primunion& otherpu_value = const_cast<common::primunion&>((*it).second);

									common::primunion pu_key;
									common::primunion pu_value;

									switch (datahandlingid_key) {
									case common::DATAHANDLINGTYPE::HANDLE:
									{
										pu_key.ptr = otherpu_key.ptr;
										engine->AddRefScriptObject(pu_key.ptr, typeinfo_key);
										break;
									}
									case common::DATAHANDLINGTYPE::OBJECT:
									{
										pu_key.ptr = engine->CreateScriptObjectCopy(otherpu_key.ptr, typeinfo_key);
										break;
									}
									case common::DATAHANDLINGTYPE::STRING:
									{
										pu_key.ptr = engine->CreateScriptObjectCopy(otherpu_key.ptr, typeinfo_key);
										break;
									}
									case common::DATAHANDLINGTYPE::PRIMITIVE:
									{
										switch (primitiveid_key) {
										case common::PRIMITIVE_TYPE::INT8: { pu_key.i8 = otherpu_key.i8; break; }
										case common::PRIMITIVE_TYPE::INT16: { pu_key.i16 = otherpu_key.i16; break; }
										case common::PRIMITIVE_TYPE::INT32: { pu_key.i32 = otherpu_key.i32; break; }
										case common::PRIMITIVE_TYPE::INT64: { pu_key.i64 = otherpu_key.i64; break; }
										case common::PRIMITIVE_TYPE::UINT8: { pu_key.ui8 = otherpu_key.ui8; break; }
										case common::PRIMITIVE_TYPE::UINT16: { pu_key.ui16 = otherpu_key.ui16; break; }
										case common::PRIMITIVE_TYPE::UINT32: { pu_key.ui32 = otherpu_key.ui32; break; }
										case common::PRIMITIVE_TYPE::UINT64: { pu_key.ui64 = otherpu_key.ui64; break; }
										case common::PRIMITIVE_TYPE::FLOAT32: { pu_key.f32 = otherpu_key.f32; break; }
										case common::PRIMITIVE_TYPE::FLOAT64: { pu_key.f64 = otherpu_key.f64; break; }
										};
										break;
									}
									};

									switch (datahandlingid_value) {
									case common::DATAHANDLINGTYPE::HANDLE:
									{
										pu_value.ptr = otherpu_value.ptr;
										engine->AddRefScriptObject(pu_value.ptr, typeinfo_value);
										break;
									}
									case common::DATAHANDLINGTYPE::OBJECT:
									{
										pu_value.ptr = engine->CreateScriptObjectCopy(otherpu_value.ptr, typeinfo_value);
										break;
									}
									case common::DATAHANDLINGTYPE::STRING:
									{
										pu_value.ptr = engine->CreateScriptObjectCopy(otherpu_value.ptr, typeinfo_value);
										break;
									}
									case common::DATAHANDLINGTYPE::PRIMITIVE:
									{
										switch (primitiveid_value) {
										case common::PRIMITIVE_TYPE::INT8: { pu_value.i8 = otherpu_value.i8; break; }
										case common::PRIMITIVE_TYPE::INT16: { pu_value.i16 = otherpu_value.i16; break; }
										case common::PRIMITIVE_TYPE::INT32: { pu_value.i32 = otherpu_value.i32; break; }
										case common::PRIMITIVE_TYPE::INT64: { pu_value.i64 = otherpu_value.i64; break; }
										case common::PRIMITIVE_TYPE::UINT8: { pu_value.ui8 = otherpu_value.ui8; break; }
										case common::PRIMITIVE_TYPE::UINT16: { pu_value.ui16 = otherpu_value.ui16; break; }
										case common::PRIMITIVE_TYPE::UINT32: { pu_value.ui32 = otherpu_value.ui32; break; }
										case common::PRIMITIVE_TYPE::UINT64: { pu_value.ui64 = otherpu_value.ui64; break; }
										case common::PRIMITIVE_TYPE::FLOAT32: { pu_value.f32 = otherpu_value.f32; break; }
										case common::PRIMITIVE_TYPE::FLOAT64: { pu_value.f64 = otherpu_value.f64; break; }
										};
										break;
									}
									};

									container.insert(std::pair<common::primunion, common::primunion>(pu_key, pu_value));
								}
							}

							return *this;
						}


						void EnumReferences(asIScriptEngine* engine) {
							if (objectmode_key) {
								T_iterator_native it = container.begin();
								T_iterator_native itend = container.end();
								for (; it != itend; it++) {
									engine->GCEnumCallback((*it).first.ptr);
								}
							}
							if (objectmode_value) {
								T_iterator_native it = container.begin();
								T_iterator_native itend = container.end();
								for (; it != itend; it++) {
									engine->GCEnumCallback((*it).second.ptr);
								}
							}
						}
						void ReleaseAllReferences(asIScriptEngine* engine) {
							clear();
						}

						void SetDirectcomp(bool ss) {
							/*
							Dont allow setting if it was forced to 1,
							only thing that forces it is
							aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_MISSINGFUNCTIONS_ZERO_TOLERANCE
							check failure and it does it to prevent crashing.
							*/
							if (directcomp_forced) { return; }
							if (datahandlingid_key == common::DATAHANDLINGTYPE::HANDLE) {
								handlemode_directcomp = ss;

								if (handlemode_directcomp) {
									need_errorcheck_missing_functions = 0;
								} else {
									need_errorcheck_missing_functions = 1;
								}
							}
						}



						//handle input is void* that points at handle which is a void*
						//handle output is void* that points at handle which is a void*

						void StoreHandle(void** target, void* ptr_to_handle, asITypeInfo* typeinfo) {
							*target = ptr_to_handle;
							engine->AddRefScriptObject(*target, typeinfo);
						}
						void* StoreHandle2(void* ptr_to_handle, asITypeInfo* typeinfo) {
							void* result = *(void**)ptr_to_handle;
							engine->AddRefScriptObject(result, typeinfo);
							return result;
						}

						void BuildPrimunion(common::primunion& pu, void* inputvalue, const common::DATAHANDLINGTYPE& dht, const common::PRIMITIVE_TYPE& pt) {
							switch (dht) {
							case common::DATAHANDLINGTYPE::HANDLE:
							{
								pu.ptr = *(void**)inputvalue;
								break;
							}
							case common::DATAHANDLINGTYPE::OBJECT:
							{
								pu.ptr = inputvalue;
								break;
							}
							case common::DATAHANDLINGTYPE::STRING:
							{
								pu.ptr = inputvalue;
								break;
							}
							case common::DATAHANDLINGTYPE::PRIMITIVE:
							{
								switch (pt) {
								case common::PRIMITIVE_TYPE::INT8: { pu.i8 = *((config::t::int8*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::INT16: { pu.i16 = *((config::t::int16*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::INT32: { pu.i32 = *((config::t::int32*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::INT64: { pu.i64 = *((config::t::int64*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::UINT8: { pu.ui8 = *((config::t::uint8*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::UINT16: { pu.ui16 = *((config::t::uint16*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::UINT32: { pu.ui32 = *((config::t::uint32*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::UINT64: { pu.ui64 = *((config::t::uint64*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::FLOAT32: { pu.f32 = *((config::t::float32*)inputvalue); break; }
								case common::PRIMITIVE_TYPE::FLOAT64: { pu.f64 = *((config::t::float64*)inputvalue); break; }
								};
								break;
							}
							};
						}

						void store_Scriptany_to_Primunion(void* scriptvalue, common::primunion& pu, const common::DATAHANDLINGTYPE& dht, const common::PRIMITIVE_TYPE& pt, asITypeInfo* ot) {
							switch (dht) {
								case common::DATAHANDLINGTYPE::STRING:
								{
									pu.ptr = engine->CreateScriptObjectCopy(scriptvalue, ot);
									break;
								}
								case common::DATAHANDLINGTYPE::HANDLE:
								{
									scriptvalue = *(void**)scriptvalue;
									StoreHandle(&(pu.ptr), scriptvalue, ot);
									break;
								}
								case common::DATAHANDLINGTYPE::OBJECT:
								{
									pu.ptr = engine->CreateScriptObjectCopy(scriptvalue, ot);
									break;
								}
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									pu.From_voidptr_to_primitive(scriptvalue, pt);
									break;
								}
							};
						}

						static void* Scriptany_ref_from_Primunion(common::primunion& pu, const common::DATAHANDLINGTYPE& dht, const common::PRIMITIVE_TYPE& pt) {
							switch (dht) {
								case common::DATAHANDLINGTYPE::HANDLE: { return &(pu.ptr); }
								case common::DATAHANDLINGTYPE::OBJECT: { return pu.ptr; }
								case common::DATAHANDLINGTYPE::STRING: { return pu.ptr; }
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									switch (pt) {
										case common::PRIMITIVE_TYPE::INT8: { return &(pu.i8); }
										case common::PRIMITIVE_TYPE::INT16: { return &(pu.i16); }
										case common::PRIMITIVE_TYPE::INT32: { return &(pu.i32); }
										case common::PRIMITIVE_TYPE::INT64: { return &(pu.i64); }
										case common::PRIMITIVE_TYPE::UINT8: { return &(pu.ui8); }
										case common::PRIMITIVE_TYPE::UINT16: { return &(pu.ui16); }
										case common::PRIMITIVE_TYPE::UINT32: { return &(pu.ui32); }
										case common::PRIMITIVE_TYPE::UINT64: { return &(pu.ui64); }
										case common::PRIMITIVE_TYPE::FLOAT32: { return &(pu.f32); }
										case common::PRIMITIVE_TYPE::FLOAT64: { return &(pu.f64); }
									};
									break;
								}
							};
							return pu.ptr;
						}

						void DefaultConstructPrimunion(common::primunion& pu, const common::DATAHANDLINGTYPE& dht, const common::PRIMITIVE_TYPE& pt, asITypeInfo* ot) {
							switch (dht) {
								case common::DATAHANDLINGTYPE::HANDLE:
								{
									pu.ptr = nullptr;
									break;
								}
								case common::DATAHANDLINGTYPE::OBJECT:
								{
									pu.ptr = engine->CreateScriptObject(ot);
									break;
								}
								case common::DATAHANDLINGTYPE::STRING:
								{
									pu.ptr = engine->CreateScriptObject(ot);
									break;
								}
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									switch (pt) {
										case common::PRIMITIVE_TYPE::INT8: { pu.i8 = common::primunion_defaultvalue.i8; break; }
										case common::PRIMITIVE_TYPE::INT16: { pu.i16 = common::primunion_defaultvalue.i16; break; }
										case common::PRIMITIVE_TYPE::INT32: { pu.i32 = common::primunion_defaultvalue.i32; break; }
										case common::PRIMITIVE_TYPE::INT64: { pu.i64 = common::primunion_defaultvalue.i64; break; }
										case common::PRIMITIVE_TYPE::UINT8: { pu.ui8 = common::primunion_defaultvalue.ui8; break; }
										case common::PRIMITIVE_TYPE::UINT16: { pu.ui16 = common::primunion_defaultvalue.ui16; break; }
										case common::PRIMITIVE_TYPE::UINT32: { pu.ui32 = common::primunion_defaultvalue.ui32; break; }
										case common::PRIMITIVE_TYPE::UINT64: { pu.ui64 = common::primunion_defaultvalue.ui64; break; }
										case common::PRIMITIVE_TYPE::FLOAT32: { pu.f32 = common::primunion_defaultvalue.f32; break; }
										case common::PRIMITIVE_TYPE::FLOAT64: { pu.f64 = common::primunion_defaultvalue.f64; break; }
									};
									break;
								}
							};
						}

						static void* DefaultPrimunion(const common::DATAHANDLINGTYPE& dht, const common::PRIMITIVE_TYPE& pt) {
							switch (dht) {
								case common::DATAHANDLINGTYPE::HANDLE: { return &(common::primunion_defaultvalue.ptr); }
								case common::DATAHANDLINGTYPE::OBJECT: { return common::primunion_defaultvalue.ptr; }
								case common::DATAHANDLINGTYPE::STRING: { return common::primunion_defaultvalue.ptr; }
								case common::DATAHANDLINGTYPE::PRIMITIVE:{
									switch (pt) {
										case common::PRIMITIVE_TYPE::INT8: { return &(common::primunion_defaultvalue.i8); }
										case common::PRIMITIVE_TYPE::INT16: { return &(common::primunion_defaultvalue.i16); }
										case common::PRIMITIVE_TYPE::INT32: { return &(common::primunion_defaultvalue.i32); }
										case common::PRIMITIVE_TYPE::INT64: { return &(common::primunion_defaultvalue.i64); }
										case common::PRIMITIVE_TYPE::UINT8: { return &(common::primunion_defaultvalue.ui8); }
										case common::PRIMITIVE_TYPE::UINT16: { return &(common::primunion_defaultvalue.ui16); }
										case common::PRIMITIVE_TYPE::UINT32: { return &(common::primunion_defaultvalue.ui32); }
										case common::PRIMITIVE_TYPE::UINT64: { return &(common::primunion_defaultvalue.ui64); }
										case common::PRIMITIVE_TYPE::FLOAT32: { return &(common::primunion_defaultvalue.f32); }
										case common::PRIMITIVE_TYPE::FLOAT64: { return &(common::primunion_defaultvalue.f64); }
									};
									break;
								}
							};
							return &common::primunion_defaultvalue.ptr;
						}

						void clear() {
							safety_iteratorversion_Increment();

							if (datahandlingid_key != common::DATAHANDLINGTYPE::PRIMITIVE) {
								auto it = container.begin();
								auto itend = container.end();
								for (; it != itend; it++) {
									engine->ReleaseScriptObject((*it).first.ptr, typeinfo_key);
								}
							}
							if (datahandlingid_value != common::DATAHANDLINGTYPE::PRIMITIVE) {
								auto it = container.begin();
								auto itend = container.end();
								for (; it != itend; it++) {
									engine->ReleaseScriptObject((*it).second.ptr, typeinfo_value);
								}
							}

							container.clear();
						}
						bool empty() { return container.empty(); }
						config::t::sizetype size() { return (config::t::sizetype)(container.size()); }





						class Iterator : public aatc::container::shared::iterator_base {
						public:
							Containerbase* host;

							typename Containerbase::T_container_native::iterator it;
							typename Containerbase::T_container_native::iterator it_end;

							common::DATAHANDLINGTYPE datahandlingid_key;
							common::DATAHANDLINGTYPE datahandlingid_value;
							common::PRIMITIVE_TYPE primitiveid_key;
							common::PRIMITIVE_TYPE primitiveid_value;

							Iterator() {}
							Iterator(Containerbase* _host) :
								host(_host),
								it(),
								it_end()
							{
								Init();
							}
							Iterator(const Iterator& other) :
								iterator_base(other),

								host(other.host),
								it(other.it),
								it_end(other.it_end),

								datahandlingid_key(other.datahandlingid_key),
								datahandlingid_value(other.datahandlingid_value),
								primitiveid_key(other.primitiveid_key),
								primitiveid_value(other.primitiveid_value)
							{
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								safety_iteratorversion = other.safety_iteratorversion;
#endif
							}
							~Iterator() {}

							Iterator& operator=(const Iterator& other) {
								host = other.host;
								it = other.it;
								it_end = other.it_end;

								firstt = other.firstt;
								cont = other.cont;

								datahandlingid_key = other.datahandlingid_key;
								datahandlingid_value = other.datahandlingid_value;
								primitiveid_key = other.primitiveid_key;
								primitiveid_key = other.primitiveid_key;

#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								safety_iteratorversion = other.safety_iteratorversion;
#endif

								return *this;
							}

							static void static_constructor_default(asITypeInfo* typeinfo, void *memory) {
								new(memory)Iterator();
							}
							static void static_constructor_copy(asITypeInfo* typeinfo, Iterator* other, void *memory) {
								new(memory)Iterator(*other);
							}
							static void static_constructor_parentcontainer(asITypeInfo* typeinfo, Containerbase* host, void *memory) {
								new(memory)Iterator(host);
								host->refcount_Release();
							}

							void Init() {
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								safety_iteratorversion = host->safety_iteratorversion;
#endif

								if (host->empty()) {
									cont = 0;

									it = host->container.end();
									it_end = host->container.end();
								} else {
									//handlemode_key = (host->datahandlingid_key == common::DATAHANDLINGTYPE::HANDLE);
									//handlemode_value = (host->datahandlingid_value == common::DATAHANDLINGTYPE::HANDLE);

									datahandlingid_key = host->datahandlingid_key;
									datahandlingid_value = host->datahandlingid_value;
									primitiveid_key = host->primitiveid_key;
									primitiveid_value = host->primitiveid_value;

									it = host->container.begin();
									it_end = host->container.end();
									cont = 1;
								}
							}

							//combine end check and continuation into one monster
							bool Next() {
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (safety_iteratorversion != host->safety_iteratorversion) {
									common::errorprint::iterator::container_modified();
									return 0;
								}
#endif

								if (firstt) {
									if (cont) {//all is well
										firstt = 0;
										return 1;
									} else {//cont set to 0 in constructor because container is empty
										return 0;
									}
								} else {
									it++;
									//if (it == host->end()){
									if (it == it_end) {
										cont = 0;
										return 0;
									} else {
										return 1;
									}
								}
							}

							const void* Current_key_get() {
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (safety_iteratorversion != host->safety_iteratorversion) {
									common::errorprint::iterator::container_modified();
									return nullptr;
								}
#endif

								switch (datahandlingid_key) {
								case common::DATAHANDLINGTYPE::HANDLE: { return &((*it).first.ptr); }//return pointer to handle
								case common::DATAHANDLINGTYPE::OBJECT: { return (*it).first.ptr; }//return copy of pointer to object
								case common::DATAHANDLINGTYPE::STRING: { return (*it).first.ptr; }//return copy of pointer to object
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									switch (primitiveid_key) {
									case common::PRIMITIVE_TYPE::INT8: { return &((*it).first.i8); }
									case common::PRIMITIVE_TYPE::INT16: { return &((*it).first.i16); }
									case common::PRIMITIVE_TYPE::INT32: { return &((*it).first.i32); }
									case common::PRIMITIVE_TYPE::INT64: { return &((*it).first.i64); }
									case common::PRIMITIVE_TYPE::UINT8: { return &((*it).first.ui8); }
									case common::PRIMITIVE_TYPE::UINT16: { return &((*it).first.ui16); }
									case common::PRIMITIVE_TYPE::UINT32: { return &((*it).first.ui32); }
									case common::PRIMITIVE_TYPE::UINT64: { return &((*it).first.ui64); }
									case common::PRIMITIVE_TYPE::FLOAT32: { return &((*it).first.f32); }
									case common::PRIMITIVE_TYPE::FLOAT64: { return &((*it).first.f64); }
									};
								}
								};
								return nullptr;//should never happen, stops compiler warning
							}

							const void* Current_value_get() {
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (safety_iteratorversion != host->safety_iteratorversion) {
									common::errorprint::iterator::container_modified();
									return nullptr;
								}
#endif

								switch (datahandlingid_value) {
								case common::DATAHANDLINGTYPE::HANDLE: { return &((*it).second.ptr); }//return pointer to handle
								case common::DATAHANDLINGTYPE::OBJECT: { return (*it).second.ptr; }//return copy of pointer to object
								case common::DATAHANDLINGTYPE::STRING: { return (*it).second.ptr; }//return copy of pointer to object
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									switch (primitiveid_key) {
									case common::PRIMITIVE_TYPE::INT8: { return &((*it).second.i8); }
									case common::PRIMITIVE_TYPE::INT16: { return &((*it).second.i16); }
									case common::PRIMITIVE_TYPE::INT32: { return &((*it).second.i32); }
									case common::PRIMITIVE_TYPE::INT64: { return &((*it).second.i64); }
									case common::PRIMITIVE_TYPE::UINT8: { return &((*it).second.ui8); }
									case common::PRIMITIVE_TYPE::UINT16: { return &((*it).second.ui16); }
									case common::PRIMITIVE_TYPE::UINT32: { return &((*it).second.ui32); }
									case common::PRIMITIVE_TYPE::UINT64: { return &((*it).second.ui64); }
									case common::PRIMITIVE_TYPE::FLOAT32: { return &((*it).second.f32); }
									case common::PRIMITIVE_TYPE::FLOAT64: { return &((*it).second.f64); }
									};
								}
								};
								return nullptr;//should never happen, stops compiler warning
							}
							void Current_value_set(void* value) {
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (safety_iteratorversion != host->safety_iteratorversion) {
									common::errorprint::iterator::container_modified();
									return;
								}
#endif

								switch (datahandlingid_value) {
								case common::DATAHANDLINGTYPE::HANDLE:
								{
									void** it_inner = &((*it).second.ptr);//convenience

									if (*it_inner) {
										host->engine->ReleaseScriptObject(*it_inner, host->typeinfo_value);
									}
									if (value) {
										*it_inner = host->StoreHandle2(value, host->typeinfo_value);
									} else {
										*it_inner = nullptr;
									}
									break;
									}
								case common::DATAHANDLINGTYPE::OBJECT:
								case common::DATAHANDLINGTYPE::STRING:
								{
									void** it_inner = &((*it).second.ptr);//convenience
									host->engine->ReleaseScriptObject(*it_inner, host->typeinfo_value);
									*it_inner = host->engine->CreateScriptObjectCopy(value, host->typeinfo_value);
									break;
								}
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									switch (primitiveid_value) {
									case common::PRIMITIVE_TYPE::INT8: { ((*it).second.i8) = *((config::t::int8*)value); break; }
									case common::PRIMITIVE_TYPE::INT16: { ((*it).second.i16) = *((config::t::int16*)value); break; }
									case common::PRIMITIVE_TYPE::INT32: { ((*it).second.i32) = *((config::t::int32*)value); break; }
									case common::PRIMITIVE_TYPE::INT64: { ((*it).second.i64) = *((config::t::int64*)value); break; }

									case common::PRIMITIVE_TYPE::UINT8: { ((*it).second.ui8) = *((config::t::uint8*)value); break; }
									case common::PRIMITIVE_TYPE::UINT16: { ((*it).second.ui16) = *((config::t::uint16*)value); break; }
									case common::PRIMITIVE_TYPE::UINT32: { ((*it).second.ui32) = *((config::t::uint32*)value); break; }
									case common::PRIMITIVE_TYPE::UINT64: { ((*it).second.ui64) = *((config::t::uint64*)value); break; }

									case common::PRIMITIVE_TYPE::FLOAT32: { ((*it).second.f32) = *((config::t::float32*)value); break; }
									case common::PRIMITIVE_TYPE::FLOAT64: { ((*it).second.f64) = *((config::t::float64*)value); break; }
									};
									break;
								}
								};
								}


							const void* Current_key_const() {
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (safety_iteratorversion != host->safety_iteratorversion) {
									common::errorprint::iterator::container_modified();
									return nullptr;
								}
#endif

								switch (datahandlingid_key) {
								case common::DATAHANDLINGTYPE::HANDLE: { return &((*it).first.ptr); }//return pointer to handle
								case common::DATAHANDLINGTYPE::OBJECT: { return (*it).first.ptr; }//return copy of pointer to object
								case common::DATAHANDLINGTYPE::STRING: { return (*it).first.ptr; }//return copy of pointer to object
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									switch (primitiveid_key) {
									case common::PRIMITIVE_TYPE::INT8: { return &((*it).first.i8); }
									case common::PRIMITIVE_TYPE::INT16: { return &((*it).first.i16); }
									case common::PRIMITIVE_TYPE::INT32: { return &((*it).first.i32); }
									case common::PRIMITIVE_TYPE::INT64: { return &((*it).first.i64); }
									case common::PRIMITIVE_TYPE::UINT8: { return &((*it).first.ui8); }
									case common::PRIMITIVE_TYPE::UINT16: { return &((*it).first.ui16); }
									case common::PRIMITIVE_TYPE::UINT32: { return &((*it).first.ui32); }
									case common::PRIMITIVE_TYPE::UINT64: { return &((*it).first.ui64); }
									case common::PRIMITIVE_TYPE::FLOAT32: { return &((*it).first.f32); }
									case common::PRIMITIVE_TYPE::FLOAT64: { return &((*it).first.f64); }
									};
								}
								};
								return nullptr;//should never happen, stops compiler warning
							}

							void* Current_value() {
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (safety_iteratorversion != host->safety_iteratorversion) {
									common::errorprint::iterator::container_modified();
									return nullptr;
								}
#endif

								switch (datahandlingid_value) {
								case common::DATAHANDLINGTYPE::HANDLE: { return &((*it).second.ptr); }//return pointer to handle
								case common::DATAHANDLINGTYPE::OBJECT: { return (*it).second.ptr; }//return copy of pointer to object
								case common::DATAHANDLINGTYPE::STRING: { return (*it).second.ptr; }//return copy of pointer to object
								case common::DATAHANDLINGTYPE::PRIMITIVE:
								{
									switch (primitiveid_value) {
									case common::PRIMITIVE_TYPE::INT8: { return &((*it).second.i8); }
									case common::PRIMITIVE_TYPE::INT16: { return &((*it).second.i16); }
									case common::PRIMITIVE_TYPE::INT32: { return &((*it).second.i32); }
									case common::PRIMITIVE_TYPE::INT64: { return &((*it).second.i64); }
									case common::PRIMITIVE_TYPE::UINT8: { return &((*it).second.ui8); }
									case common::PRIMITIVE_TYPE::UINT16: { return &((*it).second.ui16); }
									case common::PRIMITIVE_TYPE::UINT32: { return &((*it).second.ui32); }
									case common::PRIMITIVE_TYPE::UINT64: { return &((*it).second.ui64); }
									case common::PRIMITIVE_TYPE::FLOAT32: { return &((*it).second.f32); }
									case common::PRIMITIVE_TYPE::FLOAT64: { return &((*it).second.f64); }
									};
								}
								};
								return nullptr;//should never happen, stops compiler warning
							}

							/*
							Using this in script should be faster than (it == container.end()) because container.end() creates an object
							*/
							bool IsEnd() {
								return it == it_end;
							}
							void SetToEnd() {
								firstt = 0;
								cont = 0;
								it = it_end;
							}
							bool IsValid() {
#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								return safety_iteratorversion == host->safety_iteratorversion;
#else
								return 1;
#endif
							}

							bool operator==(const Iterator& other) {
								return it == other.it;
							}

							static void Register(common::RegistrationState& rs) {
								rs.error = rs.engine->RegisterObjectType(rs.n_iterator_class_T, sizeof(Iterator), asOBJ_VALUE | asOBJ_TEMPLATE | asGetTypeTraits<Iterator>()); assert(rs.error >= 0);

								rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, "void f(int&in)", asFunctionPtr(static_constructor_default), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);
								rs.Format("void f(int&in,const %s &in)", rs.n_iterator_T);
								rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, rs.textbuf, asFunctionPtr(static_constructor_copy), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);
								rs.Format("void f(int&in,%s@)", rs.n_container_T);
								rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, rs.textbuf, asFunctionPtr(static_constructor_parentcontainer), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);

								rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(aatc::common::reghelp::generic_destructor<Iterator>), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);



								rs.Format("const T_key& %s()", config::scriptname::method::iterator::access_function_key);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, Current_key_const), asCALL_THISCALL); assert(rs.error >= 0);
								rs.Format("T_value& %s()", config::scriptname::method::iterator::access_function_value);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, Current_value), asCALL_THISCALL); assert(rs.error >= 0);

								rs.Format("const T_key& get_%s()", config::scriptname::method::iterator::access_property_key);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, Current_key_get), asCALL_THISCALL); assert(rs.error >= 0);

								rs.Format("T_value& get_%s()", config::scriptname::method::iterator::access_property_value);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, Current_value_get), asCALL_THISCALL); assert(rs.error >= 0);
								rs.Format("void set_%s(const T_value &in)", config::scriptname::method::iterator::access_property_value);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, Current_value_set), asCALL_THISCALL); assert(rs.error >= 0);

								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, "bool next()", asMETHOD(Iterator, Next), asCALL_THISCALL); assert(rs.error >= 0);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, "bool opPreInc()", asMETHOD(Iterator, Next), asCALL_THISCALL); assert(rs.error >= 0);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, "bool opPostInc()", asMETHOD(Iterator, Next), asCALL_THISCALL); assert(rs.error >= 0);

								rs.Format("%s& opAssign(const %s &in)", rs.n_iterator_T, rs.n_iterator_T);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, operator=), asCALL_THISCALL); assert(rs.error >= 0);

								rs.Format("bool opEquals(const %s &in)", rs.n_iterator_T);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, operator==), asCALL_THISCALL); assert(rs.error >= 0);

								rs.Format("bool %s()", config::scriptname::method::iterator::is_end);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, IsEnd), asCALL_THISCALL); assert(rs.error >= 0);

								rs.Format("bool %s()", config::scriptname::method::iterator::is_valid);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(Iterator, IsValid), asCALL_THISCALL); assert(rs.error >= 0);
							}
						};



						Iterator begin() {
							return Iterator(this);
						}
						Iterator end() {
							Iterator result(this);
							result.SetToEnd();
							return result;
						}



					};





					template<typename T_container> void register_containerbase(common::RegistrationState& rs) {
						common::RegistrationState::Format_static(rs.n_container, common::RegistrationState::bufsize, "%s", T_container::container_tags::scriptname_container);
						common::RegistrationState::Format_static(rs.n_container_T, common::RegistrationState::bufsize, "%s<T_key, T_value>", T_container::container_tags::scriptname_container);
						common::RegistrationState::Format_static(rs.n_container_class_T, common::RegistrationState::bufsize, "%s<class T_key,class T_value>", T_container::container_tags::scriptname_container);
						common::RegistrationState::Format_static(rs.n_iterator, common::RegistrationState::bufsize, "%s%s", T_container::container_tags::scriptname_container, config::scriptname::iterator_suffix);
						common::RegistrationState::Format_static(rs.n_iterator_T, common::RegistrationState::bufsize, "%s<T_key, T_value>", rs.n_iterator);
						common::RegistrationState::Format_static(rs.n_iterator_class_T, common::RegistrationState::bufsize, "%s<class T_key,class T_value>", rs.n_iterator);



						rs.error = rs.engine->RegisterObjectType(rs.n_container_class_T, 0, asOBJ_REF | asOBJ_GC | asOBJ_TEMPLATE); assert(rs.error >= 0);

						rs.Format("%s@ f(int&in)", rs.n_container_T);
						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_FACTORY, rs.textbuf, asFUNCTION(shared::asglue::Factory_default<T_container>), asCALL_CDECL); assert(rs.error >= 0);
						rs.Format("%s@ f(int&in,%s@)", rs.n_container_T, rs.n_container_T);
						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_FACTORY, rs.textbuf, asFUNCTION(shared::asglue::Factory_copy<T_container>), asCALL_CDECL); assert(rs.error >= 0);
						rs.Format("%s& opAssign(%s@)", rs.n_container_T, rs.n_container_T);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(shared::asglue::Assign<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_TEMPLATE_CALLBACK, "bool f(int&in, bool&out)", asFUNCTION(aatc::common::templatecallback_func::map), asCALL_CDECL); assert(rs.error >= 0);

						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_ADDREF, "void f()", asMETHOD(T_container, refcount_Add), asCALL_THISCALL); assert(rs.error >= 0);
						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_RELEASE, "void f()", asMETHOD(T_container, refcount_Release), asCALL_THISCALL); assert(rs.error >= 0);
						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_SETGCFLAG, "void f()", asMETHODPR(T_container, SetGCFlag, (), void), asCALL_THISCALL); assert(rs.error >= 0);
						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_GETGCFLAG, "bool f()", asMETHODPR(T_container, GetGCFlag, (), bool), asCALL_THISCALL); assert(rs.error >= 0);
						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_GETREFCOUNT, "int f()", asMETHODPR(T_container, GetRefCount, (), int), asCALL_THISCALL); assert(rs.error >= 0);
						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_ENUMREFS, "void f(int&in)", asMETHODPR(T_container, EnumReferences, (asIScriptEngine*), void), asCALL_THISCALL); assert(rs.error >= 0);
						rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_RELEASEREFS, "void f(int&in)", asMETHODPR(T_container, ReleaseAllReferences, (asIScriptEngine*), void), asCALL_THISCALL); assert(rs.error >= 0);



						rs.Format("void %s(bool)", config::scriptname::method::container::set_directcomp);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, SetDirectcomp), asCALL_THISCALL); assert(rs.error >= 0);

						rs.Format("void %s()", config::scriptname::method::container::clear);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, clear), asCALL_THISCALL); assert(rs.error >= 0);
						rs.Format("bool %s()", config::scriptname::method::container::empty);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, empty), asCALL_THISCALL); assert(rs.error >= 0);
						rs.Format("%s %s()", config::scriptname::t::size, config::scriptname::method::container::size);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, size), asCALL_THISCALL); assert(rs.error >= 0);

						T_container::Iterator::Register(rs);

						rs.Format("%s %s()", rs.n_iterator_T, config::scriptname::method::container::begin);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, begin), asCALL_THISCALL); assert(rs.error >= 0);

						rs.Format("%s %s()", rs.n_iterator_T, config::scriptname::method::container::end);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, end), asCALL_THISCALL); assert(rs.error >= 0);
					};





				};//namespace shared
			};//namespace templated
		};//namespace mapped
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif