#include "LuaState.hpp"

using namespace saturn;

LuaState::LuaStack::LuaStack(lua_State* L) :
	L(L)
{

}
