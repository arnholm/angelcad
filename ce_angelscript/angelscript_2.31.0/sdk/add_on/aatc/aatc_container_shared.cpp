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



#include "aatc_container_shared.hpp"
#include "aatc_hash.hpp"
#include "aatc_enginestorage.hpp"


//int debug_containercount = 0;
//#include <iostream>



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace container {
		namespace shared {



			container_basicbase::container_basicbase(asIScriptEngine* engine):
				engine(engine)
			{
				#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
					safety_iteratorversion = 0;
				#endif

				//debug_containercount++;
				//std::cout << "debug_containercount ++ = " << debug_containercount << "\n";
			}
			container_basicbase::~container_basicbase() {
				//debug_containercount--;
				//std::cout << "debug_containercount -- = " << debug_containercount << "\n";
			}

			void container_basicbase::safety_iteratorversion_Increment() {
				#if aatc_CONFIG_ENABLE_ERRORCHECK_ITERATOR_SAFETY_VERSION_NUMBERS
					safety_iteratorversion++;
				#endif
			}



			iterator_base::iterator_base() :
				firstt(1)
			{}
			iterator_base::iterator_base(const iterator_base& other) :
				firstt(other.firstt),
				cont(other.cont)
			{}



			namespace containerfunctor {
				Base::Base(asIScriptEngine* _engine, Settings* settings) :
					engine(_engine),
					host_settings(settings),
					need_init(1)
				{
					els = enginestorage::Get_ELS(engine);
				}

				Comp::Comp(asIScriptEngine* _engine, Settings* settings) :
					Base(_engine, settings)
				{}
				bool Comp::operator()(const void* lhs, const void* rhs)const {
					if (need_init) {
						(const_cast<Comp*>(this))->need_init = 0;
						(const_cast<Comp*>(this))->handlemode_directcomp = host_settings->handlemode_directcomp;
						(const_cast<Comp*>(this))->func_cmp = host_settings->func_cmp;
					}
					if (handlemode_directcomp) {
						return lhs < rhs;
					}

					bool result;

					asIScriptContext* cc = els->contextcache_Get();
					cc->Prepare(func_cmp);
					cc->SetObject(const_cast<void*>(lhs));
					cc->SetArgObject(0, const_cast<void*>(rhs));
					cc->Execute();
					//result = (bool)cc->GetReturnByte();
					result = (cc->GetReturnDWord() == -1);

					els->contextcache_Return(cc);

					return result;
				}

				Equals::Equals(asIScriptEngine* _engine, Settings* settings) :
					Base(_engine, settings)
				{}
				bool Equals::operator()(const void* lhs, const void* rhs)const {
					if (need_init) {
						(const_cast<Equals*>(this))->need_init = 0;
						(const_cast<Equals*>(this))->handlemode_directcomp = host_settings->handlemode_directcomp;
						(const_cast<Equals*>(this))->func_equals = host_settings->func_equals;
					}
					if (handlemode_directcomp) {
						return lhs == rhs;
					}

					bool result;

					asIScriptContext* cc = els->contextcache_Get();
					cc->Prepare(func_equals);
					cc->SetObject(const_cast<void*>(lhs));
					cc->SetArgObject(0, const_cast<void*>(rhs));
					cc->Execute();
					result = (cc->GetReturnDWord() != 0);

					els->contextcache_Return(cc);

					return result;
				}
				bool Equals::findif_version::operator()(const void* rhs) const {
					return (*f)(target, rhs);
				}

				Hash::Hash(asIScriptEngine* _engine, Settings* settings) :
					Base(_engine, settings)
				{}
				config::t::hash Hash::operator()(const void* ptr) const {
					if (need_init) {
						//need_init = 0;
						//func_hash = host_settings->func_hash;
						//handlemode_directcomp = host_settings->handlemode_directcomp;
						(const_cast<Hash*>(this))->need_init = 0;
						(const_cast<Hash*>(this))->handlemode_directcomp = host_settings->handlemode_directcomp;
						(const_cast<Hash*>(this))->func_hash = host_settings->func_hash;
					}
					if (handlemode_directcomp) {
						return (config::t::hash)ptr;
						//return reinterpret_cast<std::size_t>(ptr);
					}

					config::t::hash result;

					asIScriptContext* cc = els->contextcache_Get();
					cc->Prepare(func_hash);
					cc->SetObject(const_cast<void*>(ptr));
					if (cc->Execute() == asEXECUTION_EXCEPTION) {
						result = 0;
					} else {
						result = cc->GetReturnQWord();
					}
					els->contextcache_Return(cc);

					return result;
				}


			};//namespace containerfunctor
			namespace containerfunctor_map {
				Base::Base(asIScriptEngine* _engine, Settings* settings) :
					engine(_engine),
					host_settings(settings),
					need_init(1)
				{
					els = enginestorage::Get_ELS(engine);
				}

				Comp::Comp(asIScriptEngine* _engine, Settings* settings) :
					Base(_engine,settings)
				{}
				bool Comp::operator()(const aatc::common::primunion& lhs, const aatc::common::primunion& rhs)const {
					if (need_init) {
						(const_cast<Comp*>(this))->need_init = 0;
						(const_cast<Comp*>(this))->handlemode_directcomp = host_settings->handlemode_directcomp;
						(const_cast<Comp*>(this))->datahandlingid_key = host_settings->datahandlingid_key;
						(const_cast<Comp*>(this))->primitiveid_key = host_settings->primitiveid_key;
						(const_cast<Comp*>(this))->func_cmp = host_settings->func_cmp;
					}
					if (datahandlingid_key == aatc::common::DATAHANDLINGTYPE::PRIMITIVE) {
						switch (primitiveid_key) {
						case aatc::common::PRIMITIVE_TYPE::INT8: { return lhs.i8 < rhs.i8; }
						case aatc::common::PRIMITIVE_TYPE::INT16: { return lhs.i16 < rhs.i16; }
						case aatc::common::PRIMITIVE_TYPE::INT32: { return lhs.i32 < rhs.i32; }
						case aatc::common::PRIMITIVE_TYPE::INT64: { return lhs.i64 < rhs.i64; }
						case aatc::common::PRIMITIVE_TYPE::UINT8: { return lhs.ui8 < rhs.ui8; }
						case aatc::common::PRIMITIVE_TYPE::UINT16: { return lhs.ui16 < rhs.ui16; }
						case aatc::common::PRIMITIVE_TYPE::UINT32: { return lhs.ui32 < rhs.ui32; }
						case aatc::common::PRIMITIVE_TYPE::UINT64: { return lhs.ui64 < rhs.ui64; }
						case aatc::common::PRIMITIVE_TYPE::FLOAT32: { return lhs.f32 < rhs.f32; }
						case aatc::common::PRIMITIVE_TYPE::FLOAT64: { return lhs.f64 < rhs.f64; }
						};
					}
					if (datahandlingid_key == aatc::common::DATAHANDLINGTYPE::STRING) {
						return (*((config::t::string*)lhs.ptr)) < (*((config::t::string*)rhs.ptr));
					}
					if (handlemode_directcomp) {
						return lhs.ptr < rhs.ptr;
					}

					bool result;

					asIScriptContext* cc = els->contextcache_Get();
					cc->Prepare(func_cmp);
					cc->SetObject(const_cast<void*>(lhs.ptr));
					cc->SetArgObject(0, const_cast<void*>(rhs.ptr));
					cc->Execute();
					//result = (bool)cc->GetReturnByte();
					result = (cc->GetReturnDWord() == -1);

					els->contextcache_Return(cc);

					return result;
				}


				Equals::Equals(asIScriptEngine* _engine, Settings* settings) :
					Base(_engine, settings)
				{}
				bool Equals::operator()(const aatc::common::primunion& lhs, const aatc::common::primunion& rhs)const {
					if (need_init) {
						(const_cast<Equals*>(this))->need_init = 0;
						(const_cast<Equals*>(this))->handlemode_directcomp = host_settings->handlemode_directcomp;
						(const_cast<Equals*>(this))->datahandlingid_key = host_settings->datahandlingid_key;
						(const_cast<Equals*>(this))->primitiveid_key = host_settings->primitiveid_key;
						(const_cast<Equals*>(this))->func_equals = host_settings->func_equals;
					}
					if (datahandlingid_key == aatc::common::DATAHANDLINGTYPE::PRIMITIVE) {
						switch (primitiveid_key) {
						case aatc::common::PRIMITIVE_TYPE::INT8: { return lhs.i8 == rhs.i8; }
						case aatc::common::PRIMITIVE_TYPE::INT16: { return lhs.i16 == rhs.i16; }
						case aatc::common::PRIMITIVE_TYPE::INT32: { return lhs.i32 == rhs.i32; }
						case aatc::common::PRIMITIVE_TYPE::INT64: { return lhs.i64 == rhs.i64; }
						case aatc::common::PRIMITIVE_TYPE::UINT8: { return lhs.ui8 == rhs.ui8; }
						case aatc::common::PRIMITIVE_TYPE::UINT16: { return lhs.ui16 == rhs.ui16; }
						case aatc::common::PRIMITIVE_TYPE::UINT32: { return lhs.ui32 == rhs.ui32; }
						case aatc::common::PRIMITIVE_TYPE::UINT64: { return lhs.ui64 == rhs.ui64; }
						case aatc::common::PRIMITIVE_TYPE::FLOAT32: { return lhs.f32 == rhs.f32; }
						case aatc::common::PRIMITIVE_TYPE::FLOAT64: { return lhs.f64 == rhs.f64; }
						};
					}
					if (datahandlingid_key == aatc::common::DATAHANDLINGTYPE::STRING) {
						return (*((config::t::string*)lhs.ptr)) == (*((config::t::string*)rhs.ptr));
					}
					if (handlemode_directcomp) {
						return lhs.ptr == rhs.ptr;
					}

					bool result;

					asIScriptContext* cc = els->contextcache_Get();
					cc->Prepare(func_equals);
					cc->SetObject(const_cast<void*>(lhs.ptr));
					cc->SetArgObject(0, const_cast<void*>(rhs.ptr));
					cc->Execute();
					result = (cc->GetReturnDWord() != 0);

					els->contextcache_Return(cc);

					return result;
				}

				Hash::Hash(asIScriptEngine* _engine, Settings* settings) :
					Base(_engine, settings)
				{}
				config::t::hash Hash::operator()(const aatc::common::primunion& pu) const {
					if (need_init) {
						//need_init = 0;
						//func_hash = host_settings->func_hash;
						//handlemode_directcomp = host_settings->handlemode_directcomp;
						(const_cast<Hash*>(this))->need_init = 0;
						(const_cast<Hash*>(this))->handlemode_directcomp = host_settings->handlemode_directcomp;
						(const_cast<Hash*>(this))->datahandlingid_key = host_settings->datahandlingid_key;
						(const_cast<Hash*>(this))->primitiveid_key = host_settings->primitiveid_key;
						(const_cast<Hash*>(this))->func_hash = host_settings->func_hash;
					}
					if (datahandlingid_key == aatc::common::DATAHANDLINGTYPE::PRIMITIVE) {
						switch (primitiveid_key) {
						case aatc::common::PRIMITIVE_TYPE::INT8: { return (config::t::hash)pu.i8; }
						case aatc::common::PRIMITIVE_TYPE::INT16: { return (config::t::hash)pu.i16; }
						case aatc::common::PRIMITIVE_TYPE::INT32: { return (config::t::hash)pu.i32; }
						case aatc::common::PRIMITIVE_TYPE::INT64: { return (config::t::hash)pu.i64; }
						case aatc::common::PRIMITIVE_TYPE::UINT8: { return (config::t::hash)pu.ui8; }
						case aatc::common::PRIMITIVE_TYPE::UINT16: { return (config::t::hash)pu.ui16; }
						case aatc::common::PRIMITIVE_TYPE::UINT32: { return (config::t::hash)pu.ui32; }
						case aatc::common::PRIMITIVE_TYPE::UINT64: { return (config::t::hash)pu.ui64; }
						case aatc::common::PRIMITIVE_TYPE::FLOAT32: { return (config::t::hash)pu.f32; }
						case aatc::common::PRIMITIVE_TYPE::FLOAT64: { return (config::t::hash)pu.f64; }
						};
					}
					if (datahandlingid_key == aatc::common::DATAHANDLINGTYPE::STRING) {
						return aatc::hash::hashfunctor<config::t::string>()(*((config::t::string*)pu.ptr));
					}
					if (handlemode_directcomp) {
						return (config::t::hash)pu.ptr;
						//return reinterpret_cast<std::size_t>(ptr);
					}

					config::t::hash result;

					asIScriptContext* cc = els->contextcache_Get();
					cc->Prepare(func_hash);
					cc->SetObject(const_cast<void*>(pu.ptr));
					if (cc->Execute() == asEXECUTION_EXCEPTION) {
						result = 0;
					} else {
						result = cc->GetReturnQWord();
					}
					els->contextcache_Return(cc);

					return result;
				}
				//MAP FUNCTORS
				//MAP FUNCTORS
				//MAP FUNCTORS
			};//namespace containerfunctor_map



			namespace scriptcmpfunctor_internal {
				void functor_SetArgs<config::t::int8>::operator()(asIScriptContext* context, config::t::int8 l, config::t::int8 r) const{
					context->SetArgByte(0, l);
					context->SetArgByte(1, r);
				}
				void functor_SetArgs<config::t::uint8>::operator()(asIScriptContext* context, config::t::uint8 l, config::t::uint8 r)  const{
					context->SetArgByte(0, l);
					context->SetArgByte(1, r);
				}
				void functor_SetArgs<config::t::int16>::operator()(asIScriptContext* context, config::t::int16 l, config::t::int16 r)  const{
					context->SetArgWord(0, l);
					context->SetArgWord(1, r);
				}
				void functor_SetArgs<config::t::uint16>::operator()(asIScriptContext* context, config::t::uint16 l, config::t::uint16 r)  const{
					context->SetArgWord(0, l);
					context->SetArgWord(1, r);
				}
				void functor_SetArgs<config::t::int32>::operator()(asIScriptContext* context, config::t::int32 l, config::t::int32 r)  const{
					context->SetArgDWord(0, l);
					context->SetArgDWord(1, r);
				}
				void functor_SetArgs<config::t::uint32>::operator()(asIScriptContext* context, config::t::uint32 l, config::t::uint32 r)  const{
					context->SetArgDWord(0, l);
					context->SetArgDWord(1, r);
				}
				void functor_SetArgs<config::t::int64>::operator()(asIScriptContext* context, config::t::int64 l, config::t::int64 r)  const{
					context->SetArgQWord(0, l);
					context->SetArgQWord(1, r);
				}
				void functor_SetArgs<config::t::uint64>::operator()(asIScriptContext* context, config::t::uint64 l, config::t::uint64 r)  const{
					context->SetArgQWord(0, l);
					context->SetArgQWord(1, r);
				}
				void functor_SetArgs<config::t::float32>::operator()(asIScriptContext* context, config::t::float32 l, config::t::float32 r)  const{
					context->SetArgFloat(0, l);
					context->SetArgFloat(1, r);
				}
				void functor_SetArgs<config::t::float64>::operator()(asIScriptContext* context, config::t::float64 l, config::t::float64 r)  const{
					context->SetArgDouble(0, l);
					context->SetArgDouble(1, r);
				}

				void functor_SetArgs<dummytype_object>::operator()(asIScriptContext* context, void* l, void* r)const {
					context->SetArgObject(0, l);
					context->SetArgObject(1, r);
				}
				void functor_SetArgs<dummytype_handle>::operator()(asIScriptContext* context, void* l, void* r)const {
					context->SetArgObject(0, l);
					context->SetArgObject(1, r);
				}
			}//namespace scriptcmpfunctor_internal



		};//namespace shared
	};//namespace container
};//namespace aatc
END_AS_NAMESPACE