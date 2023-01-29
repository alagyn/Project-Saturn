#include "Saturn.hpp"
#include <iostream>

using namespace std;

// All objects are defined under this namespace
using namespace saturn;

int main()
{
    // Create a new context
    LuaContext ctx = new LuaContext()
    // Load and initialize a script file
    ctx.load_file("script.lua");
    
    // Call a function in the script with two arguments (LuaInt, String), one return (String)
    
    // 1) Retrieve function from global table and push to stack
    ctx.get_global("myFunc");
    // 2) Push first argument
    ctx.push((LuaInt)25);
    // 3) Push second argument
    ctx.push("Oh look, a string");
    
    try
    {
        // 4) Call function, 2 args, 1 return
        ctx.call(2, 1);
    }
    catch(LuaCallError e)
    {
        // Catch any errors created by call
        cout << e.what() << endl;
        return 0;
    }
    
    // 5) Retrieve return, placed at the top of the stack (index -1 is the top)
    const char* out = ctx.to_str(-1);
    // 6) Pop return off of stack, returning stack to original state
    ctx.pop()
    
    cout << "Script Output: " << out << endl;
    
    // Close the context, releases the internal lua_State
    ctx.close()
    
    return 0;
}