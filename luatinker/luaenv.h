
#pragma once

#include <string>
#include "stdint.h"
#include "luatinker/luatinker.h"

class LuaEnv
{
public :
	LuaEnv( const char * path );
	virtual ~LuaEnv();

public :

	bool initialize();
	void finalize();

	lua_State * luastate() const { return m_LuaState; }
	const std::string & root() const { return m_RootPath; }

public :
	void dofile( const char * file );
	bool addpath( const std::string & p );

	// µ÷ÓÃluaº¯Êý
	template<typename RVal>
	RVal invoke( const char * func )
	{
		return luatinker::call<RVal>( m_LuaState, func );
	}

	template<typename RVal, typename T1>
	RVal invoke( const char * func, T1 arg )
	{
		return luatinker::call<RVal>( m_LuaState, func, arg );
	}

	template<typename RVal, typename T1, typename T2>
	RVal invoke( const char * func, T1 arg1, T2 arg2 )
	{
		return luatinker::call<RVal>( m_LuaState, func, arg1, arg2 );
	}

	template<typename RVal, typename T1, typename T2, typename T3>
	RVal invoke( const char * func, T1 arg1, T2 arg2, T3 arg3 )
	{
		return luatinker::call<RVal>( m_LuaState, func, arg1, arg2, arg3 );
	}

protected :
	void initEnviroment();
	void registering();
	static int64_t toInt64(  uint32_t number ) { return number; }

protected :
	std::string         m_Routine;      
	std::string         m_RootPath;      
	lua_State *         m_LuaState;
};
