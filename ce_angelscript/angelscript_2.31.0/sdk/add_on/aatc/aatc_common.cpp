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



#include "aatc_common.hpp"
#include "aatc_enginestorage.hpp"

#include "stdarg.h"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace common {



		std_Spinlock::std_Spinlock() : state(1) {}
		void std_Spinlock::lock(){while (state.exchange(0, std::memory_order_acquire) == 0);}
		void std_Spinlock::unlock(){state.store(1, std::memory_order_release);}






		primunion primunion_defaultvalue = primunion();






		//refcounted and gc basetype
		//refcounted and gc basetype
		basetype_refcounted::basetype_refcounted() :
			refcount(1)
		{}
		basetype_refcounted::~basetype_refcounted(){}
		void basetype_refcounted::refcount_Add(){
			asAtomicInc(refcount);
		}
		void basetype_refcounted::refcount_Release(){
			if (asAtomicDec(refcount) == 0){
				delete this;
			}
		}

		basetype_refcounted_GC::basetype_refcounted_GC():
			refCount(1),
			gcFlag(0)
		{}
		basetype_refcounted_GC::~basetype_refcounted_GC(){}

		void basetype_refcounted_GC::refcount_Add(){
			gcFlag = false;
			asAtomicInc(refCount);
		}
		void basetype_refcounted_GC::refcount_Release(){
			gcFlag = false;
			if (asAtomicDec(refCount) == 0){
				delete this;
			}
		}
		int basetype_refcounted_GC::GetRefCount(){return refCount;}
		void basetype_refcounted_GC::SetGCFlag(){gcFlag = true;}
		bool basetype_refcounted_GC::GetGCFlag(){return gcFlag;}
		void basetype_refcounted_GC::EnumReferences(asIScriptEngine *engine){}
		void basetype_refcounted_GC::ReleaseAllReferences(asIScriptEngine* engine){}
		//refcounted and gc basetype
		//refcounted and gc basetype



		bool templatecallback_func::templated_singleparam(asITypeInfo *ot, bool &dontGarbageCollect){
			return templatecallback_func::typeidd(ot, ot->GetSubTypeId(), dontGarbageCollect);
		}
		bool templatecallback_func::map(asITypeInfo *ot, bool &dontGarbageCollect){
			int typeId_key = ot->GetSubTypeId(0);
			int typeId_value = ot->GetSubTypeId(1);

			bool dont_gc_key = 0;
			bool dont_gc_value = 0;
			bool result_key = templatecallback_func::typeidd(ot, typeId_key, dont_gc_key);
			bool result_value = templatecallback_func::typeidd(ot, typeId_value, dont_gc_value);

			dontGarbageCollect = dont_gc_key && dont_gc_value;

			return result_key && result_value;
		}
		bool templatecallback_func::typeidd(asITypeInfo *ot, int typeId, bool &dontGarbageCollect){
			if ((typeId & asTYPEID_MASK_OBJECT) && !(typeId & asTYPEID_OBJHANDLE)){
				asITypeInfo *subtype = ot->GetEngine()->GetTypeInfoById(typeId);
				asDWORD flags = subtype->GetFlags();
				if ((flags & asOBJ_VALUE) && !(flags & asOBJ_POD)){
					// Verify that there is a default constructor
					bool found = false;
					for (asUINT n = 0; n < subtype->GetBehaviourCount(); n++){
						asEBehaviours beh;
						asIScriptFunction *func = subtype->GetBehaviourByIndex(n, &beh);
						if (beh != asBEHAVE_CONSTRUCT){ continue; }

						if (func->GetParamCount() == 0){
							// Found the default constructor
							found = true;
							break;
						}
					}

					if (!found){
						// There is no default constructor
						return false;
					}
				}
				else if ((flags & asOBJ_REF)){
					bool found = false;

					// If value assignment for ref type has been disabled then the array
					// can be created if the type has a default factory function
					if (!ot->GetEngine()->GetEngineProperty(asEP_DISALLOW_VALUE_ASSIGN_FOR_REF_TYPE)){
						// Verify that there is a default factory
						for (asUINT n = 0; n < subtype->GetFactoryCount(); n++){
							asIScriptFunction *func = subtype->GetFactoryByIndex(n);
							if (func->GetParamCount() == 0){
								// Found the default factory
								found = true;
								break;
							}
						}
					}

					if (!found){
						// No default factory
						return false;
					}
				}

				// If the object type is not garbage collected then the array also doesn't need to be
				if (!(flags & asOBJ_GC)){
					dontGarbageCollect = true;
				}
			}
			else if (!(typeId & asTYPEID_OBJHANDLE)){
				// Arrays with primitives cannot form circular references,
				// thus there is no need to garbage collect them
				dontGarbageCollect = true;
			}

			return 1;
		}



		script_Funcpointer::script_Funcpointer() :
			//dedicated_context(NULL),
			ready(0),
			func(NULL),
			so(NULL)
		{
		}
		script_Funcpointer::~script_Funcpointer(){
			//ReleaseRef();
		}

		script_Funcpointer* script_Funcpointer::Factory(){
			return new script_Funcpointer();
		}

		bool script_Funcpointer::Set(config::t::string _funcname){
			asIScriptContext* ctx = asGetActiveContext();
			engine = ctx->GetEngine();

			funcname = _funcname;
			ready = 0;
			func = NULL;
			is_thiscall = 0;
			so = NULL;

			const char* funcname_c = funcname.c_str();

			//application registered global functions
			func = engine->GetGlobalFunctionByDecl(funcname_c);
			//not found? script module global functions
			if (!func){
				for (uint_fast32_t i = 0; i < engine->GetModuleCount(); i++){
					func = engine->GetModuleByIndex(i)->GetFunctionByName(funcname_c);
					if (func){ break; }
				}
			}

			if (func){
				ready = 1;
			}
			return ready;
		}
		bool script_Funcpointer::Set(config::t::string _funcname, void* ref, int tid){
			funcname = _funcname;
			ready = 0;
			func = NULL;
			is_thiscall = 1;

			const char* funcname_c = funcname.c_str();

			if (ref){
				if ((tid & asTYPEID_MASK_OBJECT) && (tid & asTYPEID_OBJHANDLE)){//must be not primitive and a handle
					so = static_cast<asIScriptObject*>(*((void**)ref));

					func = so->GetObjectType()->GetMethodByName(funcname_c);
					if (func){
						ready = 1;
					}
				}else{//error
					asIScriptContext* ctx = asGetActiveContext();
					engine = ctx->GetEngine();

					char textbuf[1024];
					RegistrationState::Format_static(textbuf,1024, aatc_errormessage_funcpointer_nothandle,engine->GetTypeInfoById(tid)->GetName());
					ctx->SetException(textbuf);
				}
			}
			return ready;
		}
		void script_Funcpointer::Clear(){
			ready = 0;
		}

		void script_Funcpointer::Prepare(asIScriptContext* context){
			if (ready){
				context->Prepare(func);
				if (is_thiscall){context->SetObject(so);}
			}
		}
		void script_Funcpointer::Execute(asIScriptContext* context){
			if (ready){
				context->Execute();
			}
		}

		void script_Funcpointer::scriptsidecall_CallVoid(){
			enginestorage::engine_level_storage* els = enginestorage::Get_ELS(asGetActiveContext()->GetEngine());
			asIScriptContext* c = els->contextcache_Get();
				Prepare(c);
				Execute(c);
			els->contextcache_Return(c);
		}



		namespace errorprint {
			namespace container {
				void missingfunctions_operation_missing(const char* name_container, const char* name_content, const char* name_operation) {
					#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_EXCEPTIONS
						char msg[1000];
						RegistrationState::Format_static(msg, 1000, aatc_errormessage_container_missingfunctions_formatting, aatc_errormessage_container_missingfunctions_formatting_param1, aatc_errormessage_container_missingfunctions_formatting_param2, aatc_errormessage_container_missingfunctions_formatting_param3);
						asGetActiveContext()->SetException(msg);
					#endif
				}
				void access_empty(const char* name_container, const char* name_content, const char* name_operation) {
					#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_EXCEPTIONS
						char msg[1000];
						RegistrationState::Format_static(msg, 1000, aatc_errormessage_container_access_empty_formatting, aatc_errormessage_container_access_empty_formatting_param1, aatc_errormessage_container_access_empty_formatting_param2, aatc_errormessage_container_access_empty_formatting_param3);
						asGetActiveContext()->SetException(msg);
					#endif
				}
				void access_bounds(config::t::sizetype index, config::t::sizetype size, const char* name_container, const char* name_content, const char* name_operation) {
					#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_EXCEPTIONS
						char msg[1000];
						RegistrationState::Format_static(msg, 1000,
							aatc_errormessage_container_access_bounds_formatting,
							aatc_errormessage_container_access_bounds_formatting_param1,
							aatc_errormessage_container_access_bounds_formatting_param2,
							aatc_errormessage_container_access_bounds_formatting_param3,
							aatc_errormessage_container_access_bounds_formatting_param4,
							aatc_errormessage_container_access_bounds_formatting_param5
							);
						asGetActiveContext()->SetException(msg);
					#endif
				}
				void iterator_invalid() {
					#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_EXCEPTIONS
						asGetActiveContext()->SetException(config::errormessage::iterator::is_invalid);
					#endif
				}
			};
			namespace iterator {
				void container_modified() {
					#if aatc_CONFIG_ENABLE_ERRORCHECK_RUNTIME_EXCEPTIONS
						asGetActiveContext()->SetException(config::errormessage::iterator::container_modified);
					#endif
				}
			};
		};




		DATAHANDLINGTYPE Determine_Datahandlingtype(asIScriptEngine* engine,config::t::uint32 astypeid){
			if(astypeid == engine->GetStringFactoryReturnTypeId()){
				return DATAHANDLINGTYPE::STRING;
			}
			if(astypeid & asTYPEID_MASK_OBJECT){
				if(astypeid & asTYPEID_OBJHANDLE){
					return DATAHANDLINGTYPE::HANDLE;
				} else{
					return DATAHANDLINGTYPE::OBJECT;
				}
			} else{
				return DATAHANDLINGTYPE::PRIMITIVE;
			}
		}
		PRIMITIVE_TYPE Determine_Primitivetype(config::t::uint32 astypeid){
			switch(astypeid){
				case asTYPEID_BOOL:{return PRIMITIVE_TYPE::INT8; }
				case asTYPEID_INT8:{return PRIMITIVE_TYPE::INT8; }
				case asTYPEID_INT16:{return PRIMITIVE_TYPE::INT16; }
				case asTYPEID_INT32:{return PRIMITIVE_TYPE::INT32; }
				case asTYPEID_INT64:{return PRIMITIVE_TYPE::INT64; }
				case asTYPEID_UINT8:{return PRIMITIVE_TYPE::UINT8; }
				case asTYPEID_UINT16:{return PRIMITIVE_TYPE::UINT16; }
				case asTYPEID_UINT32:{return PRIMITIVE_TYPE::UINT32; }
				case asTYPEID_UINT64:{return PRIMITIVE_TYPE::UINT64; }
				case asTYPEID_FLOAT:{return PRIMITIVE_TYPE::FLOAT32; }
				case asTYPEID_DOUBLE:{return PRIMITIVE_TYPE::FLOAT64; }
				default: {return PRIMITIVE_TYPE::INT8; }
			};
		}



		void* primunion::Get_Ptr_To_Primitive_Type(PRIMITIVE_TYPE primtype){
			switch(primtype){
				case PRIMITIVE_TYPE::INT8:{return &i8; }
				case PRIMITIVE_TYPE::INT16:{return &i16; }
				case PRIMITIVE_TYPE::INT32:{return &i32; }
				case PRIMITIVE_TYPE::INT64:{return &i64; }
				case PRIMITIVE_TYPE::UINT8:{return &ui8; }
				case PRIMITIVE_TYPE::UINT16:{return &ui16; }
				case PRIMITIVE_TYPE::UINT32:{return &ui32; }
				case PRIMITIVE_TYPE::UINT64:{return &ui64; }
				case PRIMITIVE_TYPE::FLOAT32:{return &f32; }
				case PRIMITIVE_TYPE::FLOAT64:{return &f64; }
			};
			return nullptr;
		}
		const void* primunion::Get_Ptr_To_Primitive_Type_const(PRIMITIVE_TYPE primtype)const{
			return const_cast<primunion*>(this)->Get_Ptr_To_Primitive_Type(primtype);
			//return const_cast<void*>(Get_Ptr_To_Primitive_Type(primtype));
		}

		void primunion::From_voidptr_to_primitive(void* target, PRIMITIVE_TYPE primtype) {
			switch (primtype) {
				case common::PRIMITIVE_TYPE::INT8: { i8 = *((config::t::int8*)target); break; }
				case common::PRIMITIVE_TYPE::INT16: { i16 = *((config::t::int16*)target); break; }
				case common::PRIMITIVE_TYPE::INT32: { i32 = *((config::t::int32*)target); break; }
				case common::PRIMITIVE_TYPE::INT64: { i64 = *((config::t::int64*)target); break; }
				case common::PRIMITIVE_TYPE::UINT8: { ui8 = *((config::t::uint8*)target); break; }
				case common::PRIMITIVE_TYPE::UINT16: { ui16 = *((config::t::uint16*)target); break; }
				case common::PRIMITIVE_TYPE::UINT32: { ui32 = *((config::t::uint32*)target); break; }
				case common::PRIMITIVE_TYPE::UINT64: { ui64 = *((config::t::uint64*)target); break; }
				case common::PRIMITIVE_TYPE::FLOAT32: { f32 = *((config::t::float32*)target); break; }
				case common::PRIMITIVE_TYPE::FLOAT64: { f64 = *((config::t::float64*)target); break; }
			};
		}

		void primunion::Init(){
			ui32 = 0;
			ptr = nullptr;
		}





		RegistrationState::RegistrationState(asIScriptEngine* engine):
			engine(engine),
			error(0)
		{}
		void RegistrationState::Format(const char* msg, ...) {
			va_list argptr;
			va_start(argptr, msg);

			#if __STDC_WANT_SECURE_LIB__
				vsprintf_s(textbuf, RegistrationState::bufsize, msg, argptr);
			#else
				vsprintf(textbuf, msg, argptr);
			#endif

			va_end(argptr);
		}
		void RegistrationState::Format_static(char* buffer, int buffer_size, const char* msg, ...) {
			va_list argptr;
			va_start(argptr, msg);

			#if __STDC_WANT_SECURE_LIB__
				vsprintf_s(buffer, buffer_size, msg, argptr);
			#else
				vsprintf(buffer, msg, argptr);
			#endif

			va_end(argptr);
		}



	};//namespace common
};//namespace aatc
END_AS_NAMESPACE