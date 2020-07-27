#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

namespace Components
{

struct Movement
{
    sf::Vector2<float> velocity;
    sf::Vector2<float> acceleration;
};

struct Transform
{
    sf::Vector2<float> position;
    sf::Vector2<float> scale;
};

struct Collision
{
    sf::RectangleShape rect;
};

struct Render
{
    sf::Color color;
    sf::RectangleShape rect;
};

struct Control
{
};
}

#endif
