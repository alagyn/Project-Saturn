#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace saturn;

//Undefined for non vanilla C functions
LuaCFunc LuaContext::to_luaFunc(int idx)
{
	return lua_tocfunction(L, idx);
}

template<> LuaInt LuaContext::to(int idx, int* ret)
{
	return lua_tointegerx(L, idx, ret);
}

template<> LuaNum LuaContext::to(int idx, int* ret)
{
	return lua_tonumberx(L, idx, ret);
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
	//TOCHANGE lua_tolstring
	//would require a new arg
	return lua_tostring(L, idx);
}

template<> LuaThread LuaContext::to(int idx)
{
	return lua_tothread(L, idx);
}