#include "LuaState.hpp"
#include "LuaExceptions.hpp"

LuaState::LuaLoader::LuaLoader(lua_State* L) :
	L(L)
{

}

void LuaState::LuaLoader::stdLibs()
{
	luaL_openlibs(L);
}

void LuaState::LuaLoader::callSetup()
{
	int error = lua_pcall(L, 0, 0, 0);
	if(error)
	{
		throw LuaLoadError(lua_tostring(L, -1));
	}
}

void LuaState::LuaLoader::file(const std::string& filename, bool setup)
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

void LuaState::LuaLoader::string(const std::string& s, bool setup)
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