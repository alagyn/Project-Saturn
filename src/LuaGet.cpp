#include "LuaState.hpp"

using namespace saturn;

LuaState::LuaGet::LuaGet(lua_State* L) :
	L(L)
{

}

LuaType LuaState::LuaGet::global(const std::string& name)
{
	return convertLuaType(lua_getglobal(L, name.c_str()));
}

LuaType LuaState::LuaGet::index(int tableIdx, LuaInt idx)
{
	return convertLuaType(lua_geti(L, tableIdx, idx));
}

LuaType LuaState::LuaGet::key(int tableIdx, const std::string& key)
{
	return convertLuaType(lua_getfield(L, tableIdx, key.c_str()));
}

LuaType LuaState::LuaGet::key(int tableIdx)
{
	return convertLuaType(lua_gettable(L, tableIdx));
}

bool LuaState::LuaGet::metatable(int tableIdx)
{
	return lua_getmetatable(L, tableIdx);
}

LuaType LuaState::LuaGet::type(int idx)
{
	return convertLuaType(lua_type(L, idx));
}

void LuaState::LuaGet::length(int idx)
{
	lua_len(L, idx);
}

void LuaState::LuaGet::rawLength(int idx)
{
	lua_rawlen(L, idx);
}

LuaType LuaState::LuaGet::rawIndex(int tableIdx, LuaInt idx)
{
	return convertLuaType(lua_rawgeti(L, tableIdx, idx));
}

LuaType LuaState::LuaGet::rawKey(int tableIdx)
{
	return convertLuaType(lua_rawget(L, tableIdx));
}
