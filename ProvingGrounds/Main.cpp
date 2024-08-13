import Equinox;
import Eqx.GlfwMod;

int main()
{
    std::cout << "Start:\n\n";

    glfwm::Window::init();
    auto window = glfwm::Window{640, 480, "Test"};
    window.setMouseMoveCallback(glfwm::Mouse::moveCallback);
    window.setMouseButtonCallback(glfwm::Mouse::buttonCallback);
    window.run([&window]()
        {
            window.setName(glfwm::Mouse::getPosition().toString());
        });
    glfwm::Window::term();

    std::cout << "\nEnd: ";
    return 0;
}
