//#include "angelscript.h"
#include "ce_angelscript/ce_angelscript.h"

#include <iostream>
#include <string>

#include "ASStreams.h"
#include "ASOStream.h"

void DefaultConstructOStream( void* pMemory )
{
	asIScriptContext* pContext = asGetActiveContext();

	if( pContext )
		pContext->SetException( "OStream is a non-constructible object type" );

	return;
}

void DestructOStream( std::ostream* pStream )
{
	pStream->~basic_ostream();
}

std::streamsize OStream_tellp( std::ostream* pThis )
{
	return pThis->tellp();
}

std::ostream& OStream_seekp( std::ostream* pThis, std::streamsize iPosition )
{
	pThis->seekp( iPosition );

	return *pThis;
}

std::ostream& OStream_seekp( std::ostream* pThis, std::streamsize iOffset, int iWay )
{
   // CA, 20151223, this fails under g++ 5.2.1 20151010 , applied typecast for iWay to fix
	pThis->seekp( iOffset, (std::ios_base::seekdir)iWay );

	return *pThis;
}

int RegisterOStream( asIScriptEngine* pEngine )
{
	const char* pszObjectName = "OStream";

	int iResult = pEngine->RegisterObjectType( pszObjectName, sizeof( std::ostream ),
								 asOBJ_VALUE | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectBehaviour( pszObjectName, asBEHAVE_CONSTRUCT, "void OStream()",
													asFUNCTION( DefaultConstructOStream ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectBehaviour( pszObjectName, asBEHAVE_DESTRUCT, "void DestructOStream()",
													asFUNCTION( DestructOStream ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = RegisterBaseStream<std::ostream>( pEngine, pszObjectName );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& opShl(const string& in szString)",
												 asFUNCTIONPR( std::operator<<, ( std::ostream&, const std::string& ), std::ostream& ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& opShl(bool fValue)",
												 asMETHODPR( std::ostream, operator<<, ( bool ), std::ostream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& opShl(int64 iValue)",
												 asMETHODPR( std::ostream, operator<<, ( long long int ), std::ostream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& opShl(uint64 uiValue)",
												 asMETHODPR( std::ostream, operator<<, ( unsigned long long int ), std::ostream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& opShl(float flValue)",
												 asMETHODPR( std::ostream, operator<<, ( float ), std::ostream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& opShl(double flValue)",
												 asMETHODPR( std::ostream, operator<<, ( double ), std::ostream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "streamsize tellp() const",
												 asFUNCTION( OStream_tellp ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& seekp(streamsize iPos)",
												 asFUNCTIONPR( OStream_seekp, ( std::ostream*, std::streamsize ), std::ostream& ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& seekp(streamsize iOffset, seekdir way)",
												 asFUNCTIONPR( OStream_seekp, ( std::ostream*, std::streamsize, int ), std::ostream& ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "OStream& flush()",
												 asMETHOD( std::ostream, flush ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterGlobalProperty( "OStream cout", &std::cout );

	return iResult;
}
