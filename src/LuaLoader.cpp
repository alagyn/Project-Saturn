#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace saturn;
/*
LuaContext::LuaLoader::LuaLoader(lua_State* L) :
	L(L)
{

}

void LuaContext::LuaLoader::string(const std::string& s, bool setup)
{
	if(luaL_loadstring(L, s.c_str()))
	{
		throw LuaLoadError(lua_tostring(L, -1));
	}

	if(setup)
	{
		callSetup();
	}
}
*/


void LuaContext::load_stdLibs()
{
	luaL_openlibs(L);
}

void LuaContext::callSetup()
{
	int error = lua_pcall(L, 0, 0, 0);
	if(error)
	{
		throw LuaLoadError(lua_tostring(L, -1));
	}
}

void LuaContext::load_file(const std::string& filename, bool setup)
{
	if(luaL_loadfile(L, filename.c_str()))
	{
		throw LuaLoadError(lua_tostring(L, -1));
	}

	if(setup)
	{
		callSetup();
	}
}
