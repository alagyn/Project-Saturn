#include "LuaContext.hpp"

using namespace saturn;


void LuaContext::set_global(const std::string& name)
{
	lua_setglobal(L, name.c_str());
}


//Stack: -1 = val
void LuaContext::set_key(int tableIdx, const std::string& key)
{
	lua_setfield(L, tableIdx, key.c_str());
}

//Stack: -2 = key, -1 = val
//Pops both
void LuaContext::set_key(int tableIdx)
{
	lua_settable(L, tableIdx);
}

//Stack: -1 = val
void LuaContext::set_index(int tableIdx, LuaInt idx)
{
	lua_seti(L, tableIdx, idx);
}

//Stack: -1 = metatable
void LuaContext::set_metatable(int tableIdx)
{
	lua_setmetatable(L, tableIdx);
}

//Stack: -2 = key, -1 = val
void LuaContext::set_raw(int tableIdx)
{
	lua_rawset(L, tableIdx);
}

//Stack: -1 = val
void LuaContext::set_raw(int tableIdx, LuaInt idx)
{
	lua_rawseti(L, tableIdx, idx);
}

//Stack: -1 = val
void LuaContext::set_raw(int tableIdx, const void* p)
{
	lua_rawsetp(L, tableIdx, p);
}

//Stack: -1 = val
//Returns false if UD does not have idx == n
bool LuaContext::set_iUserVal(int udIdx, int n)
{
	return (bool)lua_setiuservalue(L, udIdx, n);
}
