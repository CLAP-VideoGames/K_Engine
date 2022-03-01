// C++ program to illustrate the use of
// LuaCpp library
#include <LuaCpp.hpp>
#include <iostream>
using namespace LuaCpp::Registry;
using namespace std;
  
// Driver Code
int main(int argc, char** argv)
{
  
    cout << "Hi from C++, this is a demo"
         << " how LuaCpp can be used\n";
  
    LuaContext lua;
  
    // The simples way is to use
    // CompileStringAndRun method
    try {
  
        lua.CompileStringAndRun(
            "print('The fastest way to "
            "start using lua in "
            "a project')");
    }
  
    catch (std::runtime_error& e) {
        std::cout << e.what()
                  << '\n';
    }
}