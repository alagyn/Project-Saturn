#include "LuaState.hpp"

LuaState::LuaSet::LuaSet(lua_State* L) :
	L(L)
{

}

void LuaState::LuaSet::global(const std::string& name)
{
	lua_setglobal(L, name.c_str());
}