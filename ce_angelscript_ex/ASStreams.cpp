//#include "angelscript.h"
#include "ce_angelscript/ce_angelscript.h"

#include <string>
#include <type_traits>

#include "ASStreams.h"

static const std::string SZEOF = { -1 };

// CA, 20151223, this fails under g++ 5.2.1 20151010 , Kubuntu 64bit, commented out as no ill effects observed
// static_assert( std::is_same<std::streamsize, long long>::value, "Stream size is not the expected type!" );

static int RegisterStreamseekdir( asIScriptEngine* pEngine )
{
	const char* pszObjectName = "seekdir";

	int iResult = pEngine->RegisterEnum( pszObjectName );

	if( iResult >= 0 )
		iResult = pEngine->RegisterEnumValue( pszObjectName, "seek_beg", std::ios::beg );

	if( iResult >= 0 )
		iResult = pEngine->RegisterEnumValue( pszObjectName, "seek_cur", std::ios::cur );

	if( iResult >= 0 )
		iResult = pEngine->RegisterEnumValue( pszObjectName, "seek_end", std::ios::end );

	return iResult;
}

int RegisterStreams( asIScriptEngine* pEngine )
{
	int iResult = pEngine->RegisterGlobalProperty( "const string EOF", const_cast<std::string*>( &SZEOF ) );

	if( iResult >= 0 )
		iResult = pEngine->RegisterTypedef( "streamsize", "int64" );

	if( iResult >= 0 )
		iResult = RegisterStreamseekdir( pEngine );

	return iResult;
}
