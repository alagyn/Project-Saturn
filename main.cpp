#include <iostream>
#include <string>
#include "LuaState.hpp"
#include "LuaExceptions.hpp"

using namespace std;

int nativeTest(LuaState* L)
{
	cout << "This is a native call" << endl;
	return 0;
}

int main()
{
	LuaState L;
	
	try
	{
		L.load.file("test/test1.lua");

	}
	catch(LuaException& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}