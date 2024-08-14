import Equinox;
import Eqx.GlfwMod;

int main()
{
    std::cout << "Start:\n\n";

    glfwm::Window::init();
    auto window = glfwm::Window{640, 480, "Test"};
    window.setMouseMoveCallback(glfwm::mouse::moveCallback);
    window.setMouseButtonCallback(glfwm::mouse::buttonCallback);
    window.setKeyboardButtonCallback(glfwm::keyboard::buttonCallback);
    window.run([&window]()
        {
            auto name = std::string{};
            name += glfwm::mouse::getPosition().toString();
            name += " : "sv;
            if (glfwm::keyboard::isPressed('A'))
            {
                name += " \'A\' Pressed!";
            }
            else
            {
                name += " \'A\' Released!";
            }
            window.setName(name);
        });
    glfwm::Window::term();

    std::cout << "\nEnd:\n";
    return 0;
}
