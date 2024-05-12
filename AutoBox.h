//Muhammad Bilal 22i-2395
//Ahad Ali 22i-2384
#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class AutoBox
{
public:
    RectangleShape shape;
    int direction; //direction of movement for the box

    AutoBox() {}
    AutoBox(float x, float y, float width, float height, int initialDirection)
        : direction(initialDirection)
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::Red); //adjust the color as needed
    }

    void move(float speed, float offsetY)
    {
        shape.move(speed * direction, offsetY);
    }
};