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


#ifndef _includedh_aatc_container_templated_shared
#define _includedh_aatc_container_templated_shared



#include "aatc_common.hpp"
#include "aatc_enginestorage.hpp"
#include "aatc_container_shared.hpp"
#include "aatc_container_listing.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
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
						Basic(asIScriptEngine* engine, aatc::container::shared::containerfunctor::Settings* settings) {}
					};

					template<
						typename T_container,
						typename T_param1
					> class Singleparam : public T_container {
					public:
						Singleparam(asIScriptEngine* _engine, aatc::container::shared::containerfunctor::Settings* settings) :
							T_container(T_param1(_engine, settings))
						{}
					};

					template<
						typename T_container,
						typename T_param1,
						typename T_param2,
						std::size_t default_bucket_count = config::detail::DEFAULT_CONTAINER_UNORDERED_SET_DEFAULTBUCKETCOUNT
					> class Hashed : public T_container {
					public:
						Hashed(asIScriptEngine* _engine, aatc::container::shared::containerfunctor::Settings* settings) :
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
					typename bcw = base_container_wrapper::Basic<T_container>>
				class Containerbase :
					public container::shared::container_basicbase,
					public common::basetype_refcounted_GC,
					public container::shared::containerfunctor::Settings
				{
				public:
					typedef T_container T_container_native;
					typedef typename T_container_native::iterator T_iterator_native;
					typedef typename T_container_native::const_iterator T_iterator_native_const;

					static const int containertype_id = _containertype_id;
					typedef T_container_tags container_tags;



					bcw container;

					enginestorage::engine_level_storage* els;

					asITypeInfo* typeinfo_container;
					asITypeInfo* objtype_content;
					config::t::astypeid astypeid_container;
					config::t::astypeid astypeid_content;
					asDWORD typeflags_container;
					asDWORD typeflags_content;

					bool handlemode_needref;

					aatc::common::container_operations_bitmask_type missing_functions;

					bool directcomp_forced;
					
					Containerbase(asIScriptEngine* _engine, asITypeInfo* _typeinfo) :
						aatc::container::shared::container_basicbase(_engine),
						container(_engine, this),
						typeinfo_container(_typeinfo),
						directcomp_forced(0)
					{
						handlemode_directcomp = config::DEFAULT_HANDLEMODE_DIRECTCOMP;

						objtype_content = typeinfo_container->GetSubType();

						astypeid_container = typeinfo_container->GetTypeId();
						astypeid_content = typeinfo_container->GetSubTypeId();

						typeflags_container = typeinfo_container->GetFlags();
						typeflags_content = objtype_content->GetFlags();

						//problem_nofunc_eq_or_cmp = 0;
						//problem_nofunc_cmp = 0;

						els = enginestorage::Get_ELS(engine);
						enginestorage::containertype_specific_storage* ctss = els->GetContainerTypeSpecificStorage(containertype_id);

						if (astypeid_content & asTYPEID_OBJHANDLE) {
							handlemode = 1;
							handlemode_needref = 1;
							if (typeflags_content & asOBJ_NOCOUNT) {
								handlemode_needref = 0;
							}
						} else {
							handlemode = 0;
							handlemode_directcomp = 0;
						}

						aatc::enginestorage::template_specific_storage* tss = ctss->GetTemplateSpecificStorage(astypeid_content);
						func_equals = tss->func_equals;
						func_cmp = tss->func_cmp;
						func_hash = tss->func_hash;

						missing_functions = tss->missing_functions;

						#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_MISSINGFUNCTIONS_ZERO_TOLERANCE
								if (missing_functions) {
									bool bad = 1;

						#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_MISSINGFUNCTIONS_ZERO_TOLERANCE_USE_DIRECTCOMP
									if (handlemode) {//force handlemode directcomp if anything is missing
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

						engine->NotifyGarbageCollectorOfNewObject(this, typeinfo_container);
					}

					virtual ~Containerbase() {
						clear();
					}

					Containerbase& operator=(const Containerbase& other) {
						safety_iteratorversion_Increment();

						clear();//will delete script objects or decrement handles

						container.operator=(other.container);

						if (handlemode) {//increment refs for newly created handles
							for (auto it = container.begin(); it != container.end(); it++) {
								engine->AddRefScriptObject(*it, objtype_content);
							}
						} else {//value objects must be copied
								/*
								TODO: Safety for associative containers (set,unordered_set).

								Copying script objects will call script functions and custom
								script functions might not perfectly copy whatever is keeping
								the associative container sorted, thus sorting might explode.

								Implement some flag to tell the container that your custom
								script copy function is indeed safe. If the flag is set, use
								simple copy like this, otherwise copy all objects first and
								insert to the new container after copy.
								*/

							T_iterator_native it = container.begin();
							T_iterator_native it_other = const_cast<Containerbase&>(other).container.begin();
							T_iterator_native it_end = container.end();

							for (; it != it_end;) {
								void*& iii = const_cast<void*&>(*it);
								void*& iii_other = const_cast<void*&>(*it_other);

								iii = engine->CreateScriptObjectCopy(iii_other, objtype_content);

								it++;
								it_other++;
							}
						}

						return *this;
					}

					void SetDirectcomp(bool ss) {
						if (directcomp_forced) { return; }
						handlemode_directcomp = ss;
					}

					//handle input is void* that points at handle which is a void*
					//handle output is void* that points at handle which is a void*
					void StoreHandle(void** target, void* ptr_to_handle) {
						*target = *(void**)ptr_to_handle;
						engine->AddRefScriptObject(*target, objtype_content);
					}
					void* StoreHandle2(void* ptr_to_handle) {
						void* result = *(void**)ptr_to_handle;
						engine->AddRefScriptObject(result, objtype_content);
						return result;
					}
					void ReleaseHandle(void* handle) {
						engine->ReleaseScriptObject(handle, objtype_content);
					}

					bool empty() {return container.empty();}
					config::t::sizetype size() { return (config::t::sizetype)(container.size()); }

					void clear() {
						safety_iteratorversion_Increment();

						T_iterator_native it = container.begin();
						T_iterator_native itend = container.end();
						if (handlemode) {
							for (; it != itend; it++) {
								ReleaseHandle(*it);
							}
						} else {
							for (; it != itend; it++) {
								engine->ReleaseScriptObject(*it, objtype_content);
							}
						}
						container.clear();
					}

					void EnumReferences(asIScriptEngine* engine) {
						if (astypeid_content & asTYPEID_MASK_OBJECT) {//dont do this for primitives
							T_iterator_native it = container.begin();
							T_iterator_native itend = container.end();
							for (; it != itend; it++) {
								engine->GCEnumCallback(*it);
							}
						}
					}
					void ReleaseAllReferences(asIScriptEngine* engine) {
						clear();
					}





					class Iterator : public aatc::container::shared::iterator_base {
					public:
						Containerbase* host;

						typename Containerbase::T_container_native::iterator it;
						typename Containerbase::T_container_native::iterator it_end;

						bool handlemode;

						Iterator() :
							it(),
							it_end()
						{}
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

							handlemode(other.handlemode)
						{
							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								safety_iteratorversion = other.safety_iteratorversion;
							#endif
						}
						~Iterator() {}

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
						//static void static_constructor_copy(asITypeInfo* typeinfo, const aatc_iterator& other, void *memory){
						//	new(memory)aatc_iterator(other);
						//}

						Iterator& operator=(const Iterator& other) {
							host = other.host;
							it = other.it;
							it_end = other.it_end;

							firstt = other.firstt;
							cont = other.cont;

							handlemode = other.handlemode;

							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								safety_iteratorversion = other.safety_iteratorversion;
							#endif

							return *this;
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
								handlemode = host->handlemode;

								it = host->container.begin();
								it_end = host->container.end();
								cont = 1;
							}
						}

						//combine end check and continuation into one monster
						bool Next() {
							if (!IsValid()) {
								common::errorprint::iterator::container_modified();
								return 0;
							}

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
									return 0;
								} else {
									return 1;
								}
							}
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



				namespace iterator_method {
					template<typename T_iterator> const void* current_get(T_iterator* thiis) {
						if (!thiis->IsValid()) {
							common::errorprint::iterator::container_modified();
							return nullptr;
						}

						if (thiis->handlemode) {
							return &(*(thiis->it));//return pointer to handle
						} else {
							return *(thiis->it);//return copy of pointer to object
						}
					}
					template<typename T_iterator> void current_set(T_iterator* thiis, void* value) {
						if (!thiis->IsValid()) {
							common::errorprint::iterator::container_modified();
							return;
						}

						if (thiis->handlemode) {
							if (*(thiis->it)) {
								thiis->host->engine->ReleaseScriptObject(*(thiis->it), thiis->host->objtype_content);
							}
							if (value) {
								*(thiis->it) = thiis->host->StoreHandle2(value);
							} else {
								*(thiis->it) = nullptr;
							}
						} else {
							thiis->host->engine->ReleaseScriptObject(*(thiis->it), thiis->host->objtype_content);
							*(thiis->it) = thiis->host->engine->CreateScriptObjectCopy(value, thiis->host->objtype_content);
						}
					}

					template<typename T_iterator> void* current(T_iterator* thiis) {
						if (!thiis->IsValid()) {
							common::errorprint::iterator::container_modified();
							return nullptr;
						}

						if (thiis->handlemode) {
							return &(*(thiis->it));//return pointer to handle
						} else {
							return *(thiis->it);//return copy of pointer to object
						}
					}

					template<typename T_iterator> const void* current_const(T_iterator* thiis) {
						if (!thiis->IsValid()) {
							common::errorprint::iterator::container_modified();
							return nullptr;
						}

						if (thiis->handlemode) {
							return &(*(thiis->it));//return pointer to handle
						} else {
							return *(thiis->it);//return copy of pointer to object
						}
					}
				}//namespace iterator_method



				namespace detail {
					namespace register_iterator_method {



						template<typename T_iterator, typename T_tag_need_const> struct current {};
						template<typename T_iterator> struct current<T_iterator, container::shared::tag::iterator_access::access_is_mutable> {
							void operator()(common::RegistrationState& rs) const{
								rs.Format("T& %s()", config::scriptname::method::iterator::access_function);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current<T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

								rs.Format("T& get_%s()", config::scriptname::method::iterator::access_property);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current_get<T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
								rs.Format("void set_%s(const T &in)", config::scriptname::method::iterator::access_property);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current_set<T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
							}
						};
						template<typename T_iterator> struct current<T_iterator, container::shared::tag::iterator_access::access_is_const> {
							void operator()(common::RegistrationState& rs) const {
								rs.Format("const T& %s()", config::scriptname::method::iterator::access_function);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current_const<T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

								rs.Format("const T& get_%s()", config::scriptname::method::iterator::access_property);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current_get<T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
							}
						};



					}//namespace register_iterator_method
				}//namespace detail



				template<typename T_container, typename T_iterator> void register_iterator(common::RegistrationState& rs) {
					typedef typename T_container::container_tags container_tags;
					typedef typename container_tags::iterator_access container_tags__iterator_access;

					rs.error = rs.engine->RegisterObjectType(rs.n_iterator_class_T, sizeof(T_iterator), asOBJ_VALUE | asOBJ_TEMPLATE | asGetTypeTraits<T_iterator>()); assert(rs.error >= 0);

					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, "void f(int&in)", asFunctionPtr(T_iterator::static_constructor_default), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);
					rs.Format("void f(int&in,const %s &in)", rs.n_iterator_T);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, rs.textbuf, asFunctionPtr(T_iterator::static_constructor_copy), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);
					rs.Format("void f(int&in,%s@)", rs.n_container_T);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, rs.textbuf, asFunctionPtr(T_iterator::static_constructor_parentcontainer), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);

					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(aatc::common::reghelp::generic_destructor<T_iterator>), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);

					detail::register_iterator_method::current<T_iterator, container_tags__iterator_access> register_method_current; register_method_current(rs);

					rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, "bool next()", asMETHOD(T_iterator, Next), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, "bool opPreInc()", asMETHOD(T_iterator, Next), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, "bool opPostInc()", asMETHOD(T_iterator, Next), asCALL_THISCALL); assert(rs.error >= 0);

					rs.Format("%s& opAssign(const %s &in)", rs.n_iterator_T, rs.n_iterator_T);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(T_iterator, operator=), asCALL_THISCALL); assert(rs.error >= 0);

					rs.Format("bool opEquals(const %s &in)", rs.n_iterator_T);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(T_iterator, operator==), asCALL_THISCALL); assert(rs.error >= 0);

					rs.Format("bool %s()", config::scriptname::method::iterator::is_end);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(T_iterator, IsEnd), asCALL_THISCALL); assert(rs.error >= 0);

					rs.Format("bool %s()", config::scriptname::method::iterator::is_valid);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asMETHOD(T_iterator, IsValid), asCALL_THISCALL); assert(rs.error >= 0);
				}



				template<typename T_container> void register_containerbase(common::RegistrationState& rs) {
					typedef typename T_container::Iterator T_iterator;

					common::RegistrationState::Format_static(rs.n_container, common::RegistrationState::bufsize, "%s", T_container::container_tags::scriptname_container);
					common::RegistrationState::Format_static(rs.n_container_T, common::RegistrationState::bufsize, "%s<T>", T_container::container_tags::scriptname_container);
					common::RegistrationState::Format_static(rs.n_container_class_T, common::RegistrationState::bufsize, "%s<class T>", T_container::container_tags::scriptname_container);
					common::RegistrationState::Format_static(rs.n_iterator, common::RegistrationState::bufsize, "%s%s", T_container::container_tags::scriptname_container, config::scriptname::iterator_suffix);
					common::RegistrationState::Format_static(rs.n_iterator_T, common::RegistrationState::bufsize, "%s<T>", rs.n_iterator);
					common::RegistrationState::Format_static(rs.n_iterator_class_T, common::RegistrationState::bufsize, "%s<class T>", rs.n_iterator);

					rs.error = rs.engine->RegisterObjectType(rs.n_container_class_T, 0, asOBJ_REF | asOBJ_GC | asOBJ_TEMPLATE); assert(rs.error >= 0);

					rs.Format("%s@ f(int&in)", rs.n_container_T);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_FACTORY, rs.textbuf, asFUNCTION(shared::asglue::Factory_default<T_container>), asCALL_CDECL); assert(rs.error >= 0);
					rs.Format("%s@ f(int&in,%s@)", rs.n_container_T, rs.n_container_T);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_FACTORY, rs.textbuf, asFUNCTION(shared::asglue::Factory_copy<T_container>), asCALL_CDECL); assert(rs.error >= 0);
					rs.Format("%s& opAssign(%s@)", rs.n_container_T, rs.n_container_T);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(shared::asglue::Assign<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_ADDREF, "void f()", asMETHOD(T_container, refcount_Add), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_RELEASE, "void f()", asMETHOD(T_container, refcount_Release), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_SETGCFLAG, "void f()", asMETHODPR(T_container, SetGCFlag, (), void), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_GETGCFLAG, "bool f()", asMETHODPR(T_container, GetGCFlag, (), bool), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_GETREFCOUNT, "int f()", asMETHODPR(T_container, GetRefCount, (), int), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_ENUMREFS, "void f(int&in)", asMETHODPR(T_container, EnumReferences, (asIScriptEngine*), void), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_RELEASEREFS, "void f(int&in)", asMETHODPR(T_container, ReleaseAllReferences, (asIScriptEngine*), void), asCALL_THISCALL); assert(rs.error >= 0);


					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_TEMPLATE_CALLBACK, "bool f(int&in, bool&out)", asFUNCTION(aatc::common::templatecallback_func::templated_singleparam), asCALL_CDECL); assert(rs.error >= 0);

					rs.Format("void %s(bool)", config::scriptname::method::container::set_directcomp);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, SetDirectcomp), asCALL_THISCALL); assert(rs.error >= 0);

					rs.Format("void %s()", config::scriptname::method::container::clear);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, clear), asCALL_THISCALL); assert(rs.error >= 0);
					rs.Format("bool %s()", config::scriptname::method::container::empty);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, empty), asCALL_THISCALL); assert(rs.error >= 0);
					rs.Format("%s %s()", config::scriptname::t::size, config::scriptname::method::container::size);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, size), asCALL_THISCALL); assert(rs.error >= 0);

					register_iterator<T_container, T_iterator>(rs);

					rs.Format("%s %s()", rs.n_iterator_T, config::scriptname::method::container::begin);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, begin), asCALL_THISCALL); assert(rs.error >= 0);

					rs.Format("%s %s()", rs.n_iterator_T, config::scriptname::method::container::end);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container, end), asCALL_THISCALL); assert(rs.error >= 0);
				};



			};//namespace shared
		};//namespace templated
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif