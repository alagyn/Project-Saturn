#include <iostream>
#include <string>
#include "LuaState.hpp"
#include "LuaExceptions.hpp"

using namespace std;

int main()
{
	LuaState L;
	
	try
	{
		L.load.file("test/test1.lua");
		L.get.global("testFunc");
		L.call();
	}
	catch(LuaException& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}