import <Eqx/std.hpp>;

import Eqx.Lib;

import Eqx.Pul.Tests;

int main()
{
    std::cout << "Start:\n\n"sv;

    tests::run();

    std::cout << "\nEnd:\n"sv;
    return 0;
}
