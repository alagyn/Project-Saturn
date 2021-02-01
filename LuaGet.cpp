#include "LuaState.hpp"

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
