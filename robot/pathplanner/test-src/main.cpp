#include "../TestMethods.h"

#include <iostream>

int main()
{
    std::cout << "Hello, World! One day I am going to test a big robot!" << std::endl;
    std::cout << "My name is Path Planner Tester!" << std::endl;
    TestAll tests;
    tests.TestPathPlanner();
    return 0;
}