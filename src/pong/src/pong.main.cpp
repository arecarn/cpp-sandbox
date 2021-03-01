#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <components.hpp>

#include <bitset>
#include <vector>

namespace Config
{
constexpr float Paddle_Height{25.0F};
constexpr float Paddle_Width{100.0F};
constexpr unsigned int Window_Width{800};
constexpr unsigned int Window_Height{600};
} // namespace

class Paddle
{
public:
    Paddle()
        : m_dimenstions{Config::Paddle_Height, Config::Paddle_Width}
        , m_shape{m_dimenstions}
    {
        m_shape.setFillColor(sf::Color::White);
    }

    void update()
    {
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(m_shape);
    }

private:
    sf::Vector2<float> m_position;
    sf::Vector2f m_dimenstions;
    sf::RectangleShape m_shape;
};

int main()
{

    sf::VideoMode video_mode{Config::Window_Width, Config::Window_Height};
    sf::RenderWindow window{video_mode, "Pong"};
    std::vector<int> v;

    Paddle paddle{};

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
        paddle.draw(window);
        window.display();
    }

    return 0;
}
