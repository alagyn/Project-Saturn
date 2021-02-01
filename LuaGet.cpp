#include "LuaState.hpp"

LuaState::LuaGet::LuaGet(lua_State* L) :
	L(L)
{

}

LuaType LuaState::LuaGet::global(const std::string& name)
{
	int t = lua_getglobal(L, name.c_str());
	return convertLuaType(t);
}