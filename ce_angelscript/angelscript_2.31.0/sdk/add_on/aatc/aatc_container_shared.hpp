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


#ifndef _includedh_aatc_container_shared
#define _includedh_aatc_container_shared



#include "aatc_common.hpp"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace shared {



			namespace tag {
				namespace iterator_access {
					struct access_is_const {};
					struct access_is_mutable {};
				};
				namespace serializer_insert_value_func {
					struct push_back {};
					struct insert {};
				};
				namespace is_map {
					struct is_map {};
					struct is_not_map {};
				};
				namespace is_associative {
					struct is_associative {};
					struct is_not_associative {};
				};
			};

			struct tagbase {
				typedef tag::iterator_access::access_is_mutable iterator_access;
				typedef tag::serializer_insert_value_func::push_back serializer_insert_value_func;
				typedef tag::is_map::is_not_map is_map;
				typedef tag::is_associative::is_not_associative is_associative;
			};



			class container_basicbase {
			public:
				asIScriptEngine* engine;

				#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
					int8_t safety_iteratorversion;
				#endif

				container_basicbase(asIScriptEngine* engine);
				virtual ~container_basicbase();

				void safety_iteratorversion_Increment();
			};



			class iterator_base {
			public:
				bool firstt;
				bool cont;

				#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
					int_fast16_t safety_iteratorversion;
				#endif

				iterator_base();
				iterator_base(const iterator_base& other);
			};



			namespace containerfunctor {
				class Settings {
				public:
					bool handlemode;
					bool handlemode_directcomp;
					asIScriptFunction* func_cmp;
					asIScriptFunction* func_equals;
					asIScriptFunction* func_hash;
				};
				class Base {
				public:
					asIScriptEngine* engine;
					enginestorage::engine_level_storage* els;
					Settings* host_settings;

					bool need_init;

					Base(asIScriptEngine* engine, Settings* settings);
				};

				class Comp : public Settings, public Base {
				public:
					Comp(asIScriptEngine* engine, Settings* settings);
					bool operator()(const void* lhs, const void* rhs) const;
				};
				class Equals : public Settings, public Base {
				public:
					Equals(asIScriptEngine* engine, Settings* settings);
					bool operator()(const void* lhs, const void* rhs) const;

					class findif_version {
					public:
						void* target;
						Equals* f;

						bool operator()(const void* rhs) const;
					};
				};
				class Hash : public Settings, public Base {
				public:
					Hash(asIScriptEngine* engine, Settings* settings);
					config::t::hash operator()(const void* ptr) const;
				};
			};//namespace containerfunctor
			namespace containerfunctor_map {
				class Settings {
				public:
					bool handlemode_directcomp;
					asIScriptFunction* func_cmp;
					asIScriptFunction* func_equals;
					asIScriptFunction* func_hash;

					aatc::common::DATAHANDLINGTYPE datahandlingid_key;
					aatc::common::PRIMITIVE_TYPE primitiveid_key;
				};
				class Base {
				public:
					asIScriptEngine* engine;
					enginestorage::engine_level_storage* els;
					Settings* host_settings;

					bool need_init;

					Base(asIScriptEngine* engine, Settings* settings);
				};

				class Comp : public Settings, public Base {
				public:
					Comp(asIScriptEngine* engine, Settings* settings);
					bool operator()(const aatc::common::primunion& lhs, const aatc::common::primunion& rhs) const;
				};
				class Equals : public Settings, public Base {
				public:
					Equals(asIScriptEngine* engine, Settings* settings);
					bool operator()(const aatc::common::primunion& lhs, const aatc::common::primunion& rhs) const;
				};
				class Hash : public Settings, public Base {
				public:
					Hash(asIScriptEngine* engine, Settings* settings);
					config::t::hash operator()(const aatc::common::primunion& a) const;
				};
			};//namespace containerfunctor_map



			namespace scriptcmpfunctor_internal {
				struct dummytype_object {};
				struct dummytype_handle {};

				template<typename T> struct functor_SetArgs {
					void operator()(asIScriptContext* context, T const& l, T const& r) const {
						context->SetArgObject(0, (void*)(&l));
						context->SetArgObject(1, (void*)(&r));
					}
				};

				template<> struct functor_SetArgs<config::t::int8> {
					void operator()(asIScriptContext* context, config::t::int8 l, config::t::int8 r)const;
				};
				template<> struct functor_SetArgs<config::t::uint8> {
					void operator()(asIScriptContext* context, config::t::uint8 l, config::t::uint8 r)const;
				};

				template<> struct functor_SetArgs<config::t::int16> {
					void operator()(asIScriptContext* context, config::t::int16 l, config::t::int16 r)const;
				};
				template<> struct functor_SetArgs<config::t::uint16> {
					void operator()(asIScriptContext* context, config::t::uint16 l, config::t::uint16 r)const;
				};

				template<> struct functor_SetArgs<config::t::int32> {
					void operator()(asIScriptContext* context, config::t::int32 l, config::t::int32 r)const;
				};
				template<> struct functor_SetArgs<config::t::uint32> {
					void operator()(asIScriptContext* context, config::t::uint32 l, config::t::uint32 r)const;
				};

				template<> struct functor_SetArgs<config::t::int64> {
					void operator()(asIScriptContext* context, config::t::int64 l, config::t::int64 r)const;
				};
				template<> struct functor_SetArgs<config::t::uint64> {
					void operator()(asIScriptContext* context, config::t::uint64 l, config::t::uint64 r)const;
				};

				template<> struct functor_SetArgs<config::t::float32> {
					void operator()(asIScriptContext* context, config::t::float32 l, config::t::float32 r)const;
				};
				template<> struct functor_SetArgs<config::t::float64> {
					void operator()(asIScriptContext* context, config::t::float64 l, config::t::float64 r)const;
				};

				template<> struct functor_SetArgs<dummytype_object> {
					void operator()(asIScriptContext* context, void* l, void* r)const;
				};
				template<> struct functor_SetArgs<dummytype_handle> {
					void operator()(asIScriptContext* context, void* l, void* r)const;
				};

			}//namespace scriptcmpfunctor_internal

			template<typename T> class scriptcmpfunctor_globalfunction {
			public:
				asIScriptContext* context;
				asIScriptFunction* func;
				int reverse_multiplier;

				bool operator()(T const& lhs, T const& rhs) {
					context->Prepare(func);
					scriptcmpfunctor_internal::functor_SetArgs<T> functor_setargs;
					functor_setargs(context, lhs, rhs);
					context->Execute();
					return (context->GetReturnDWord() * reverse_multiplier) == -1;
				}
			};
			template<> class scriptcmpfunctor_globalfunction<scriptcmpfunctor_internal::dummytype_object> {
			public:
				asIScriptContext* context;
				asIScriptFunction* func;
				int reverse_multiplier;

				bool operator()(void* lhs, void* rhs) const {
					context->Prepare(func);
					scriptcmpfunctor_internal::functor_SetArgs<scriptcmpfunctor_internal::dummytype_object> functor_setargs;
					functor_setargs(context, lhs, rhs);
					context->Execute();
					return (context->GetReturnDWord() * reverse_multiplier) == -1;
				}
			};
			template<> class scriptcmpfunctor_globalfunction<scriptcmpfunctor_internal::dummytype_handle> {
			public:
				asIScriptContext* context;
				asIScriptFunction* func;
				int reverse_multiplier;

				bool operator()(void* lhs, void* rhs) const {
					context->Prepare(func);
					scriptcmpfunctor_internal::functor_SetArgs<scriptcmpfunctor_internal::dummytype_handle> functor_setargs;
					functor_setargs(context, lhs, rhs);
					context->Execute();
					return (context->GetReturnDWord() * reverse_multiplier) == -1;
				}
			};

			template<typename T> class scriptcmpfunctor_method {
			public:
				asIScriptContext* context;
				asIScriptFunction* func;
				int reverse_multiplier;
				void* aux_object;

				bool operator()(T const& lhs, T const& rhs) {
					context->Prepare(func);
					context->SetObject(aux_object);
					scriptcmpfunctor_internal::functor_SetArgs<T> functor_setargs;
					functor_setargs(context, lhs, rhs);
					context->Execute();
					return (context->GetReturnDWord() * reverse_multiplier) == -1;
				}
			};
			template<> class scriptcmpfunctor_method<scriptcmpfunctor_internal::dummytype_object> {
			public:
				asIScriptContext* context;
				asIScriptFunction* func;
				int reverse_multiplier;
				void* aux_object;

				bool operator()(void* lhs, void* rhs) {
					context->Prepare(func);
					context->SetObject(aux_object);
					scriptcmpfunctor_internal::functor_SetArgs<scriptcmpfunctor_internal::dummytype_object> functor_setargs;
					functor_setargs(context, lhs, rhs);
					context->Execute();
					return (context->GetReturnDWord() * reverse_multiplier) == -1;
				}
			};
			template<> class scriptcmpfunctor_method<scriptcmpfunctor_internal::dummytype_handle> {
			public:
				asIScriptContext* context;
				asIScriptFunction* func;
				int reverse_multiplier;
				void* aux_object;

				bool operator()(void* lhs, void* rhs) {
					context->Prepare(func);
					context->SetObject(aux_object);
					scriptcmpfunctor_internal::functor_SetArgs<scriptcmpfunctor_internal::dummytype_handle> functor_setargs;
					functor_setargs(context, lhs, rhs);
					context->Execute();
					return (context->GetReturnDWord() * reverse_multiplier) == -1;
				}
			};



			namespace autoregister {
				template<template<typename T_content> class tempspec_container_template> void register_all_tempspec_basics_for_container(asIScriptEngine* engine) {
					common::RegistrationState rs(engine);

					tempspec_container_template<config::t::int8>::Register(rs, "int8");
					tempspec_container_template<config::t::int16>::Register(rs, "int16");
					tempspec_container_template<config::t::int32>::Register(rs, "int");
					tempspec_container_template<config::t::int64>::Register(rs, "int64");

					tempspec_container_template<config::t::uint8>::Register(rs, "uint8");
					tempspec_container_template<config::t::uint16>::Register(rs, "uint16");
					tempspec_container_template<config::t::uint32>::Register(rs, "uint");
					tempspec_container_template<config::t::uint64>::Register(rs, "uint64");

					tempspec_container_template<config::t::float32>::Register(rs, "float");
					tempspec_container_template<config::t::float64>::Register(rs, "double");

					tempspec_container_template<config::t::string>::Register(rs, "string");
				}
			};//namespace autoregister



		};//namespace shared
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE



#endif