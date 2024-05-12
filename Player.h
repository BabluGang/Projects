//Muhammad Bilal 22i-2395
//Ahad Ali 22i-2384
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>


using namespace sf;

class Player
{
public:
    RectangleShape shape;
    float speed = 5.0f;         //adjust the speed as needed
    int direction = 0;          //direction of movement for the player
    int lives = 3;              //number of lives for the player
    AutoBox& autoBox;           //reference to AutoBox
    int points = 0;             //number of points for the player

    Player(float x, float y, float width, float height, int initialDirection, AutoBox& ab)
        : autoBox(ab)
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::Green);       //adjust the color as needed
        direction = initialDirection;
    }


    void fire()
    {
        // Implement firing logic if needed
    }

    void move(std::string s, float windowWidth, float windowHeight)
    {
        float delta_x = 0, delta_y = 0;

        if (s == "l")
            delta_x = -1.0f;
        else if (s == "r")
            delta_x = 1.0f;
        else if (s == "u")
            delta_y = -1.0f;
        else if (s == "d")
            delta_y = 1.0f;

        float length = std::sqrt(delta_x * delta_x + delta_y * delta_y);            //normalize the direction vector
        if (length != 0) {
            delta_x /= length;
            delta_y /= length;
        }

        delta_x *= speed;       //scale the direction vector by the speed
        delta_y *= speed;

        shape.move(delta_x, delta_y);       //move the player

        if (shape.getPosition().x < 0)          //check if the player is within the window boundaries
            shape.setPosition(0, shape.getPosition().y);

        else if (shape.getPosition().x + shape.getSize().x > windowWidth)
            shape.setPosition(windowWidth - shape.getSize().x, shape.getPosition().y);

        if (shape.getPosition().y < 0)
            shape.setPosition(shape.getPosition().x, 0);

        else if (shape.getPosition().y + shape.getSize().y > windowHeight - 50)             //adjusted to leave space for lives display
            shape.setPosition(shape.getPosition().x, windowHeight - shape.getSize().y - 50);

        //border for the player
        RectangleShape border(Vector2f(shape.getSize().x, shape.getSize().y));
        border.setPosition(shape.getPosition());
        border.setFillColor(Color::Transparent);
        border.setOutlineColor(Color::White);
        border.setOutlineThickness(2.0f);

        if (shape.getGlobalBounds().intersects(autoBox.shape.getGlobalBounds()))
        {
            lives--;
            std::cout << "Lives: " << lives << std::endl;

            shape.setPosition(200.f, 300.f);        //reset player position after collision
        }
    }

    //set points 
void setPoints(int p)
{
		points = p;
	}

	//get points
	int getPoints()
    {
		return points;
	}
};