#pragma once
#include "Saturn.hpp"

using namespace saturn;

int nativeFunc(LuaState& L)
{
	LuaInt a = L.to.integer(1);
	LuaInt b = L.to.integer(2);

	L.push.integer(a + b);
	return 1;
}

int main()
{
	LuaState L;

	L.load.file("test.lua");
	L.registerFunc("nativeFunc", nativeFunc);

	L.get.global("scriptFunc");
	L.call();

	return 0;
}

