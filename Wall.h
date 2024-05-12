//Muhammad Bilal 22i-2395
//Ahad Ali 22i-2384
#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Wall
{
public:
    RectangleShape shape;

    Wall(float x, float y, float width, float height)
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::Blue); // Adjust the color as needed
    }
};