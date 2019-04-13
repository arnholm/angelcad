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


#ifndef _includedh_aatc_container_tempspec_shared_method
#define _includedh_aatc_container_tempspec_shared_method



#include "aatc_container_tempspec_shared.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace tempspec {
			namespace shared {



				namespace method {

					template<typename T_container> void swap(T_container* t, T_container& other) {
						t->container.swap(other.container);

						t->safety_iteratorversion_Increment();
						other.safety_iteratorversion_Increment();
					}



					namespace native {



						template<typename T_container> void push_back(T_container* t, const typename T_container::T_content& value) {
							t->container.push_back(value);

							t->safety_iteratorversion_Increment();
						}
						template<typename T_container> void pop_back(T_container* t) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::pop_back);
									return;
								}
							#endif

							t->container.pop_back();
							t->safety_iteratorversion_Increment();
						}

						template<typename T_container> void push_front(T_container* t, const typename T_container::T_content& value) {
							t->container.push_front(value);

							t->safety_iteratorversion_Increment();
						}
						template<typename T_container> void pop_front(T_container* t) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::pop_front);
									return;
								}
							#endif

							t->container.pop_front();
							t->safety_iteratorversion_Increment();
						}

						template<typename T_container> typename T_container::T_content& back(T_container* t) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::back);
									return T_container::defaultvalue;
								}
							#endif

							return t->container.back();
						}
						template<typename T_container> typename T_container::T_content& front(T_container* t) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::front);
									return T_container::defaultvalue;
								}
							#endif

							return t->container.front();
						}

						template<typename T_container> bool erase_value(T_container* t, const typename T_container::T_content& value) {
							config::t::sizetype oldsize = config::t::sizetype(t->container.size());

							t->container.erase(value);
							t->safety_iteratorversion_Increment();

							return oldsize != t->container.size();
						}
						template<typename T_container> void insert_value(T_container* t, const typename T_container::T_content& value) {
							t->container.insert(value);
							t->safety_iteratorversion_Increment();
						}

						template<typename T_container> typename T_container::T_content& operator_index_position(T_container* t, config::t::sizetype position) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::operator_index);
									return T_container::defaultvalue;
								}
								if (position >= t->container.size()) {
									aatc::common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::operator_index);
									return T_container::defaultvalue;
								}
							#endif

							return t->container[position];
						}
						template<typename T_container> void reserve(T_container* t, config::t::sizetype size) {
							t->safety_iteratorversion_Increment();
							return t->container.reserve(size);
						}

						template<typename T_container> void sort(T_container* t, bool ascending) {
							t->safety_iteratorversion_Increment();

							if (ascending) {
								t->container.sort(std::less<typename T_container::T_content>());
							} else {
								t->container.sort(common::detail::functor_notcmp<typename T_container::T_content, std::less<typename T_container::T_content>>());

								///*
								//std::list didn't like common::detail::functor_notcmp with primitives in debug mode for some reason
								//so we'll have to use some black majicks
								//*/
								//t->container.sort(
								//	std::conditional<
								//	std::is_class<T_content>::value,
								//	common::detail::functor_notcmp<T_content, std::less<T_content>>,
								//	std::greater<T_content>
								//	>::type()
								//);
							}
						}
						template<typename T_container> void sort_aatcfuncptr(T_container* t, common::script_Funcpointer* funcptr, bool ascending) {
							t->safety_iteratorversion_Increment();

							asIScriptFunction* scriptfunc = funcptr->func;
							asIScriptContext* context = NULL;
							asIScriptEngine* engine = t->engine;
							asIScriptContext* old_context = asGetActiveContext();

							if (old_context) {
								if (old_context->PushState() > -1) {
									context = old_context;
								} else {
									context = engine->RequestContext();
								}
							} else {
								context = engine->RequestContext();
							}



							int reverse_multiplier = -1;
							if (ascending) {
								reverse_multiplier = 1;
							}

							void* aux_object = funcptr->so;
							if (aux_object) {
								container::shared::scriptcmpfunctor_method<typename T_container::T_content> functor;
								functor.context = context;
								functor.func = scriptfunc;
								functor.reverse_multiplier = reverse_multiplier;

								functor.aux_object = aux_object;

								t->container.sort(functor);
							} else {
								container::shared::scriptcmpfunctor_globalfunction<typename T_container::T_content> functor;
								functor.context = context;
								functor.func = scriptfunc;
								functor.reverse_multiplier = reverse_multiplier;

								t->container.sort(functor);
							}



							if (context == old_context) {
								old_context->PopState();
							} else {
								engine->ReturnContext(context);
							}
						}
						template<typename T_container> void sort_scriptfunc(T_container* t, asIScriptFunction* scriptfunc, bool ascending) {
							t->safety_iteratorversion_Increment();

							asIScriptContext* context = NULL;
							asIScriptEngine* engine = t->engine;
							asIScriptContext* old_context = asGetActiveContext();

							if (old_context) {
								if (old_context->PushState() > -1) {
									context = old_context;
								} else {
									context = engine->RequestContext();
								}
							} else {
								context = engine->RequestContext();
							}



							int reverse_multiplier = -1;
							if (ascending) {
								reverse_multiplier = 1;
							}

							void* aux_object = scriptfunc->GetAuxiliary();
							if (aux_object) {
								container::shared::scriptcmpfunctor_method<typename T_container::T_content> functor;
								functor.context = context;
								functor.func = scriptfunc;
								functor.reverse_multiplier = reverse_multiplier;

								functor.aux_object = aux_object;

								t->container.sort(functor);
							} else {
								container::shared::scriptcmpfunctor_globalfunction<typename T_container::T_content> functor;
								functor.context = context;
								functor.func = scriptfunc;
								functor.reverse_multiplier = reverse_multiplier;

								t->container.sort(functor);
							}



							if (context == old_context) {
								old_context->PopState();
							} else {
								engine->ReturnContext(context);
							}
						}


						template<typename T_container> bool contains(T_container* t, const typename T_container::T_content& value) {
							return t->container.find(value) != t->container.end();
						}

						template<typename T_container> bool erase_iterator(T_container* t, const typename T_container::Iterator& aatc_it) {
							if (t->container.empty()) { return 0; }

							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (t->safety_iteratorversion != aatc_it.safety_iteratorversion) {
									common::errorprint::container::iterator_invalid();
									return 0;
								}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native it = aatc_it.it;

							if (it == t->container.end()) {
								return 0;
							}

							t->container.erase(it);

							return 1;
						}

						template<typename T_container> config::t::sizetype erase_iterator_range(T_container* t, const typename T_container::Iterator& aatc_it_range_begin, const typename T_container::Iterator& aatc_it_range_end) {
							if (t->container.empty()) { return 0; }

							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
							if ((t->safety_iteratorversion != aatc_it_range_begin.safety_iteratorversion) || (t->safety_iteratorversion != aatc_it_range_end.safety_iteratorversion)) {
								common::errorprint::container::iterator_invalid();
								return 0;
							}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native it_range_begin = aatc_it_range_begin.it;
							typename T_container::T_iterator_native it_range_end = aatc_it_range_end.it;

							if (it_range_begin == it_range_end) {
								return 0;
							} else {
								config::t::sizetype delcount = (config::t::sizetype)std::distance(it_range_begin, it_range_end);
								t->container.erase(it_range_begin, it_range_end);
								return delcount;
							}
						}

						template<typename T_container> typename T_container::Iterator find_iterator(T_container* t, const typename T_container::T_content& value) {
							typename T_container::T_iterator_native it = t->container.find(value);

							typename T_container::Iterator result(t);
							result.it = it;

							if (it == t->container.end()) {
								result.SetToEnd();
							}

							return result;
						}

						template<typename T_container> void insert_iterator(T_container* t, typename T_container::Iterator position, const typename T_container::T_content& value) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (t->safety_iteratorversion != position.safety_iteratorversion) {
									common::errorprint::container::iterator_invalid();
									return;
								}
							#endif

							t->safety_iteratorversion_Increment();

							t->container.insert(position.it, value);
						}




					};//namespace native



					namespace genericcc {



						template<typename T_container> void erase_position_constant(T_container* t, config::t::sizetype position) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
									return;
								}
								if (position >= t->container.size()) {
									aatc::common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(),T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
									return;
								}
							#endif

							t->container.erase(t->container.begin() + position);
							t->safety_iteratorversion_Increment();
						}
						template<typename T_container> void erase_position_linear(T_container* t, config::t::sizetype position) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
									return;
								}
								if (position >= t->container.size()) {
									aatc::common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
									return;
								}
							#endif

							typename T_container::T_iterator_native it = t->container.begin();
							for (int i = 0; i < position; i++) { it++; }

							t->container.erase(it);
							t->safety_iteratorversion_Increment();
						}

						template<typename T_container> config::t::sizetype erase_position_range_constant(T_container* t, config::t::sizetype range_begin, config::t::sizetype range_end) {
							if (range_begin >= range_end) {
								return 0;
							}

							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
									return 0;
								}
								if (range_begin >= t->container.size()) {
									aatc::common::errorprint::container::access_bounds(range_begin, (config::t::sizetype)t->container.size(), T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
									return 0;
								}
								if (range_end >= t->container.size()) {
									aatc::common::errorprint::container::access_bounds(range_end, (config::t::sizetype)t->container.size(), T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
									return 0;
								}
							#endif

							t->safety_iteratorversion_Increment();

							std::size_t oldsize = t->container.size();

							t->container.erase(t->container.begin() + range_begin, t->container.begin() + range_end);

							return config::t::sizetype(oldsize - t->container.size());
						}
						template<typename T_container> config::t::sizetype erase_position_range_linear(T_container* t, config::t::sizetype range_begin, config::t::sizetype range_end) {
							if (range_begin >= range_end) {
								return 0;
							}

							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
								return 0;
							}
							if (range_begin >= t->container.size()) {
								aatc::common::errorprint::container::access_bounds(range_begin, (config::t::sizetype)t->container.size(), T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
								return 0;
							}
							if (range_end >= t->container.size()) {
								aatc::common::errorprint::container::access_bounds(range_end, (config::t::sizetype)t->container.size(), T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::erase);
								return 0;
							}
							#endif

							t->safety_iteratorversion_Increment();

							std::size_t oldsize = t->container.size();

							typename T_container::T_iterator_native it_begin = t->container.begin();
							typename T_container::T_iterator_native it_end = t->container.begin();
							for (int i = 0; i < range_begin; i++) { it_begin++; }
							for (int i = 0; i < range_end; i++) { it_end++; }

							t->container.erase(it_begin, it_end);

							return config::t::sizetype(oldsize - t->container.size());
						}

						template<typename T_container> void sort(T_container* t, bool ascending) {
							t->safety_iteratorversion_Increment();

							if (ascending) {
								std::sort(t->container.begin(), t->container.end(), std::less<typename T_container::T_content>());
							} else {
								std::sort(t->container.begin(), t->container.end(), common::detail::functor_notcmp<typename T_container::T_content, std::less<typename T_container::T_content>>());
							}
						}
						template<typename T_container> void sort_aatcfuncptr(T_container* t, common::script_Funcpointer* funcptr, bool ascending) {
							t->safety_iteratorversion_Increment();

							asIScriptFunction* scriptfunc = funcptr->func;
							asIScriptContext* context = NULL;
							asIScriptEngine* engine = t->engine;
							asIScriptContext* old_context = asGetActiveContext();

							if (old_context) {
								if (old_context->PushState() > -1) {
									context = old_context;
								} else {
									context = engine->RequestContext();
								}
							} else {
								context = engine->RequestContext();
							}



							int reverse_multiplier = -1;
							if (ascending) {
								reverse_multiplier = 1;
							}

							void* aux_object = funcptr->so;
							if (aux_object) {
								container::shared::scriptcmpfunctor_method<typename T_container::T_content> functor;
								functor.context = context;
								functor.func = scriptfunc;
								functor.reverse_multiplier = reverse_multiplier;

								functor.aux_object = aux_object;

								std::sort(t->container.begin(), t->container.end(), functor);
							} else {
								container::shared::scriptcmpfunctor_globalfunction<typename T_container::T_content> functor;
								functor.context = context;
								functor.func = scriptfunc;
								functor.reverse_multiplier = reverse_multiplier;

								std::sort(t->container.begin(), t->container.end(), functor);
							}



							if (context == old_context) {
								old_context->PopState();
							} else {
								engine->ReturnContext(context);
							}
						}

						template<typename T_container> void sort_scriptfunc(T_container* t, asIScriptFunction* scriptfunc,bool ascending) {
							t->safety_iteratorversion_Increment();

							asIScriptContext* context = NULL;
							asIScriptEngine* engine = t->engine;
							asIScriptContext* old_context = asGetActiveContext();

							if (old_context) {
								if (old_context->PushState() > -1) {
									context = old_context;
								} else {
									context = engine->RequestContext();
								}
							} else {
								context = engine->RequestContext();
							}



							int reverse_multiplier = -1;
							if (ascending) {
								reverse_multiplier = 1;
							}

							void* aux_object = scriptfunc->GetAuxiliary();
							if (aux_object) {
								container::shared::scriptcmpfunctor_method<typename T_container::T_content> functor;
								functor.context = context;
								functor.func = scriptfunc;
								functor.reverse_multiplier = reverse_multiplier;

								functor.aux_object = aux_object;

								std::sort(t->container.begin(), t->container.end(), functor);
							} else {
								container::shared::scriptcmpfunctor_globalfunction<typename T_container::T_content> functor;
								functor.context = context;
								functor.func = scriptfunc;
								functor.reverse_multiplier = reverse_multiplier;

								std::sort(t->container.begin(), t->container.end(), functor);
							}



							if (context == old_context) {
								old_context->PopState();
							} else {
								engine->ReturnContext(context);
							}
						}


						template<typename T_container> void insert_position_before_constant(T_container* t, config::t::sizetype position, const typename T_container::T_content& value) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::insert_position_before);
									return;
								}
								if (position > t->container.size()) {
									aatc::common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::insert_position_before);
									return;
								}
							#endif

							t->container.insert(t->container.begin() + position,value);
							t->safety_iteratorversion_Increment();
						}
						template<typename T_container> void insert_position_before_linear(T_container* t, config::t::sizetype position, const typename T_container::T_content& value) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->empty()) {
									aatc::common::errorprint::container::access_empty(T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::insert_position_before);
									return;
								}
								if (position > t->container.size()) {
									aatc::common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), T_container::staticname_container.c_str(), T_container::staticname_content.c_str(), config::scriptname::method::container::insert_position_before);
									return;
								}
							#endif

							typename T_container::T_iterator_native it = t->container.begin();
							for (int i = 0; i < position; i++) { it++; }

							t->container.insert(it, value);
							t->safety_iteratorversion_Increment();
						}

						template<typename T_container> config::t::sizetype erase_value(T_container* t, const typename T_container::T_content& value,bool all) {
							t->safety_iteratorversion_Increment();

							config::t::sizetype killcount = 0;

							bool continuu = 1;
							while (continuu) {
								continuu = 0;
								bool found = 0;

								typename T_container::T_iterator_native it = t->container.begin();
								typename T_container::T_iterator_native itend = t->container.end();

								for (; it != itend; it++) {
									if (*it == value) {
										found = 1;
										t->container.erase(it);
										killcount++;
										break;
									}
								}
								if (t->container.empty()) { break; }

								if (found && all) { continuu = 1; }
							}

							return killcount;
						}

						template<typename T_container> typename T_container::Iterator find_iterator(T_container* t, const typename T_container::T_content& value) {
							typename T_container::T_iterator_native it = std::find(t->container.begin(), t->container.end(), value);

							typename T_container::Iterator result(t);
							result.it = it;

							if (it == t->container.end()) {
								result.SetToEnd();
							}

							return result;
						}

						template<typename T_container> bool contains(T_container* t, const typename T_container::T_content& value) {
							for (typename T_container::T_iterator_native_const it = t->container.begin(); it != t->container.end(); it++) {
								if (*it == value) {
									return 1;
								}
							}
							return 0;
						}

						template<typename T_container> config::t::sizetype count(T_container* t, const typename T_container::T_content& value) {
							return (config::t::sizetype)(std::count(t->container.begin(), t->container.end(), value));
						}



					};//namespace genericcc



				};//namespace method
				namespace register_method {



					template<typename T_container> static void swap(common::RegistrationState& rs) {
						rs.Format("%s& %s(%s &inout)", rs.n_container_T, config::scriptname::method::container::swap, rs.n_container_T);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container,swap), asCALL_THISCALL); assert(rs.error >= 0);
					}



					namespace native {



						template<typename T_container> static void push_back(common::RegistrationState& rs) {
							rs.Format("void %s(const %s &in)", config::scriptname::method::container::push_back, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::push_back<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void pop_back(common::RegistrationState& rs) {
							rs.Format("void %s()", config::scriptname::method::container::pop_back);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::pop_back<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void push_front(common::RegistrationState& rs) {
							rs.Format("void %s(const %s &in)", config::scriptname::method::container::push_front, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::push_front<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void pop_front(common::RegistrationState& rs) {
							rs.Format("void %s()", config::scriptname::method::container::pop_front);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::pop_front<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void back(common::RegistrationState& rs) {
							rs.Format("%s& %s()", rs.n_content, config::scriptname::method::container::back);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::back<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void front(common::RegistrationState& rs) {
							rs.Format("%s& %s()", rs.n_content, config::scriptname::method::container::front);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::front<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void erase_value(common::RegistrationState& rs) {
							rs.Format("bool %s(const %s &in)", config::scriptname::method::container::erase, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::erase_value<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void insert_value(common::RegistrationState& rs) {
							rs.Format("void %s(const %s &in)", config::scriptname::method::container::insert, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::insert_value<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void operator_index_position(common::RegistrationState& rs) {
							rs.Format("%s& %s(%s)", rs.n_content, config::scriptname::method::container::operator_index, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::operator_index_position<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void reserve(common::RegistrationState& rs) {
							rs.Format("void %s(%s)", config::scriptname::method::container::reserve, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::reserve<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void sort(common::RegistrationState& rs) {
							rs.Format("void %s(bool ascending)", config::scriptname::method::container::sort);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::sort<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

							rs.Format("void %s(const %s&in, bool ascending)", config::scriptname::method::container::sort_aatcfuncptr, config::scriptname::funcpointer);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::sort_aatcfuncptr<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);



							rs.Format("%s%s", config::scriptname::funcdef_cmp_prefix, rs.n_content);
							std::string this_funcdef_name(rs.textbuf);

							rs.Format("int %s(%s,%s)", this_funcdef_name.c_str(), rs.n_content, rs.n_content);
							std::string this_funcdef_def(rs.textbuf);

							enginestorage::Get_ELS(rs.engine)->RegisterFuncdefIfNeeded(this_funcdef_def);

							rs.Format("void %s(%s@, bool ascending)", config::scriptname::method::container::sort_scriptfunc, this_funcdef_name.c_str());
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::sort_scriptfunc<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void contains(common::RegistrationState& rs) {
							rs.Format("bool %s(const %s &in)", config::scriptname::method::container::contains, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::contains<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void erase_iterator(common::RegistrationState& rs) {
							rs.Format("%s %s(const %s &in)", config::scriptname::t::size, config::scriptname::method::container::erase_iterator, rs.n_iterator_T);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::erase_iterator<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void erase_iterator_range(common::RegistrationState& rs) {
							rs.Format("%s %s(const %s &in,const %s &in)", config::scriptname::t::size, config::scriptname::method::container::erase_iterator_range, rs.n_iterator_T, rs.n_iterator_T);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::erase_iterator_range<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void find_iterator(common::RegistrationState& rs) {
							rs.Format("%s %s(const %s &in)", rs.n_iterator_T, config::scriptname::method::container::find, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::find_iterator<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void insert_iterator(common::RegistrationState& rs) {
							rs.Format("void %s(const %s &in,const %s &in)", config::scriptname::method::container::insert_iterator, rs.n_iterator_T, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::insert_iterator<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}


					};//namespace native



					namespace genericcc {



						template<typename T_container> static void erase_position_constant(common::RegistrationState& rs) {
							rs.Format("void %s(%s)", config::scriptname::method::container::erase_position, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::erase_position_constant<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void erase_position_linear(common::RegistrationState& rs) {
							rs.Format("void %s(%s)", config::scriptname::method::container::erase_position, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::erase_position_linear<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void erase_position_range_constant(common::RegistrationState& rs) {
							rs.Format("void %s(%s,%s)", config::scriptname::method::container::erase_position_range, config::scriptname::t::size, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::erase_position_range_constant<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void erase_position_range_linear(common::RegistrationState& rs) {
							rs.Format("void %s(%s,%s)", config::scriptname::method::container::erase_position_range, config::scriptname::t::size, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::erase_position_range_linear<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void sort(common::RegistrationState& rs) {
							rs.Format("void %s(bool ascending)", config::scriptname::method::container::sort);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::sort<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

							rs.Format("void %s(const %s&in, bool ascending)", config::scriptname::method::container::sort_aatcfuncptr, config::scriptname::funcpointer);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::sort_aatcfuncptr<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

							rs.Format("%s%s", config::scriptname::funcdef_cmp_prefix, rs.n_content);
							std::string this_funcdef_name(rs.textbuf);

							rs.Format("int %s(%s,%s)", this_funcdef_name.c_str(), rs.n_content, rs.n_content);
							std::string this_funcdef_def(rs.textbuf);

							enginestorage::Get_ELS(rs.engine)->RegisterFuncdefIfNeeded(this_funcdef_def);

							rs.Format("void %s(%s@, bool ascending)", config::scriptname::method::container::sort_scriptfunc, this_funcdef_name.c_str());
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::sort_scriptfunc<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void insert_position_before_constant(common::RegistrationState& rs) {
							rs.Format("void %s(%s,const %s &in)", config::scriptname::method::container::insert_position_before, config::scriptname::t::size, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::insert_position_before_constant<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void insert_position_before_linear(common::RegistrationState& rs) {
							rs.Format("void %s(%s,const %s &in)", config::scriptname::method::container::insert_position_before, config::scriptname::t::size, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::insert_position_before_linear<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void erase_value(common::RegistrationState& rs) {
							rs.Format("void %s(const %s &in,bool all = false)", config::scriptname::method::container::erase_value, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::erase_value<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void find_iterator(common::RegistrationState& rs) {
							rs.Format("%s %s(const %s &in)", rs.n_iterator_T, config::scriptname::method::container::find_iterator, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::find_iterator<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void contains(common::RegistrationState& rs) {
							rs.Format("bool %s(const %s &in)", config::scriptname::method::container::contains, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::contains<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void count(common::RegistrationState& rs) {
							rs.Format("%s %s(const %s &in)", config::scriptname::t::size, config::scriptname::method::container::count, rs.n_content);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::count<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}



					};//namespace genericcc



				};//namespace register_method



			};//namespace shared
		};//namespace tempspec
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif