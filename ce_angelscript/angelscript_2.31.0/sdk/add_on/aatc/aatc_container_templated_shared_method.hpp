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


#ifndef _includedh_aatc_container_templated_shared_method
#define _includedh_aatc_container_templated_shared_method



#include "aatc_container_templated_shared.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace templated {
			namespace shared {



				namespace method {



					template<typename T_container> void swap(T_container* t, T_container& other) {
						t->container.swap(other.container);
						t->safety_iteratorversion_Increment();
						other.safety_iteratorversion_Increment();
					}



					namespace detail {
						class scriptfunctor_cmp {
						public:
							asIScriptContext* cc;
							asIScriptFunction* func;

							bool operator()(void*& lhs, void*& rhs) {
								cc->Prepare(func);
								cc->SetObject(lhs);
								cc->SetArgObject(0, rhs);
								cc->Execute();
								return cc->GetReturnDWord() == -1;
							}
						};

						class scriptfunctor_cmp_customscript {
						public:
							asIScriptContext* cc;
							common::script_Funcpointer* funcptr;

							bool operator()(void*& lhs, void*& rhs) {
								funcptr->Prepare(cc);
								cc->SetArgObject(0, lhs);
								cc->SetArgObject(1, rhs);
								funcptr->Execute(cc);

								return cc->GetReturnDWord() == -1;
							}
						};
					};//namespace detail



					namespace native {



						template<typename T_container> void push_back(T_container* t, void* value) {
							t->safety_iteratorversion_Increment();

							if (t->handlemode) {
								t->container.push_back(nullptr);
								t->StoreHandle(&(t->container.back()), value);
							} else {
								t->container.push_back(t->engine->CreateScriptObjectCopy(value, t->objtype_content));
							}
						}
						template<typename T_container> void pop_back(T_container* t) {
							t->safety_iteratorversion_Increment();

							if (t->handlemode) {
								t->ReleaseHandle(t->container.back());
							} else {
								t->engine->ReleaseScriptObject(t->container.back(), t->objtype_content);
							}

							t->container.pop_back();
						}

						template<typename T_container> void push_front(T_container* t, void* value) {
							t->safety_iteratorversion_Increment();

							if (t->handlemode) {
								t->container.push_front(nullptr);
								t->StoreHandle(&(t->container.front()), value);
							} else {
								t->container.push_front(t->engine->CreateScriptObjectCopy(value, t->objtype_content));
							}
						}
						template<typename T_container> void pop_front(T_container* t) {
							t->safety_iteratorversion_Increment();

							if (t->handlemode) {
								t->ReleaseHandle(t->container.front());
							} else {
								t->engine->ReleaseScriptObject(t->container.front(), t->objtype_content);
							}

							t->container.pop_front();
						}

						template<typename T_container> void* back(T_container* t) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								aatc::common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::back);
								return nullptr;
							}
							#endif

							if (t->handlemode) {
								return &(t->container.back());//return pointer to handle
							} else {
								return t->container.back();//return copy of pointer to object
							}
						}
						template<typename T_container> void* front(T_container* t) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								aatc::common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::back);
								return nullptr;
							}
							#endif

							if (t->handlemode) {
								return &(t->container.front());//return pointer to handle
							} else {
								return t->container.front();//return copy of pointer to object
							}
						}

						template<typename T_container> bool erase_value(T_container* t, void* value) {
							if (t->handlemode) {
								if (!t->handlemode_directcomp) {
									#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
										if (t->missing_functions & common::CONTAINER_OPERATION::ERASE_VALUE) {
											common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase_value);
											return 0;
										}
									#endif
								}
								typename T_container::T_iterator_native it = t->container.find(*(void**)value);
								if (it != t->container.end()) {
									t->ReleaseHandle(*it);
									t->container.erase(it);

									t->safety_iteratorversion_Increment();

									return 1;
								}
							} else {
								#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
									if (t->missing_functions & common::CONTAINER_OPERATION::ERASE_VALUE) {
										common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase_value);
										return 0;
									}
								#endif

								typename T_container::T_iterator_native it = t->container.find(value);
								if (it != t->container.end()) {
									void* object_to_release = *it;
									t->container.erase(it);//erasing needs object alive to call opCmp
									t->engine->ReleaseScriptObject(object_to_release, t->objtype_content);

									t->safety_iteratorversion_Increment();

									return 1;
								}
							}

							return 0;
						}
						template<typename T_container> void* operator_index_position(T_container* t, config::t::sizetype position) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::operator_index);
								return nullptr;
							}
							if (position >= t->container.size()) {
								common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::operator_index);
								return nullptr;
							}
							#endif

							if (t->handlemode) {
								return &(t->container.operator[](position));//return pointer to handle
							} else {
								return t->container.operator[](position);//return pointer to object
							}
						}

						template<typename T_container> void reserve(T_container* t, config::t::sizetype size) {
							if (size > t->container.size()) {
								t->container.reserve(size);
								t->safety_iteratorversion_Increment();
							}
						}

						template<typename T_container> void insert_value(T_container* t, void* value) {
							t->safety_iteratorversion_Increment();

							if (t->handlemode) {
								if (!t->handlemode_directcomp) {
									#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
										if (t->missing_functions & common::CONTAINER_OPERATION::INSERT) {
											common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::insert);
											return;
										}
									#endif
								}
								std::pair<typename T_container::T_iterator_native, bool> rr = t->container.insert(*(void**)value);
								if (rr.second) {
									t->StoreHandle((void**)&(*rr.first), value);
								}
							} else {
								#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
									if (t->missing_functions & common::CONTAINER_OPERATION::INSERT) {
										common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::insert);
										return;
									}
								#endif

								typename T_container::T_iterator_native it = t->container.find(value);
								if (it == t->container.end()) {
									t->container.insert(t->engine->CreateScriptObjectCopy(value, t->objtype_content));
								}
							}
						}

						template<typename T_container> void sort(T_container* t, bool ascending) {
							if (t->handlemode_directcomp) { return; }

							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->missing_functions & common::CONTAINER_OPERATION::SORT) {
								common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::sort);
								return;
							}
							#endif

							t->safety_iteratorversion_Increment();

							detail::scriptfunctor_cmp functor;
							functor.cc = t->els->contextcache_Get();
							functor.func = t->func_cmp;

							if (ascending) {
								t->container.sort(functor);
							} else {
								t->container.sort(common::detail::functor_notcmp_persistent_noconst<void*, detail::scriptfunctor_cmp>(functor));
							}

							t->els->contextcache_Return(functor.cc);
						}

						template<typename T_container> void sort_aatcfuncptr(T_container* t, common::script_Funcpointer* funcptr, bool ascending) {
							if (t->handlemode_directcomp) { return; }

							t->safety_iteratorversion_Increment();

							detail::scriptfunctor_cmp_customscript functor;
							functor.cc = t->els->contextcache_Get();
							functor.funcptr = funcptr;

							if (ascending) {
								t->container.sort(functor);
							} else {
								t->container.sort(common::detail::functor_notcmp_persistent_noconst<void*, detail::scriptfunctor_cmp_customscript>(functor));
							}

							t->els->contextcache_Return(functor.cc);
						}

						/*
						?&in wont compile in AS 2.31.0 with funcptr as argument
						template<typename T_container> void sort_scriptfunc(T_container* t, void* scriptfunc_, int tid, bool ascending) {
							if (t->handlemode_directcomp) { return; }

							t->safety_iteratorversion_Increment();

							asIScriptFunction* scriptfunc = (asIScriptFunction*)scriptfunc_;
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

							if (t->handlemode) {
								void* aux_object = scriptfunc->GetAuxiliary();
								if (aux_object) {
									container::shared::scriptcmpfunctor_method<container::shared::scriptcmpfunctor_internal::dummytype_handle> functor;
									functor.context = context;
									functor.func = scriptfunc;
									functor.reverse_multiplier = reverse_multiplier;

									functor.aux_object = aux_object;

									t->container.sort(functor);
								} else {
									container::shared::scriptcmpfunctor_globalfunction<container::shared::scriptcmpfunctor_internal::dummytype_handle> functor;
									functor.context = context;
									functor.func = scriptfunc;
									functor.reverse_multiplier = reverse_multiplier;

									t->container.sort(functor);
								}
							} else {
								void* aux_object = scriptfunc->GetAuxiliary();
								if (aux_object) {
									container::shared::scriptcmpfunctor_method<container::shared::scriptcmpfunctor_internal::dummytype_object> functor;
									functor.context = context;
									functor.func = scriptfunc;
									functor.reverse_multiplier = reverse_multiplier;

									functor.aux_object = aux_object;

									t->container.sort(functor);
								} else {
									container::shared::scriptcmpfunctor_globalfunction<container::shared::scriptcmpfunctor_internal::dummytype_object> functor;
									functor.context = context;
									functor.func = scriptfunc;
									functor.reverse_multiplier = reverse_multiplier;

									t->container.sort(functor);
								}
							}

							if (context == old_context) {
								old_context->PopState();
							} else {
								engine->ReturnContext(context);
							}
						}
						*/

						template<typename T_container> bool contains(T_container* t, void* value) {
							if (!t->handlemode_directcomp) {
								#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
									if (t->missing_functions & common::CONTAINER_OPERATION::CONTAINS) {
										common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::contains);
										return 0;
									}
								#endif
							}
							if (t->handlemode) { value = *(void**)value; }

							typename T_container::T_iterator_native_const it = t->container.find(value);
							return it != t->container.end();
						}

						template<typename T_container> void erase_iterator(T_container* t, const typename T_container::Iterator& position) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (t->safety_iteratorversion != position.safety_iteratorversion) {
									common::errorprint::container::iterator_invalid();
									return;
								}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native it = position.it;

							if (it != t->container.end()) {
								if (t->handlemode) {
									t->ReleaseHandle(*it);
									t->container.erase(it);
								} else {
									void* object_to_release = *it;
									t->container.erase(it);
									t->engine->ReleaseScriptObject(object_to_release, t->objtype_content);
								}
							}
						}
						template<typename T_container> config::t::sizetype erase_iterator_range(T_container* t, const typename T_container::Iterator& range_begin, const typename T_container::Iterator& range_end) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if ((t->safety_iteratorversion != range_begin.safety_iteratorversion) || (t->safety_iteratorversion != range_end.safety_iteratorversion)) {
									common::errorprint::container::iterator_invalid();
									return 0;
								}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native it_range_begin = range_begin.it;
							typename T_container::T_iterator_native it_range_end = range_end.it;

							if (it_range_begin == it_range_end) {
								return 0;
							} else {
								config::t::sizetype delcount = 0;

								if (t->handlemode) {
									for (auto it = it_range_begin; it != it_range_end; it++) {
										t->ReleaseHandle(*it);
										delcount++;
									}
									t->container.erase(it_range_begin, it_range_end);
								} else {
									std::vector<void*> objects_to_release;//ohhh my performance

									objects_to_release.reserve(t->container.size());
									for (auto it = it_range_begin; it != it_range_end; it++) {
										objects_to_release.push_back(*it);
									}

									t->container.erase(it_range_begin, it_range_end);//erasing needs objects alive to call opCmp

									for (auto it = objects_to_release.begin(); it != objects_to_release.end(); it++) {
										t->engine->ReleaseScriptObject(*it, t->objtype_content);
										delcount++;
									}
								}

								return delcount;
							}
						}

						template<typename T_container> typename T_container::Iterator find_iterator(T_container* t, void* value) {
							if (!t->handlemode_directcomp) {
								#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
									if (t->missing_functions & common::CONTAINER_OPERATION::FIND) {
										common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::find);

										typename T_container::Iterator result(t);
										result.SetToEnd();
										return result;
									}
								#endif
							}

							if (t->handlemode) { value = *(void**)value; }

							auto it = t->container.find(value);

							typename T_container::Iterator result(t);

							if (it == t->container.end()) {
								result.SetToEnd();
							} else {
								result.it = it;
							}

							return result;
						}

						template<typename T_container> void insert_iterator(T_container* t, const typename T_container::Iterator& position, void* value) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
								if (t->safety_iteratorversion != position.safety_iteratorversion) {
									common::errorprint::container::iterator_invalid();
									return;
								}
							#endif

							t->safety_iteratorversion_Increment();

							void* final_value;

							if (t->handlemode) {
								final_value = t->StoreHandle2(value);
							} else {
								final_value = t->engine->CreateScriptObjectCopy(value, t->objtype_content);
							}

							t->container.insert(position.it, final_value);
						}



					};//namespace native
					namespace genericcc{



						template<typename T_container> void sort(T_container* t, bool ascending) {
							if (t->handlemode_directcomp) { return; }

							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->missing_functions & common::CONTAINER_OPERATION::SORT) {
								common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::sort);
								return;
							}
							#endif

							t->safety_iteratorversion_Increment();

							detail::scriptfunctor_cmp functor;
							functor.cc = t->els->contextcache_Get();
							functor.func = t->func_cmp;

							if (ascending) {
								std::sort(t->container.begin(), t->container.end(), functor);
							} else {
								std::sort(t->container.begin(), t->container.end(), common::detail::functor_notcmp_persistent_noconst<void*, detail::scriptfunctor_cmp>(functor));
							}

							t->els->contextcache_Return(functor.cc);
						}

						template<typename T_container> void sort_aatcfuncptr(T_container* t, common::script_Funcpointer* funcptr, bool ascending) {
							if (t->handlemode_directcomp) { return; }

							t->safety_iteratorversion_Increment();

							detail::scriptfunctor_cmp_customscript functor;
							functor.cc = t->els->contextcache_Get();
							functor.funcptr = funcptr;

							if (ascending) {
								std::sort(t->container.begin(), t->container.end(), functor);
							} else {
								std::sort(t->container.begin(), t->container.end(), common::detail::functor_notcmp_persistent_noconst<void*, detail::scriptfunctor_cmp_customscript>(functor));
							}

							t->els->contextcache_Return(functor.cc);
						}

						/*
						?&in wont compile in AS 2.31.0 with funcptr as argument
						template<typename T_container> void sort_scriptfunc(T_container* t, void* scriptfunc_, int tid, bool ascending) {
							if (t->handlemode_directcomp) { return; }

							t->safety_iteratorversion_Increment();

							asIScriptFunction* scriptfunc = (asIScriptFunction*)scriptfunc_;
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

							if (t->handlemode) {
								void* aux_object = scriptfunc->GetAuxiliary();
								if (aux_object) {
									container::shared::scriptcmpfunctor_method<container::shared::scriptcmpfunctor_internal::dummytype_handle> functor;
									functor.context = context;
									functor.func = scriptfunc;
									functor.reverse_multiplier = reverse_multiplier;

									functor.aux_object = aux_object;

									std::sort(t->container.begin(), t->container.end(), functor);
								} else {
									container::shared::scriptcmpfunctor_globalfunction<container::shared::scriptcmpfunctor_internal::dummytype_handle> functor;
									functor.context = context;
									functor.func = scriptfunc;
									functor.reverse_multiplier = reverse_multiplier;

									std::sort(t->container.begin(), t->container.end(), functor);
								}
							} else {
								void* aux_object = scriptfunc->GetAuxiliary();
								if (aux_object) {
									container::shared::scriptcmpfunctor_method<container::shared::scriptcmpfunctor_internal::dummytype_object> functor;
									functor.context = context;
									functor.func = scriptfunc;
									functor.reverse_multiplier = reverse_multiplier;

									functor.aux_object = aux_object;

									std::sort(t->container.begin(), t->container.end(), functor);
								} else {
									container::shared::scriptcmpfunctor_globalfunction<container::shared::scriptcmpfunctor_internal::dummytype_object> functor;
									functor.context = context;
									functor.func = scriptfunc;
									functor.reverse_multiplier = reverse_multiplier;

									std::sort(t->container.begin(), t->container.end(), functor);
								}
							}

							if (context == old_context) {
								old_context->PopState();
							} else {
								engine->ReturnContext(context);
							}
						}
						*/

						template<typename T_container> void insert_position_before_constant(T_container* t, config::t::sizetype position, void* value) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::insert_position_before);
								return;
							}
							if (position >= t->container.size()) {
								common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::insert_position_before);
								return;
							}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native ii = t->container.begin() + position;

							if (t->handlemode) {
								t->container.insert(ii, t->StoreHandle2(value));
							} else {
								t->container.insert(ii, t->engine->CreateScriptObjectCopy(value, t->objtype_content));
							}
						}
						template<typename T_container> void insert_position_before_linear(T_container* t, config::t::sizetype position, void* value) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::insert_position_before);
								return;
							}
							if (position >= t->container.size()) {
								common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::insert_position_before);
								return;
							}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native ii = t->container.begin();
							for (int i = 0; i < position; i++) { ii++; }

							if (t->handlemode) {
								t->container.insert(ii, t->StoreHandle2(value));
							} else {
								t->container.insert(ii, t->engine->CreateScriptObjectCopy(value, t->objtype_content));
							}
						}

						template<typename T_container> void erase_position_constant(T_container* t, config::t::sizetype position) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return;
							}
							if (position >= t->container.size()) {
								common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return;
							}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native ii = t->container.begin() + position;

							if (t->handlemode) {
								t->ReleaseHandle(*ii);
							} else {
								t->engine->ReleaseScriptObject(*ii, t->objtype_content);
							}

							t->container.erase(ii);
						}
						template<typename T_container> void erase_position_linear(T_container* t, config::t::sizetype position) {
							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return;
							}
							if (position >= t->container.size()) {
								common::errorprint::container::access_bounds(position, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return;
							}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native ii = t->container.begin();
							for (int i = 0; i < position; i++) { ii++; }

							if (t->handlemode) {
								t->ReleaseHandle(*ii);
							} else {
								t->engine->ReleaseScriptObject(*ii, t->objtype_content);
							}

							t->container.erase(ii);
						}

						template<typename T_container> config::t::sizetype erase_position_range_constant(T_container* t, config::t::sizetype range_begin, config::t::sizetype range_end) {
							if (range_begin >= range_end) {
								return 0;
							}

							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return 0;
							}
							if (range_begin >= t->container.size()) {
								common::errorprint::container::access_bounds(range_begin, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return 0;
							}
							if (range_end > t->container.size()) {
								common::errorprint::container::access_bounds(range_end, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return 0;
							}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native ii_begin = t->container.begin() + range_begin;
							typename T_container::T_iterator_native ii_end = t->container.begin() + range_end;

							{
								typename T_container::T_iterator_native ii = ii_begin;

								if (t->handlemode) {
									for (; ii != ii_end; ii++) {
										t->ReleaseHandle(*ii);
									}
								} else {
									for (; ii != ii_end; ii++) {
										t->engine->ReleaseScriptObject(*ii, t->objtype_content);
									}
								}


							}

							std::size_t oldsize = t->container.size();
							t->container.erase(ii_begin, ii_end);
							return config::t::sizetype(oldsize - t->container.size());
						}
						template<typename T_container> config::t::sizetype erase_position_range_linear(T_container* t, config::t::sizetype range_begin, config::t::sizetype range_end) {
							if (range_begin >= range_end) {
								return 0;
							}

							#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
							if (t->empty()) {
								common::errorprint::container::access_empty(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return 0;
							}
							if (range_begin >= t->container.size()) {
								common::errorprint::container::access_bounds(range_begin, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return 0;
							}
							if (range_end > t->container.size()) {
								common::errorprint::container::access_bounds(range_end, (config::t::sizetype)t->container.size(), t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase);
								return 0;
							}
							#endif

							t->safety_iteratorversion_Increment();

							typename T_container::T_iterator_native ii_begin = t->container.begin();
							typename T_container::T_iterator_native ii_end = t->container.begin();
							for (int i = 0; i < range_begin; i++) { ii_begin++; }
							for (int i = 0; i < range_end; i++) { ii_end++; }

							{
								typename T_container::T_iterator_native ii = ii_begin;

								if (t->handlemode) {
									for (; ii != ii_end; ii++) {
										t->ReleaseHandle(*ii);
									}
								} else {
									for (; ii != ii_end; ii++) {
										t->engine->ReleaseScriptObject(*ii, t->objtype_content);
									}
								}


							}

							std::size_t oldsize = t->container.size();
							t->container.erase(ii_begin, ii_end);
							return config::t::sizetype(oldsize - t->container.size());
						}

						template<typename T_container> config::t::sizetype erase_value(T_container* t, void* value, bool all) {
							std::size_t oldsize = t->container.size();

							if (t->handlemode) { value = *(void**)value; }

							if (t->handlemode_directcomp) {
								bool continuu = 1;
								while (continuu) {
									continuu = 0;
									bool found = 0;

									typename T_container::T_iterator_native it = t->container.begin();
									typename T_container::T_iterator_native itend = t->container.end();

									for (; it != itend; it++) {
										if (*it == value) {
											found = 1;
											t->engine->ReleaseScriptObject(*it, t->objtype_content);
											t->container.erase(it);
											break;
										}
									}
									if (t->container.empty()) { break; }

									if (found && all) { continuu = 1; }
								}
							} else {
								#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
									if (t->missing_functions & common::CONTAINER_OPERATION::ERASE_VALUE) {
										common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::erase_value);
										return 0;
									}
								#endif

								asIScriptContext* cc = t->els->contextcache_Get();

								asIScriptFunction* func = t->func_cmp;
								if (t->func_equals) { func = t->func_equals; }

								bool continuu = 1;
								while (continuu) {
									continuu = 0;
									bool found = 0;

									typename T_container::T_iterator_native it = t->container.begin();
									typename T_container::T_iterator_native itend = t->container.end();

									for (; it != itend; it++) {
										cc->Prepare(func);
										cc->SetObject(value);
										cc->SetArgObject(0, *it);
										cc->Execute();

										if (t->func_equals) {
											if (cc->GetReturnByte()) { found = 1; }
										} else {
											if (cc->GetReturnDWord() == 0) { found = 1; }
										}
										if (found) {
											found = 1;
											t->engine->ReleaseScriptObject(*it, t->objtype_content);
											t->container.erase(it);
											break;
										}
									}
									if (t->container.empty()) { break; }

									if (found && all) { continuu = 1; }
								}

								t->els->contextcache_Return(cc);
							}

							std::size_t sizediff = oldsize - t->container.size();
							if (sizediff) { t->safety_iteratorversion_Increment(); }
							return config::t::sizetype(sizediff);
						}

						template<typename T_container> typename T_container::Iterator find_iterator(T_container* t, void* value) {
							if (!t->handlemode_directcomp) {
								#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->missing_functions & common::CONTAINER_OPERATION::FIND) {
									common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::find);

									typename T_container::Iterator result(t);
									result.SetToEnd();
									return result;
								}
								#endif
							}

							if (t->handlemode) { value = *(void**)value; }

							container::shared::containerfunctor::Equals eq(t->engine, t);
							container::shared::containerfunctor::Equals::findif_version eq_fi;
							eq_fi.f = &eq;
							eq_fi.target = value;

							auto it = std::find_if(t->container.begin(), t->container.end(), eq_fi);

							typename T_container::Iterator result(t);
							result.it = it;

							if (it == t->container.end()) {
								result.SetToEnd();
							}

							return result;
						}

						template<typename T_container> config::t::sizetype count(T_container* t, void* value) {
							if (t->handlemode_directcomp) {
								return (config::t::sizetype)(std::count(t->container.begin(), t->container.end(), *(void**)value));
							} else {
								#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME
								if (t->missing_functions & common::CONTAINER_OPERATION::COUNT) {
									common::errorprint::container::missingfunctions_operation_missing(t->typeinfo_container->GetName(), t->objtype_content->GetName(), config::scriptname::method::container::count);

									typename T_container::Iterator result(t);
									result.SetToEnd();
									return 0;
								}
								#endif

								if (t->handlemode) { value = *(void**)value; }

								asIScriptContext* cc = t->els->contextcache_Get();

								config::t::sizetype count = 0;
								typename T_container::T_iterator_native it = t->container.begin();
								typename T_container::T_iterator_native itend = t->container.end();

								asIScriptFunction* func = t->func_cmp;
								if (t->func_equals) { func = t->func_equals; }

								if (t->func_equals) {
									for (; it != itend; it++) {
										cc->Prepare(func);
										cc->SetObject(value);
										cc->SetArgObject(0, *it);
										cc->Execute();
										count += (cc->GetReturnByte());
									}
								} else {//func cmp
									for (; it != itend; it++) {
										cc->Prepare(func);
										cc->SetObject(value);
										cc->SetArgObject(0, *it);
										cc->Execute();
										count += (cc->GetReturnDWord() == 0);
									}
								}
								t->els->contextcache_Return(cc);

								return count;
							}
						}

						template<typename T_container> bool contains(T_container* t, void* value) {
							return count(t, value) > 0;
						}



					};//namespace genericcc



				};//namespace method
				namespace register_method {



					template<typename T_container> static void swap(common::RegistrationState& rs) {
						rs.Format("%s& %s(%s &inout)", rs.n_container_T, config::scriptname::method::container::swap, rs.n_container_T);
						rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asMETHOD(T_container,swap), asCALL_THISCALL); assert(rs.error >= 0);
					}

					namespace native{



						template<typename T_container> static void push_back(common::RegistrationState& rs) {
							rs.Format("void %s(const T&in)", config::scriptname::method::container::push_back);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::push_back<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void pop_back(common::RegistrationState& rs) {
							rs.Format("void %s()", config::scriptname::method::container::pop_back);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::pop_back<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void push_front(common::RegistrationState& rs) {
							rs.Format("void %s(const T&in)", config::scriptname::method::container::push_front);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::push_front<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void pop_front(common::RegistrationState& rs) {
							rs.Format("void %s()", config::scriptname::method::container::pop_front);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::pop_front<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void back(common::RegistrationState& rs) {
							rs.Format("T& %s()", config::scriptname::method::container::back);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::back<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void front(common::RegistrationState& rs) {
							rs.Format("T& %s()", config::scriptname::method::container::front);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::front<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void erase_value(common::RegistrationState& rs) {
							rs.Format("bool %s(const T&in)", config::scriptname::method::container::erase);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::erase_value<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void operator_index_position(common::RegistrationState& rs) {
							rs.Format("T& %s(%s)", config::scriptname::method::container::operator_index, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::operator_index_position<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void reserve(common::RegistrationState& rs) {
							rs.Format("void %s(%s)", config::scriptname::method::container::reserve, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::reserve<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void insert_value(common::RegistrationState& rs) {
							rs.Format("void %s(const T&in)", config::scriptname::method::container::insert);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::insert_value<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void sort(common::RegistrationState& rs) {
							rs.Format("void %s(bool ascending)", config::scriptname::method::container::sort);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::sort<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

							rs.Format("void %s(const %s&in funcptr, bool ascending)", config::scriptname::method::container::sort_aatcfuncptr, config::scriptname::funcpointer);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::sort_aatcfuncptr<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

							//?&in wont compile in AS 2.31.0 with funcptr as argument
							//rs.Format("void %s(const ?&in scriptfunc, bool ascending)", config::scriptname::method::container::sort_scriptfunc);
							//rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::sort_aatcfuncptr<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void contains(common::RegistrationState& rs) {
							rs.Format("bool %s(const T&in)", config::scriptname::method::container::contains);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::contains<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void erase_iterator(common::RegistrationState& rs) {
							rs.Format("void %s(const %s &in)", config::scriptname::method::container::erase_iterator,rs.n_iterator_T);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::erase_iterator<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void erase_iterator_range(common::RegistrationState& rs) {
							rs.Format("%s %s(const %s &in,const %s &in)",config::scriptname::t::size, config::scriptname::method::container::erase_iterator_range, rs.n_iterator_T, rs.n_iterator_T);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::erase_iterator_range<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void find_iterator(common::RegistrationState& rs) {
							rs.Format("%s %s(const T&in)", rs.n_iterator_T, config::scriptname::method::container::find_iterator);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::find_iterator<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void insert_iterator(common::RegistrationState& rs) {
							rs.Format("void %s(const %s &in, const T&in)", config::scriptname::method::container::insert_iterator, rs.n_iterator_T);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::native::insert_iterator<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}



					};//namespace native
					namespace genericcc{



						template<typename T_container> static void sort(common::RegistrationState& rs) {
							rs.Format("void %s(bool ascending)", config::scriptname::method::container::sort);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::sort<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

							rs.Format("void %s(const %s&in, bool ascending)", config::scriptname::method::container::sort_aatcfuncptr, config::scriptname::funcpointer);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::sort_aatcfuncptr<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);

							//?&in wont compile in AS 2.31.0 with funcptr as argument
							//rs.Format("void %s(const ?&in scriptfunc, bool ascending)", config::scriptname::method::container::sort_scriptfunc);
							//rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::sort_aatcfuncptr<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void insert_position_before_constant(common::RegistrationState& rs) {
							rs.Format("void %s(%s, const T&in)", config::scriptname::method::container::insert_position_before, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::insert_position_before_constant<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}
						template<typename T_container> static void insert_position_before_linear(common::RegistrationState& rs) {
							rs.Format("void %s(%s, const T&in)", config::scriptname::method::container::insert_position_before, config::scriptname::t::size);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::insert_position_before_linear<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

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

						template<typename T_container> static void erase_value(common::RegistrationState& rs) {
							rs.Format("%s %s(const T&in, bool all = false)", config::scriptname::t::size, config::scriptname::method::container::erase_value);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::erase_value<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void find_iterator(common::RegistrationState& rs) {
							rs.Format("%s %s(const T&in)", rs.n_iterator_T, config::scriptname::method::container::find_iterator);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::find_iterator<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void contains(common::RegistrationState& rs) {
							rs.Format("bool %s(const T&in)", config::scriptname::method::container::contains);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::contains<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}

						template<typename T_container> static void count(common::RegistrationState& rs) {
							rs.Format("%s %s(const T&in)", config::scriptname::t::size, config::scriptname::method::container::count);
							rs.error = rs.engine->RegisterObjectMethod(rs.n_container_T, rs.textbuf, asFUNCTION(method::genericcc::count<T_container>), asCALL_CDECL_OBJFIRST); assert(rs.error >= 0);
						}



					};//namespace genericcc



				};//namespace register_method



			};//namespace shared
		};//namespace templated
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif