#ifndef ASSTREAMS_H
#define ASSTREAMS_H

#include <iostream>

class asIScriptEngine;

int RegisterStreams( asIScriptEngine* pEngine );

template<typename STREAM>
bool Stream_good( STREAM* pThis )
{
	return pThis->good();
}

template<typename STREAM>
bool Stream_eof( STREAM* pThis )
{
	return pThis->eof();
}

template<typename STREAM>
bool Stream_fail( STREAM* pThis )
{
	return pThis->fail();
}

template<typename STREAM>
bool Stream_bad( STREAM* pThis )
{
	return pThis->bad();
}

template<typename STREAM>
void Stream_clear( STREAM* pThis )
{
	pThis->clear();
}

template<typename STREAM>
bool Stream_operator_bool( STREAM* pThis )
{
	return !!( *pThis );
}

template<typename STREAM>
int RegisterBaseStream( asIScriptEngine* pEngine, const char* const pszObjectName )
{
	int iResult = pEngine->RegisterObjectMethod( pszObjectName, "bool good() const",
												 asFUNCTION( Stream_good<STREAM> ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "bool eof() const",
											 asFUNCTION( Stream_eof<STREAM> ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "bool fail() const",
												 asFUNCTION( Stream_fail<STREAM> ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "bool bad() const",
												 asFUNCTION( Stream_bad<STREAM> ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "void clear()",
												 asFUNCTION( Stream_clear<STREAM> ), asCALL_CDECL_OBJLAST );

	if( iResult >= 0 )
		iResult = pEngine->RegisterObjectMethod( pszObjectName, "bool opImplConv() const",
												 asFUNCTION( Stream_operator_bool<STREAM> ), asCALL_CDECL_OBJLAST );

	return iResult;
}

#endif //ASSTREAMS_H