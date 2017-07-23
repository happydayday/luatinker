
#include <cstdio>
#include <cassert>
#include <cstring>
#include <list>
#include <set>
#include <map>
#include <vector>

#include "test.h"
#include "luaenv.h"

LuaEnv::LuaEnv( const char * path )
: m_Routine( path ),
  m_LuaState( NULL )
{}

LuaEnv::~LuaEnv()
{}

bool LuaEnv::initialize()
{
	m_LuaState = luaL_newstate();
	if ( m_LuaState == NULL )
	{
		printf("LuaEnv::initialize() : new lua_State failed .\n");
		return false;
	}

	// lua脚本路径
	const char * result = std::strrchr( m_Routine.c_str(), '/' );
	assert( result != NULL );
	m_RootPath = std::string( m_Routine.c_str(), result-m_Routine.c_str() );
	// 环境
	this->initEnviroment();

	luatinker::dofile( m_LuaState, m_Routine.c_str() );

	return true;
}

void LuaEnv::finalize()
{
	if ( m_LuaState )
	{
		lua_close( m_LuaState );
		m_LuaState = NULL;
	}
}

void LuaEnv::dofile( const char * file )
{
	luatinker::dofile( m_LuaState, file );
}

bool LuaEnv::addpath( const std::string & path )
{
	std::string new_path = "package.path = package.path .. \"";

	if ( path.empty() )
	{
		return false;
	}

	// 添加new_path
	new_path += ";";
	new_path += path;
	if ( path[path.length() - 1] != '/' )
	{
		new_path += "/";
	}
	new_path += "?.lua\" ";

	// dostring
	luatinker::dostring( m_LuaState, new_path.c_str() );

	return true;
}

void LuaEnv::initEnviroment()
{
	luaopen_base( m_LuaState );
	luaopen_string( m_LuaState );
	luaL_openlibs( m_LuaState );

	this->addpath( m_RootPath );

	// 注册全局函数
	luatinker::def( m_LuaState, "TOINT64", LuaEnv::toInt64 );

	// 注册全局变量
	luatinker::set( m_LuaState, "ENV", this );
	luatinker::set( m_LuaState, "ROOT", m_RootPath.c_str() );

	// 其他注册给lua使用的东西
	this->registering();
}

void LuaEnv::registering()
{
    this->addpath( root() + "/fight" );

	luatinker::class_<base_t>( m_LuaState, "base_t" )
		.def( luatinker::constructor<base_t> )
		.def( "dump", &base_t::dump )
		.prop( "v", &base_t::v )
		;


	luatinker::class_<foo_t>( m_LuaState, "foo_t" )
		.inh<base_t>()
		.def( luatinker::constructor<foo_t, int> )
		.def( "print", &foo_t::print )
		.prop( "a", &foo_t::a )
		;

	luatinker::class_<clazz>( m_LuaState, "clazz" )
		.def( luatinker::constructor<clazz> )
		.defstatic( "static_func", &clazz::static_func )
		;
}
