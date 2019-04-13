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


#ifndef _includedh_aatc_container_tempspec_shared
#define _includedh_aatc_container_tempspec_shared



#include "aatc_common.hpp"
#include "aatc_enginestorage.hpp"
#include "aatc_container_shared.hpp"
#include "aatc_container_listing.hpp"

#include "aatc_serializer.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace tempspec {
			namespace shared {



				namespace factory {
					template<typename T_container> T_container* Factory_default() {
						return new T_container();
					}
					template<typename T_container> T_container* Factory_copy(const T_container& other) {
						return new T_container(other);
					}
				}
				namespace asglue {
					template<typename T_container> T_container* Factory_default() {
						return factory::Factory_default<T_container>();
					}
					template<typename T_container> T_container* Factory_copy(T_container* other) {
						T_container* result = factory::Factory_copy<T_container>(*other);
						other->refcount_Release();
						return result;
					}
					template<typename T_container> T_container& Assign(T_container* t, T_container* other) {
						*t = *other;
						other->refcount_Release();
						return *t;
					}
				}



				template<
					typename _T_container,
					typename _T_content,
					int _containertype_id,
					typename T_container_tags = aatc::container::shared::tagbase>
				class Containerbase :
					public container::shared::container_basicbase,
					public common::basetype_refcounted {
				public:
					typedef _T_container T_container_native;
					typedef _T_content T_content;
					typedef typename T_container_native::iterator T_iterator_native;
					typedef typename T_container_native::const_iterator T_iterator_native_const;

					static const int containertype_id = _containertype_id;
					typedef T_container_tags container_tags;



					T_container_native container;

					//used to return something when script exceptions happen and the proper result cannot be returned
					static T_content defaultvalue;

					//used for error messages to retrieve names without sacrificing runtime performance while errors dont happen
					static std::string staticname_container;
					static std::string staticname_content;

					Containerbase():
						container_basicbase(nullptr)
					{
						auto* ctx = asGetActiveContext();
						if (ctx) { engine = ctx->GetEngine(); }
					}
					Containerbase(const Containerbase& other) :
						container_basicbase(nullptr),
						container(other.container)
					{
						engine = other.engine;
					}



					Containerbase& operator=(const Containerbase& other) {
						safety_iteratorversion_Increment();
						container.operator=(other.container);
						return *this;
					}

					void clear() {
						container.clear();
						safety_iteratorversion_Increment();
					}
					bool empty() { return container.empty(); }
					config::t::sizetype size() { return (config::t::sizetype)(container.size()); }





					class Iterator : public aatc::container::shared::iterator_base {
					public:
						Containerbase* host;

						T_iterator_native it;
						T_iterator_native it_end;

						Iterator() :
							it(),
							it_end()
						{}
						Iterator(Containerbase* host) :
							host(host),
							it(),
							it_end()
						{
							Init();
						}
						Iterator(const Iterator& other) :
							iterator_base(other),

							host(other.host),
							it(other.it),
							it_end(other.it_end)
						{
							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								safety_iteratorversion = other.safety_iteratorversion;
							#endif
						}
						~Iterator() {}

						static void static_constructor_parentcontainer(Containerbase* host, void *memory) {
							new(memory)Iterator(host);
							host->refcount_Release();
						}

						Iterator& operator=(const Iterator& other) {
							host = other.host;
							it = other.it;
							it_end = other.it_end;

							firstt = other.firstt;
							cont = other.cont;

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



				template<typename T_container, typename T_content, int _containertype_id, typename T_container_tags> T_content Containerbase<T_container, T_content, _containertype_id, T_container_tags>::defaultvalue = T_content();
				template<typename T_container, typename T_content, int _containertype_id, typename T_container_tags> std::string Containerbase<T_container, T_content, _containertype_id, T_container_tags>::staticname_container = "test_container";
				template<typename T_container, typename T_content, int _containertype_id, typename T_container_tags> std::string Containerbase<T_container, T_content, _containertype_id, T_container_tags>::staticname_content = "test_content";



				namespace iterator_method {



					template<typename T_container, typename T_content, typename T_iterator> const T_content& current_get(T_iterator* thiis) {
						if (!thiis->IsValid()) {
							common::errorprint::iterator::container_modified();
							return T_container::defaultvalue;
						}

						return *(thiis->it);
					}
					template<typename T_container, typename T_content, typename T_iterator> void current_set(T_iterator* thiis, const T_content& value) {
						if (!thiis->IsValid()) {
							common::errorprint::iterator::container_modified();
							return;
						}

						*(thiis->it) = value;
					}

					template<typename T_container, typename T_content, typename T_iterator> T_content& current(T_iterator* thiis) {
						if (!thiis->IsValid()) {
							common::errorprint::iterator::container_modified();
							return T_container::defaultvalue;
						}

						return *(thiis->it);
					}

					template<typename T_container, typename T_content, typename T_iterator> const T_content& current_const(T_iterator* thiis) {
						if (!thiis->IsValid()) {
							common::errorprint::iterator::container_modified();
							return T_container::defaultvalue;
						}

						return *(thiis->it);
					}



				}//namespace iterator_method



				namespace detail {
					namespace register_iterator_method {



						template<typename T_container, typename T_content, typename T_iterator, typename T_tag_need_const> struct current {};
						template<typename T_container, typename T_content, typename T_iterator> struct current<T_container, T_content, T_iterator, container::shared::tag::iterator_access::access_is_mutable> {
							void operator()(common::RegistrationState& rs) const {
								rs.Format("%s& %s()", rs.n_content, config::scriptname::method::iterator::access_function);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current<T_container, T_content, T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

								rs.Format("%s& get_%s()", rs.n_content, config::scriptname::method::iterator::access_property);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current_get<T_container, T_content, T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
								rs.Format("void set_%s(const %s &in)", config::scriptname::method::iterator::access_property, rs.n_content);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current_set<T_container, T_content, T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
							}
						};
						template<typename T_container, typename T_content, typename T_iterator> struct current<T_container, T_content, T_iterator, container::shared::tag::iterator_access::access_is_const> {
							void operator()(common::RegistrationState& rs) const {
								rs.Format("const %s& %s()", rs.n_content, config::scriptname::method::iterator::access_function);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current_const<T_container, T_content, T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

								rs.Format("const %s& get_%s()", rs.n_content, config::scriptname::method::iterator::access_property);
								rs.error = rs.engine->RegisterObjectMethod(rs.n_iterator_T, rs.textbuf, asFunctionPtr(iterator_method::current_get<T_container, T_content, T_iterator>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
							}
						};



					}//namespace register_iterator_method
				}//namespace detail

				template<typename T_container, typename T_iterator> void register_iterator(common::RegistrationState& rs) {
					typedef typename T_container::T_content T_content;
					typedef typename T_container::container_tags container_tags;
					typedef typename container_tags::iterator_access container_tags__iterator_access;

					rs.error = rs.engine->RegisterObjectType(rs.n_iterator_T, sizeof(T_iterator), asOBJ_VALUE | asGetTypeTraits<T_iterator>()); assert(rs.error >= 0);

					rs.Format("void f()");
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, rs.textbuf, asFunctionPtr(common::reghelp::constructor<T_iterator>), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);
					rs.Format("void f(%s@)", rs.n_container_T);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, rs.textbuf, asFunctionPtr(T_iterator::static_constructor_parentcontainer), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);
					rs.Format("void f(const %s &in)", rs.n_iterator_T);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_CONSTRUCT, rs.textbuf, asFunctionPtr(common::reghelp::constructor_copy<T_iterator, T_iterator>), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);

					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_iterator_T, asBEHAVE_DESTRUCT, "void f()", asFUNCTION(common::reghelp::generic_destructor<T_iterator>), asCALL_CDECL_OBJLAST); assert(rs.error >= 0);

					detail::register_iterator_method::current<T_container, T_content, T_iterator, container_tags__iterator_access> register_method_current; register_method_current(rs);

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



				template<typename T_container> void register_containerbase(common::RegistrationState& rs, const char* n_content) {
					typedef typename T_container::Iterator T_iterator;

					common::RegistrationState::Format_static(rs.n_content, common::RegistrationState::bufsize, "%s", n_content);
					common::RegistrationState::Format_static(rs.n_container_T, common::RegistrationState::bufsize, "%s<%s>", T_container::container_tags::scriptname_container, n_content);
					common::RegistrationState::Format_static(rs.n_iterator, common::RegistrationState::bufsize, "%s%s", T_container::container_tags::scriptname_container, config::scriptname::iterator_suffix);
					common::RegistrationState::Format_static(rs.n_iterator_T, common::RegistrationState::bufsize, "%s<%s>", rs.n_iterator, n_content);
					


					rs.error = rs.engine->RegisterObjectType(rs.n_container_T, 0, asOBJ_REF); assert(rs.error >= 0);

					rs.Format("%s@ f()", rs.n_container_T);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_FACTORY, rs.textbuf, asFUNCTION(shared::asglue::Factory_default<T_container>), asCALL_CDECL); assert(rs.error >= 0);
					rs.Format("%s@ f(%s@)", rs.n_container_T, rs.n_container_T);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_FACTORY, rs.textbuf, asFUNCTION(shared::asglue::Factory_copy<T_container>), asCALL_CDECL); assert(rs.error >= 0);
					rs.Format("%s& opAssign(%s@)", rs.n_container_T, rs.n_container_T);
					rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(shared::asglue::Assign<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_ADDREF, "void f()", asMETHOD(T_container, refcount_Add), asCALL_THISCALL); assert(rs.error >= 0);
					rs.error = rs.engine->RegisterObjectBehaviour(rs.n_container_T, asBEHAVE_RELEASE, "void f()", asMETHOD(T_container, refcount_Release), asCALL_THISCALL); assert(rs.error >= 0);



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

					#if aatc_CONFIG_USE_ASADDON_SERIALIZER
						serializer::engine_registration::Register_els_helpers_for_tempspec<T_container, T_container::containertype_id>(enginestorage::Get_ELS(rs.engine), rs.n_content);
					#endif
				};



			};//namespace shared
		};//namespace tempspec
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif