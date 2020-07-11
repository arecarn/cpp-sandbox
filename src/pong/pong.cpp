#include <SFML/Graphics.hpp>

namespace Config
{
// This should be made into a configHandler Class
constexpr float Paddle_Height{25.0F};
constexpr float Paddle_Width{100.0F};
constexpr float Window_Width{800};
constexpr float Window_Height{600};
} // namespace

int main()
{
    sf::RenderWindow window(sf::VideoMode(Config::Window_Width, Config::Window_Height), "Pong");

    sf::RectangleShape shape(sf::Vector2f(Config::Paddle_Height, Config::Paddle_Width));
    shape.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
