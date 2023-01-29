#include "LuaContext.hpp"

using namespace saturn;

LuaType LuaContext::get_global(const std::string& name)
{
	return static_cast<LuaType>(lua_getglobal(L, name.c_str()));
}

LuaType LuaContext::get(int tableIdx, LuaInt idx)
{
	return static_cast<LuaType>(lua_geti(L, tableIdx, idx));
}

LuaType LuaContext::get(int tableIdx, const std::string& key)
{
	return static_cast<LuaType>(lua_getfield(L, tableIdx, key.c_str()));
}

LuaType LuaContext::get(int tableIdx)
{
	return static_cast<LuaType>(lua_gettable(L, tableIdx));
}

//Returns true if mt exists
bool LuaContext::get_metatable(int tableIdx)
{
	return lua_getmetatable(L, tableIdx);
}

LuaType LuaContext::get_raw(int tableIdx, LuaInt idx)
{
	return static_cast<LuaType>(lua_rawgeti(L, tableIdx, idx));
}

LuaType LuaContext::get_raw(int tableIdx)
{
	return static_cast<LuaType>(lua_rawget(L, tableIdx));
}

LuaType LuaContext::get_raw(int tableIdx, const void* p)
{
	return static_cast<LuaType>(lua_rawgetp(L, tableIdx, p));
}

LuaType LuaContext::get_iUserVal(int udIdx, int n)
{
	return static_cast<LuaType>(lua_getiuservalue(L, udIdx, n));
}