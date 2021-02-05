#include "LuaContext.hpp"

using namespace saturn;

bool LuaContext::is_boolean(int idx)
{
	return lua_isboolean(L, idx);
}

bool LuaContext::is_cFunction(int idx)
{
	return lua_iscfunction(L, idx);
}

bool LuaContext::is_function(int idx)
{
	return lua_isfunction(L, idx);
}

bool LuaContext::is_integer(int idx)
{
	return lua_isinteger(L, idx);
}

bool LuaContext::is_pointer(int idx)
{
	return lua_islightuserdata(L, idx);
}

bool LuaContext::is_nil(int idx)
{
	return lua_isnil(L, idx);
}

bool LuaContext::is_invalid(int idx)
{
	return lua_isnone(L, idx);
}

bool LuaContext::is_invalidOrNil(int idx)
{
	return lua_isnoneornil(L, idx);
}

bool LuaContext::is_number(int idx)
{
	return lua_isnumber(L, idx);
}

bool LuaContext::is_string(int idx)
{
	return lua_isstring(L, idx);
}

bool LuaContext::is_table(int idx)
{
	return lua_istable(L, idx);
}

bool LuaContext::is_thread(int idx)
{
	return lua_isthread(L, idx);
}

bool LuaContext::is_userdata(int idx)
{
	return lua_isuserdata(L, idx);
}

bool LuaContext::is_yieldable(int idx)
{
	return lua_isyieldable(L);
}
