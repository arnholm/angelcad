//#include "angelscript.h"
#include "ce_angelscript/ce_angelscript.h"

#include <iostream>
#include <string>

#include "ASStreams.h"
#include "ASIStream.h"

void DefaultConstructIStream( void* pMemory )
{
	asIScriptContext* pContext = asGetActiveContext();

	if( pContext )
		pContext->SetException( "IStream is a non-constructible object type" );

	return;
}

void DestructIStream( std::istream* pStream )
{
	pStream->~basic_istream();
}

std::istream& getline( std::istream& in, std::string& szString, const std::string& szDelim )
{
	const char cDelim = !szDelim.empty() ? szDelim[ 0 ] : '\n';

	return std::getline( in, szString, cDelim );
}

std::istream& ignore( std::istream& in, std::streamsize n, const std::string& szDelim )
{
	return in.ignore( n, !szDelim.empty() ? szDelim[ 0 ] : EOF );
}

std::istream& IStream_clearbuffer( std::istream& in )
{
	char szBuffer[ 128 ];

	while( in.readsome( szBuffer, sizeof( szBuffer ) ) > 0 )
	{
	}

	return in;
}

std::streamsize IStream_tellg( std::istream* pThis )
{
	return pThis->tellg();
}

std::istream& IStream_seekg( std::istream* pThis, std::streamsize iPosition )
{
	pThis->seekg( iPosition );

	return *pThis;
}

std::istream& IStream_seekg( std::istream* pThis, std::streamsize iOffset, int iWay )
{
   // CA, 20151223, this fails under g++ 5.2.1 20151010 , applied typecast for iWay to fix
	pThis->seekg( iOffset, (std::ios_base::seekdir)iWay );

	return *pThis;
}

int RegisterIStream( asIScriptEngine* pEngine )
{
	const char* pszObjectName = "IStream";

	int iResult = pEngine->RegisterObjectType( pszObjectName, sizeof( std::istream ),
								 asOBJ_VALUE | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectBehaviour( pszObjectName, asBEHAVE_CONSTRUCT, "void IStream()",
									  asFUNCTION( DefaultConstructIStream ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectBehaviour( pszObjectName, asBEHAVE_DESTRUCT, "void DestructIStream()",
									  asFUNCTION( DestructIStream ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = RegisterBaseStream<std::istream>( pEngine, pszObjectName );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(string& out szString)",
								   asFUNCTIONPR( std::operator>>, ( std::istream&, std::string& ), std::istream& ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(bool& out fValue)",
												 asMETHODPR( std::istream, operator>>, ( bool& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(int16& out iValue)",
												 asMETHODPR( std::istream, operator>>, ( short& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(uint16& out uiValue)",
												 asMETHODPR( std::istream, operator>>, ( unsigned short& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(int& out iValue)",
												 asMETHODPR( std::istream, operator>>, ( int& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(uint& out uiValue)",
												 asMETHODPR( std::istream, operator>>, ( unsigned int& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(int64& out iValue)",
												 asMETHODPR( std::istream, operator>>, ( long long int& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(uint64& out uiValue)",
												 asMETHODPR( std::istream, operator>>, ( unsigned long long int& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(float& out flValue)",
												 asMETHODPR( std::istream, operator>>, ( float& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& opShr(double& out flValue)",
												 asMETHODPR( std::istream, operator>>, ( double& ), std::istream& ), asCALL_THISCALL );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& getline(string& out szString)",
												 asFUNCTIONPR( std::getline, ( std::istream&, std::string& ), std::istream& ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& getline(string& out szString, const string& in szDelim)",
												 asFUNCTIONPR( getline, ( std::istream&, std::string&, const std::string& ), std::istream& ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& ignore(streamsize n = 1, const string& in szDelim = EOF)",
												 asFUNCTION( ignore ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& clearbuffer()",
												 asFUNCTION( IStream_clearbuffer ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "streamsize tellg() const",
												 asFUNCTION( IStream_tellg ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& seekg(streamsize iPos)",
												 asFUNCTIONPR( IStream_seekg, ( std::istream*, std::streamsize ), std::istream& ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "IStream& seekg(streamsize iOffset, seekdir way)",
												 asFUNCTIONPR( IStream_seekg, ( std::istream*, std::streamsize, int ), std::istream& ), asCALL_CDECL_OBJFIRST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterGlobalProperty( "IStream cin", &std::cin );

	return iResult;
}
