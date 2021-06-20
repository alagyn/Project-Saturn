#include "LuaContext.hpp"

using namespace saturn;

LuaType LuaContext::get_global(const std::string& name)
{
	return convertLuaType(lua_getglobal(L, name.c_str()));
}

LuaType LuaContext::get_index(int tableIdx, LuaInt idx)
{
	return convertLuaType(lua_geti(L, tableIdx, idx));
}

LuaType LuaContext::get_key(int tableIdx, const std::string& key)
{
	return convertLuaType(lua_getfield(L, tableIdx, key.c_str()));
}

LuaType LuaContext::get_key(int tableIdx)
{
	return convertLuaType(lua_gettable(L, tableIdx));
}

bool LuaContext::get_metatable(int tableIdx)
{
	return lua_getmetatable(L, tableIdx);
}

LuaType LuaContext::get_type(int idx)
{
	return convertLuaType(lua_type(L, idx));
}

void LuaContext::get_length(int idx)
{
	lua_len(L, idx);
}

void LuaContext::get_rawLength(int idx)
{
	lua_rawlen(L, idx);
}

LuaType LuaContext::get_rawIndex(int tableIdx, LuaInt idx)
{
	return convertLuaType(lua_rawgeti(L, tableIdx, idx));
}

LuaType LuaContext::get_rawKey(int tableIdx)
{
	return convertLuaType(lua_rawget(L, tableIdx));
}

LuaType LuaContext::get_iUserVal(int udIdx, int n)
{
	return convertLuaType(lua_getiuservalue(L, udIdx, n));
}