#include "LuaContext.hpp"

using namespace saturn;

LuaContext::LuaGet::LuaGet(lua_State* L) :
	L(L)
{

}

LuaType LuaContext::LuaGet::global(const std::string& name)
{
	return convertLuaType(lua_getglobal(L, name.c_str()));
}

LuaType LuaContext::LuaGet::index(int tableIdx, LuaInt idx)
{
	return convertLuaType(lua_geti(L, tableIdx, idx));
}

LuaType LuaContext::LuaGet::key(int tableIdx, const std::string& key)
{
	return convertLuaType(lua_getfield(L, tableIdx, key.c_str()));
}

LuaType LuaContext::LuaGet::key(int tableIdx)
{
	return convertLuaType(lua_gettable(L, tableIdx));
}

bool LuaContext::LuaGet::metatable(int tableIdx)
{
	return lua_getmetatable(L, tableIdx);
}

LuaType LuaContext::LuaGet::type(int idx)
{
	return convertLuaType(lua_type(L, idx));
}

void LuaContext::LuaGet::length(int idx)
{
	lua_len(L, idx);
}

void LuaContext::LuaGet::rawLength(int idx)
{
	lua_rawlen(L, idx);
}

LuaType LuaContext::LuaGet::rawIndex(int tableIdx, LuaInt idx)
{
	return convertLuaType(lua_rawgeti(L, tableIdx, idx));
}

LuaType LuaContext::LuaGet::rawKey(int tableIdx)
{
	return convertLuaType(lua_rawget(L, tableIdx));
}
