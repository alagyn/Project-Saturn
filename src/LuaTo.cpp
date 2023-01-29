#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace saturn;

//Undefined for non vanilla C functions
LuaCFunc LuaContext::to_cFunc(int idx)
{
	return lua_tocfunction(L, idx);
}

LuaInt LuaContext::to_int(int idx, int* ret)
{
	return lua_tointegerx(L, idx, ret);
}

LuaNum LuaContext::to_num(int idx, int* ret)
{
	return lua_tonumberx(L, idx, ret);
}

bool LuaContext::to_bool(int idx)
{
	return lua_toboolean(L, idx);
}

void* LuaContext::to_pointer(int idx)
{
	return lua_touserdata(L, idx);
}

const char* LuaContext::to_str(int idx, size_t* len)
{
	return lua_tolstring(L, idx, len);
}

LuaThread LuaContext::to_thread(int idx)
{
	return lua_tothread(L, idx);
}