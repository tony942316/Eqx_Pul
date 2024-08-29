import <Eqx/std.hpp>;

import Eqx.Lib;

import GlfwMod.Tests;

int main()
{
    std::cout << "Start:\n\n"sv;

    glfwmod::tests::run();

    std::cout << "\nEnd:\n"sv;
    return 0;
}
