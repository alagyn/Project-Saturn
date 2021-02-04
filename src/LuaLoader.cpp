#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace saturn;

LuaContext::LuaLoader::LuaLoader(lua_State* L) :
	L(L)
{

}

void LuaContext::LuaLoader::stdLibs()
{
	luaL_openlibs(L);
}

void LuaContext::LuaLoader::callSetup()
{
	int error = lua_pcall(L, 0, 0, 0);
	if(error)
	{
		throw LuaLoadError(lua_tostring(L, -1));
	}
}

void LuaContext::LuaLoader::file(const std::string& filename, bool setup)
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