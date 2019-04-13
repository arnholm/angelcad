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



#include "aatc_enginestorage.hpp"

#include "string.h"



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace enginestorage {


		engine_level_storage::engine_level_storage(asIScriptEngine* _engine) :
			engine(_engine)
		{}
		engine_level_storage::~engine_level_storage(){}

		template_specific_storage* containertype_specific_storage::GetTemplateSpecificStorage(config::t::uint32 id){
			template_specific_storage* result;

			template_specific_storages_lock.lock();
				tmap_tss::iterator it = template_specific_storages.find(id);
				if (it == template_specific_storages.end()){
					result = new template_specific_storage(this,id);
					template_specific_storages.insert(tpair_tss(id, result));
				}else{
					result = it->second;
				}
			template_specific_storages_lock.unlock();

			return result;
		}
		containertype_specific_storage* engine_level_storage::GetContainerTypeSpecificStorage(config::t::uint32 id){
			return &(containertype_specific_storages[id]);
		}

		containertype_specific_storage::~containertype_specific_storage(){
			for (auto it = template_specific_storages.begin(); it != template_specific_storages.end(); it++){
				const auto& pp = *it;
				delete pp.second;
			}
		}

		void engine_level_storage::Clean(){
			for (auto it = context_cache.begin(); it != context_cache.end(); it++){
				auto* a = *it;
				a->Release();

			}
			context_cache.clear();
		}

		template_specific_storage::template_specific_storage(containertype_specific_storage* ctss,config::t::uint32 subtypeid) :
			ctss(ctss),
			func_equals(NULL),
			func_cmp(NULL),
			func_hash(NULL)
		{
			asIScriptEngine* engine = ctss->els->engine;
			asITypeInfo* typeinfo = engine->GetTypeInfoById(subtypeid);

			//get opEquals or opCmp function for this type to be stored

			bool mustBeConst = (subtypeid & asTYPEID_HANDLETOCONST) ? true : false;

			if (typeinfo){
				for (asUINT i = 0; i < typeinfo->GetMethodCount(); i++){
					asIScriptFunction *func = typeinfo->GetMethodByIndex(i);

					asDWORD flags = 0;
					int returnTypeId = func->GetReturnTypeId(&flags);

					if(func->GetParamCount() == 0){
						if(strcmp(func->GetName(), config::scriptname::method::content::hash) == 0){
							if((returnTypeId == asTYPEID_UINT64) || (returnTypeId == asTYPEID_UINT32) || (returnTypeId == asTYPEID_UINT16) || (returnTypeId == asTYPEID_UINT8)){
								func_hash = func;
							}
						}
					}
					if (func->GetParamCount() == 1 && (!mustBeConst || func->IsReadOnly())){

						// The method must not return a reference
						if (flags != asTM_NONE)
							continue;

						// opCmp returns an int and opEquals returns a bool
						bool isCmp = false, isEq = false;
						if (returnTypeId == asTYPEID_INT32 && strcmp(func->GetName(), "opCmp") == 0){
							isCmp = true;
						}
						if (returnTypeId == asTYPEID_BOOL && strcmp(func->GetName(), "opEquals") == 0){
							isEq = true;
						}

						if(!isCmp && !isEq){
							continue;
						}


						// The parameter must either be a reference to the subtype or a handle to the subtype
						int paramTypeId;
						func->GetParam(0, &paramTypeId, &flags);

						if ((paramTypeId & ~(asTYPEID_OBJHANDLE | asTYPEID_HANDLETOCONST)) != (subtypeid &  ~(asTYPEID_OBJHANDLE | asTYPEID_HANDLETOCONST))){
							continue;
						}

						if ((flags & asTM_INREF)){
							if ((paramTypeId & asTYPEID_OBJHANDLE) || (mustBeConst && !(flags & asTM_CONST))){
								continue;
							}
						}else if (paramTypeId & asTYPEID_OBJHANDLE){
							if (mustBeConst && !(paramTypeId & asTYPEID_HANDLETOCONST)){
								continue;
							}
						}else{
							continue;
						}

						if (isCmp){
							func_cmp = func;
						}else if (isEq){
							func_equals = func;
						}
					}
				}
			}

			missing_functions = ctss->func_errorcheck_missing_functions_make_bitfield_for_template(this);
		}

		asIScriptContext* engine_level_storage::contextcache_Get(){
			asIScriptContext* result;

			context_cache_lock.lock();
				if (context_cache.empty()){
					result = engine->CreateContext();
				}else{
					result = context_cache.back();
					context_cache.pop_back();
				}
			context_cache_lock.unlock();

			return result;
		}
		void engine_level_storage::contextcache_Return(asIScriptContext* a){
			context_cache_lock.lock();
				context_cache.push_back(a);
			context_cache_lock.unlock();
		}



		engine_level_storage* Get_ELS(asIScriptEngine* engine){
			return (engine_level_storage*)engine->GetUserData(config::detail::engine_userdata_id);
		}
		asIScriptContext* contextcache_Get(){
			engine_level_storage* els = Get_ELS(asGetActiveContext()->GetEngine());
			return els->contextcache_Get();
		}
		void contextcache_Return(asIScriptContext* c){
			engine_level_storage* els = Get_ELS(asGetActiveContext()->GetEngine());
			els->contextcache_Return(c);
		}

		void engine_cleanup(asIScriptEngine* engine) {
			enginestorage::engine_level_storage* els = enginestorage::Get_ELS(engine);

			els->Clean();
			delete els;
		}

		void enginestorage::engine_level_storage::RegisterFuncdefIfNeeded(std::string const& this_funcdef_def) {
			if (registered_funcdefs.find(this_funcdef_def) == registered_funcdefs.end()) {
				engine->RegisterFuncdef(this_funcdef_def.c_str());

				registered_funcdefs.insert(this_funcdef_def);
			}
		}



	};//namespace enginestorage
};//namespace aatc
END_AS_NAMESPACE