#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace saturn;

bool LuaContext::to_boolean(int idx)
{
	return lua_toboolean(L, idx);
}

LuaNum LuaContext::to_number(int idx, bool unsafe)
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

void* LuaContext::to_pointer(int idx)
{
	return lua_touserdata(L, idx);
}

const char* LuaContext::to_string(int idx, size_t* lenOutput)
{
	return lua_tolstring(L, idx, lenOutput);
}

//Undefined for non vanilla C functions
LuaCFunc LuaContext::to_luaFunc(int idx)
{
	return lua_tocfunction(L, idx);
}



LuaInt LuaContext::to_integer(int idx, bool unsafe)
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
