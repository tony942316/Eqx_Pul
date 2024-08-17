import Equinox;
import Eqx.GlfwMod;

import GlfwMod.Tests;

int main()
{
    std::cout << "Start:\n\n"sv;

    glfwmod::tests::run();

    std::cout << "\nEnd:\n"sv;
    return 0;
}
