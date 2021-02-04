#include "LuaContext.hpp"

using namespace saturn;

LuaContext::LuaSet::LuaSet(lua_State* L) :
	L(L)
{

}

void LuaContext::LuaSet::global(const std::string& name)
{
	lua_setglobal(L, name.c_str());
}

//Stack: -1 = val
void LuaContext::LuaSet::key(int tableIdx, const std::string& key)
{
	lua_setfield(L, tableIdx, key.c_str());
}

//Stack: -2 = key, -1 = val
//Pops both
void LuaContext::LuaSet::key(int tableIdx)
{
	lua_settable(L, tableIdx);
}

//Stack: -1 = val
void LuaContext::LuaSet::index(int tableIdx, LuaInt idx)
{
	lua_seti(L, tableIdx, idx);
}

//Stack: -1 = metatable
void LuaContext::LuaSet::metatable(int tableIdx)
{
	lua_setmetatable(L, tableIdx);
}

//Stack: -2 = key, -1 = val
void LuaContext::LuaSet::rawKey(int tableIdx)
{
	lua_rawset(L, tableIdx);
}

//Stack: -1 = val
void LuaContext::LuaSet::rawIndex(int tableIdx, LuaInt idx)
{
	lua_rawseti(L, tableIdx, idx);
}