#pragma once
#include "Saturn.hpp"

using namespace saturn;

int nativeFunc(LuaState& L)
{
	LuaInt a = L.to<LuaInt>(1);
	LuaInt b = L.to<LuaInt>(2);

	L.push<LuaInt>(a + b);
	
    return 1;
}

int main()
{
	LuaState L;

	L.load_file("test.lua");
	L.register_func("nativeFunc", nativeFunc);

	L.get_global("scriptFunc");
	L.call();

	return 0;
}

