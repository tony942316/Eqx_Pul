import Equinox;
import Eqx.GlfwMod;

int main()
{
    std::cout << "Start:\n\n";

    glfwm::Window::init();
    auto window = glfwm::Window{640, 480, "Test"};
    window.setMouseMoveCallback(glfwm::mouse::moveCallback);
    window.setMouseButtonCallback(glfwm::mouse::buttonCallback);
    window.run([&window]()
        {
            window.setName(glfwm::mouse::getPosition().toString());
        });
    glfwm::Window::term();

    std::cout << "\nEnd:\n";
    return 0;
}
