#include "components.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Config
{
constexpr float Paddle_Height{25.0F};
constexpr float Paddle_Width{100.0F};
constexpr unsigned int Window_Width{800};
constexpr unsigned int Window_Height{600};
} // namespace

int main()
{
    sf::VideoMode video_mode{Config::Window_Width, Config::Window_Height};
    sf::RenderWindow window{video_mode, "Pong"};

    sf::Vector2f dimenstions{Config::Paddle_Height, Config::Paddle_Width};
    sf::RectangleShape shape(dimenstions);
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
