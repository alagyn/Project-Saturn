#include "LuaContext.hpp"

using namespace saturn;


LuaType LuaContext::type(int idx)
{
	return static_cast<LuaType>(lua_type(L, idx));
}

bool LuaContext::is_cFunc(int idx)
{
	return lua_iscfunction(L, idx);
}

bool LuaContext::is_int(int idx)
{
	return lua_isinteger(L, idx);
}

bool LuaContext::is_num(int idx)
{
	return lua_isnumber(L, idx);
}

bool LuaContext::is_str(int idx)
{
	return lua_isstring(L, idx);
}

bool LuaContext::is_userdata(int idx)
{
	return lua_isuserdata(L, idx);
}

bool LuaContext::is_noneOrNil(int idx)
{
	return lua_type(L, idx) <= 0;
}

bool LuaContext::is_yieldable(LuaThread t)
{
	return lua_isyieldable(t);
}
