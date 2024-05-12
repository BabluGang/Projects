//Muhammad Bilal 22i-2395
//Ahad Ali 22i-2384
#include <SFML/Graphics.hpp>
using namespace std;

// Base Fruit class
class Fruit
{
public:
    Fruit(float x, float y, float size, int randomnum);
    ~Fruit();

    void draw(sf::RenderWindow& window);
    bool checkCollision(const sf::FloatRect& otherBounds) const;

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

    int getPoints() const;

    const sf::Shape& getShape() const { return *shape; }        //get the shape

private:
    int points;
     unique_ptr<sf::Shape> shape;
};

Fruit::Fruit(float x, float y, float size, int randomnum)
{
    points = 0;
    if (randomnum == 0)
    {
        shape =  make_unique<sf::CircleShape>(size / 2);
        shape->setFillColor(sf::Color::Green); //default color for the base class
        points = 1;
    }

    else if (randomnum == 1)
	{
		shape =  make_unique<sf::RectangleShape>(sf::Vector2f(size, size));
        shape->setFillColor(sf::Color::Red); //default color for the base class
    points = 2;
	}

	else if (randomnum == 2)
	{
		shape =  make_unique<sf::CircleShape>(size / 2, 3);
        shape->setFillColor(sf::Color::White); //default color for the base class
    points = 3;
	}

	else if (randomnum == 3)
	{
		shape =  make_unique<sf::CircleShape>(size / 2, 6);
        //make it orange
    shape->setFillColor(sf::Color(255, 165, 0)); //default color for the base class
    points = 4;
	}

	else
	{
		shape =  make_unique<sf::CircleShape>(size / 2);
    shape->setFillColor(sf::Color::Green); //default color for the base class
		points = 1;
	}
    setPosition(x, y);
}

Fruit::~Fruit()
{
    //no need to delete the shape manually, as smart pointers handle it
}

void Fruit::draw(sf::RenderWindow& window)
{
    window.draw(*shape);
}

bool Fruit::checkCollision(const sf::FloatRect& otherBounds) const
{
    return shape->getGlobalBounds().intersects(otherBounds);
}

void Fruit::setPosition(float x, float y)
{
    shape->setPosition(x, y);
}

sf::Vector2f Fruit::getPosition() const
{
    return shape->getPosition();
}

int Fruit::getPoints() const
{
    return points;
}

//derived classes for specific fruit shapes

class CircleFruit : public Fruit
{
public:
    using Fruit::Fruit;     //inherit constructors from the base class

};

class SquareFruit : public Fruit
{
public:
    using Fruit::Fruit;
};

class TriangleFruit : public Fruit
{
public:
    using Fruit::Fruit;
};

class HexagonFruit : public Fruit
{
public:
    using Fruit::Fruit;
};