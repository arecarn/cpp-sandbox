#include <SFML/Graphics.hpp>

namespace config
{
// This should be made into a configHandler Class
constexpr float kPaddleHeight{25.f};
constexpr float kPaddleWidth{100.f};
} // namespace config

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

    sf::RectangleShape shape(sf::Vector2f(config::kPaddleHeight, config::kPaddleWidth));
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
