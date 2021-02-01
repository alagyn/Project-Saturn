#include "LuaState.hpp"
#include "LuaExceptions.hpp"

LuaState::LuaTo::LuaTo(lua_State* L) :
	L(L)
{

}

bool LuaState::LuaTo::boolean(int idx)
{
	return lua_toboolean(L, idx);
}

LuaInt LuaState::LuaTo::integer(int idx, bool unsafe)
{
	if(unsafe)
	{
		return lua_tointeger(L, idx);
	}

	int valid;

	LuaInt out = lua_tointegerx(L, idx, &valid);

	if(valid)
	{
		return out;
	}
	
	LuaType act = convertLuaType(lua_type(L, idx));
	throw LuaInvalidType(LuaType::NUMBER, act);
}

LuaNum LuaState::LuaTo::number(int idx, bool unsafe)
{
	if(unsafe)
	{
		return lua_tonumber(L, idx);
	}

	int valid;

	LuaNum out = lua_tonumberx(L, idx, &valid);

	if(valid)
	{
		return out;
	}

	LuaType act = convertLuaType(lua_type(L, idx));
	throw LuaInvalidType(LuaType::NUMBER, act);
}

void* LuaState::LuaTo::pointer(int idx)
{
	return lua_touserdata(L, idx);
}