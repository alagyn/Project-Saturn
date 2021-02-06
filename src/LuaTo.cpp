#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace saturn;

//Undefined for non vanilla C functions
LuaCFunc LuaContext::to_luaFunc(int idx)
{
	return lua_tocfunction(L, idx);
}

template<> LuaInt LuaContext::to(int idx)
{
	return lua_tointeger(L, idx);
}

template<> LuaNum LuaContext::to(int idx)
{
	return lua_tonumber(L, idx);
}

template<> bool LuaContext::to(int idx)
{
	return lua_toboolean(L, idx);
}

template<> void* LuaContext::to(int idx)
{
	return lua_touserdata(L, idx);
}

template<> const char* LuaContext::to(int idx)
{
	return lua_tostring(L, idx);
}

