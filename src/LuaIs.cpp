#include "LuaContext.hpp"

using namespace saturn;


bool LuaContext::is_noneOrNil(int idx)
{
	return lua_type(L, idx) <= 0;
}


bool LuaContext::is_yieldable(LuaThread t)
{
	return lua_isyieldable(t);
}

bool LuaContext::is_invalid(int idx)
{
	return lua_type(L, idx) == LUA_TNONE;
}

bool LuaContext::is_bool(int idx)
{
	return lua_type(L, idx) == LUA_TBOOLEAN;
}

bool LuaContext::is_nil(int idx)
{
	return lua_type(L, idx) == LUA_TNIL;
}

bool LuaContext::is_num(int idx)
{
	return lua_isnumber(L, idx);
}

bool LuaContext::is_string(int idx)
{
	return lua_isstring(L, idx);
}

bool LuaContext::is_table(int idx)
{
	return lua_type(L, idx) == LUA_TTABLE;
}

bool LuaContext::is_userdata(int idx)
{
	return lua_isuserdata(L, idx);
}

bool LuaContext::is_pointer(int idx)
{
	return lua_type(L, idx) == LUA_TLIGHTUSERDATA;		
}

bool LuaContext::is_function(int idx)
{
	return lua_iscfunction(L, idx);
}

bool LuaContext::is_thread(int idx)
{
	return lua_type(L, idx) == LUA_TTHREAD;
}
