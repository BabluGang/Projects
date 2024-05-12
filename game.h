//Muhammad Bilal 22i-2395
//Ahad Ali 22i-2384
#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include "AutoBox.h"
#include "Player.h"
#include "Wall.h"
#include "Fruit.h"
using namespace sf;
using namespace std;

const char title[] = "OOP-Project, Spring-2023";
enum FruitShape { Circle, Square, Triangle, Hexagon };


class Game
{
public:
    Sprite background;  //game background sprite
    Texture bg_texture;
    Player* p;          //player
    AutoBox autoBox;    //auto-moving box
    
    int level;

    
    int direction = 1;          //variable to store the direction of movement
    bool gameRunning = true;    //flag to track the game state

    bool paused = false;        //flag to track the pause state
    
    void togglePause()      //function to handle pausing and resuming the game
    {
        paused = !paused;
    }

     vector<Wall> walls;
     vector<Fruit*> fruits;
    Game(int initialLevel = 1) : level(initialLevel)
    {
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);
        p = new Player(200.f, 300.f, 30.f, 30.f, 1, autoBox);           //initialize the player
        autoBox = AutoBox(200.f, 300.f, 30.f, 30.f, 1);                 //initialize the auto-moving box

        walls.push_back(Wall(40.f, 100.f, 290.f, 10.f));
        walls.push_back(Wall(40.f, 100.f, 10.f, 250.f));
        walls.push_back(Wall(100.f, 160.f, 230.f, 10.f));
        walls.push_back(Wall(100.f, 160.f, 10.f, 190.f));
        walls.push_back(Wall(160.f, 250.f, 170.f, 10.f));
        walls.push_back(Wall(160.f, 250.f, 10.f, 100.f));
        walls.push_back(Wall(220.f, 300.f, 110.f, 10.f));
		walls.push_back(Wall(220.f, 300.f, 10.f, 50.f));

        walls.push_back(Wall(220.f, 500.f, 110.f, 10.f));
        walls.push_back(Wall(220.f, 450.f, 10.f, 50.f));
        walls.push_back(Wall(160.f, 550.f, 170.f, 10.f));
        walls.push_back(Wall(160.f, 450.f, 10.f, 100.f));
        walls.push_back(Wall(100.f, 600.f, 230.f, 10.f));
        walls.push_back(Wall(100.f, 450.f, 10.f, 150.f));
        walls.push_back(Wall(40.f, 650.f, 290.f, 10.f));
        walls.push_back(Wall(40.f, 450.f, 10.f, 200.f));

        walls.push_back(Wall(450.f, 100.f, 290.f, 10.f));       //repeat the same pattern for the second half of the map inverted
		walls.push_back(Wall(730.f, 100.f, 10.f, 250.f));
		walls.push_back(Wall(450.f, 160.f, 230.f, 10.f));
		walls.push_back(Wall(680.f, 160.f, 10.f, 190.f));
		walls.push_back(Wall(450.f, 250.f, 170.f, 10.f));
		walls.push_back(Wall(620.f, 250.f, 10.f, 100.f));
		walls.push_back(Wall(450.f, 300.f, 110.f, 10.f));
        walls.push_back(Wall(560.f, 300.f, 10.f, 50.f));
        walls.push_back(Wall(450.f, 500.f, 110.f, 10.f));
        walls.push_back(Wall(560.f, 450.f, 10.f, 60.f));
		walls.push_back(Wall(450.f, 550.f, 170.f, 10.f));
		walls.push_back(Wall(620.f, 450.f, 10.f, 110.f));
		walls.push_back(Wall(450.f, 600.f, 230.f, 10.f));
		walls.push_back(Wall(680.f, 450.f, 10.f, 160.f));
		walls.push_back(Wall(450.f, 650.f, 290.f, 10.f));
		walls.push_back(Wall(730.f, 450.f, 10.f, 200.f));

        
        generateFruits();       //generate fruits

    }

    void generateFruits()
    {
        srand(time(NULL));               //seed the random number generator
        for (int i = 0; i < 10; ++i)
        {
            float x = rand() % 700 + 40;        //random x position within the playable area
            float y = rand() % 700 + 40;        //random y position within the playable area
            float size = 20.0f;

            FruitShape shapeType;

            switch (level)          //generate fruits based on the current level
            {
            case 1:
                shapeType = FruitShape::Circle;
                break;
            case 2:
                shapeType = (rand() % 2 == 0) ? FruitShape::Circle : FruitShape::Square;
                break;
            case 3:
                shapeType = static_cast<FruitShape>(rand() % 3);
                break;
            default:
                shapeType = static_cast<FruitShape>(rand() % 4);
                break;
            }

            Fruit* newFruit = nullptr;

            switch (shapeType)
            {
            case FruitShape::Circle:
                newFruit = new CircleFruit(x, y, size, 0);
                break;
            case FruitShape::Square:
                newFruit = new SquareFruit(x, y, size, 1);
                break;
            case FruitShape::Triangle:
                newFruit = new TriangleFruit(x, y, size, 2);
                break;
            case FruitShape::Hexagon:
                newFruit = new HexagonFruit(x, y, size, 3);
                break;
            }

            if (newFruit != nullptr)
            {
                fruits.push_back(newFruit);
            }
        }
    }

    ~Game()
    {
        for (Fruit* fruit : fruits)
        {
            delete fruit;
        }
        delete p;           //clean up allocated memory for player
    }

    void checkFruitCollision()
    {
        for (auto it = fruits.begin(); it != fruits.end();)
        {
            if (p->shape.getGlobalBounds().intersects((*it)->getShape().getGlobalBounds()))
            {
                p->setPoints(p->getPoints() + (*it)->getPoints());      //collision detected with a fruit
                
                                                //remove the eaten fruit from the vector
                delete* it;                     //delete the memory of the eaten fruit
                it = fruits.erase(it);          //remove the fruit from the vector              
            }

            else
            {
                ++it;
            }
        }
    }

    void stop_game()
    {

        gameRunning = false;
        bool gameover = true;
        RenderWindow window(VideoMode(780, 780), title);

        while (gameover && window.isOpen())
		{
			
			window.clear(Color::Black);
			Font font;
			font.loadFromFile("C:\\Users\\Lenovo\\Desktop\\M.Bilal_22i-2395_C, AhadAli_22i-2384_C\\22i-2384_22i_2395_project\\KnightWarrior.otf");

			Text gameOverText("Game Over", font, 50);
			gameOverText.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 25);
			gameOverText.setFillColor(Color::Red);
			window.draw(gameOverText);

			window.display();
		}

    }

    bool check_autoBox_wall_collision()
    {
        for (Wall& wall : walls)
        {
            if (autoBox.shape.getGlobalBounds().intersects(wall.shape.getGlobalBounds()))
            {
                float deltaX = 0.0f;          //collision detected, adjust autobox direction based on current movement
                float deltaY = 0.0f;

                float autoBoxVelocityX = autoBox.direction;         //determine the direction of the autobox movement
                float autoBoxVelocityY = autoBox.direction;

                if ( abs(autoBoxVelocityX) >  abs(autoBoxVelocityY))        //check if autobox is moving horizontally
                {
                    int random = rand() % 2;        //randomly choose to move right or down

                    if (autoBoxVelocityX < 0)       //autoBox moving left
                    {
                        if (random == 0)
                            deltaX = 10.0f;      //move right
                        else
                            deltaY = 10.0f;      //move down
                    }

                    else        //autoBox moving right
                    {
                        int r2 = rand() % 2;        //randomly choose to move left or down
                        if (r2 == 0)
                            deltaX = -10.0f;        //move left
                        else
                            deltaY = 10.0f;         //move down
                    }
                }

                else        //autobox is moving vertically
                {
                    int random = rand() % 2;
                    if (random ==0 )
                    {
                        deltaY = 10.0f;         //move down
                    }

                    else            //autoBox moving down
                    {
                        int r2 = rand() % 2;        //randomly choose to move left or right
                        if (r2 == 0)
                            deltaY = -10.0f;        //move up
                        else
                            deltaX = (autoBoxVelocityX < 0) ? 10.0f : -10.0f;       //move right if previously moving left, move left if previously moving right
                    }
                }

                autoBox.shape.move(deltaX, deltaY);         //move the AutoBox to the new position

                if (check_wall_collision())     //check collision with walls for the adjusted autobox position
                {
                    autoBox.shape.move(-deltaX, -deltaY);       //revert the autobox position as it collides with walls
                }

                return true;            //collision detected
            }
        }
        return false;           //no collision
    }

    bool check_wall_collision()             //function to check collision with walls
    {
        for (const Wall& wall : walls)
        {
            if (p->shape.getGlobalBounds().intersects(wall.shape.getGlobalBounds()))
            {
                float overlapX = 0, overlapY = 0;           //collision detected, prevent player from passing through walls

                if (p->shape.getPosition().x < wall.shape.getPosition().x)           //calculate the overlap on the X-axis
                {
                    overlapX = p->shape.getPosition().x + p->shape.getSize().x - wall.shape.getPosition().x;
                }

                else
                {
                    overlapX = wall.shape.getPosition().x + wall.shape.getSize().x - p->shape.getPosition().x;
                }

                if (p->shape.getPosition().y < wall.shape.getPosition().y)          //calculate the overlap on the Y-axis
                {
                    overlapY = p->shape.getPosition().y + p->shape.getSize().y - wall.shape.getPosition().y;
                }

                else
                {
                    overlapY = wall.shape.getPosition().y + wall.shape.getSize().y - p->shape.getPosition().y;
                }

                bool wallOnLeft = wall.shape.getPosition().x < p->shape.getPosition().x;            //determine the relative positions of the player and the wall
                bool wallAbove = wall.shape.getPosition().y < p->shape.getPosition().y;

                if (overlapX < overlapY)        //move the player away from the wall based on the relative positions
                {
                    if (wallOnLeft)
                    {
                        p->shape.move(overlapX, 0);
                    }

                    else
                    {
                        p->shape.move(-overlapX, 0);
                    }
                }

                else
                {
                    if (wallAbove)
                    {
                        p->shape.move(0, overlapY);
                    }
                    else
                    {
                        p->shape.move(0, -overlapY);
                    }
                }
                return true;    //collision detected
            }
        }
        return false;           //no collision
    }

    void start_game()
	{
		RenderWindow window(VideoMode(780, 780), title);
		window.setFramerateLimit(60);

		Clock clock;        //game loop
		float timer = 0.0f;

    while (window.isOpen() && gameRunning)
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        if (!paused)
        {
            checkFruitCollision();
            timer += time;

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
                else if (e.type == Event::KeyPressed && e.key.code == Keyboard::P)
                    togglePause();          //toggle pause state when 'p' is pressed
            }

            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
                p->move("l", window.getSize().x, window.getSize().y);
            if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
                p->move("r", window.getSize().x, window.getSize().y);
            if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
                p->move("u", window.getSize().x, window.getSize().y);
            if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
                p->move("d", window.getSize().x, window.getSize().y);

            window.clear(Color::Black);

            window.draw(background);

            for (const Wall& wall : walls)          //draw walls
            {
                window.draw(wall.shape);
            }

            for (Fruit* fruit : fruits)
            {
                fruit->draw(window);


            }

            float speed = 2.0f;         //move and draw the auto-moving box
            autoBox.move(speed, 0.0f);

            if (autoBox.shape.getPosition().x + autoBox.shape.getSize().x > window.getSize().x ||       //check if the box reached the right or left boundary
                autoBox.shape.getPosition().x < 0)
            {
                //if the left side of the box is outside the window, move it to the right or up or down
                //if the right side of the box is outside the window, move it to the left or up or down
                int random = rand() % 3;        //randomly choose to move right or up or down

                if (random == 0)
                    autoBox.direction = 1.0f;           //move right
                else if (random == 1)
                    autoBox.direction = -1.0f;          //move left
                else
                {
                    autoBox.direction = -autoBox.direction;         //rotate the box direction by 90 degrees
                }
            }

            if (check_autoBox_wall_collision())         //check collision with walls for the autobox
            {

            }
            window.draw(autoBox.shape);

            window.draw(p->shape);

            Font font;              //draw lives at the top right
            font.loadFromFile("C:\\Users\\Lenovo\\Desktop\\M.Bilal_22i-2395_C, AhadAli_22i-2384_C\\22i-2384_22i_2395_project\\KnightWarrior.otf");
            Text livesText("Lives: " +  to_string(p->lives), font, 20);
            livesText.setPosition(20, 20);
            livesText.setFillColor(Color::White);
            window.draw(livesText);

            Text pointsText("Points: " +  to_string(p->getPoints()), font, 20);     //draw points at the top left
			pointsText.setPosition(window.getSize().x - 150, 20);
            pointsText.setFillColor(Color::White);
			window.draw(pointsText);

            if (p->lives <= 0)          //display "Game Over" if lives are zero
            {
                window.clear(Color::Black);
                window.close();
                stop_game();
            }

            if (check_wall_collision())         //check collision with walls for the player
            {
                //no need to reset player position, it has been adjusted in case of collision
            }

            if (fruits.empty())         //check if the player has eaten all the fruits
            {
                ++level;            //increase the level and generate new fruits
                generateFruits();
            }
        }

        else
        {
            Font font;          //jf paused, display a message

            font.loadFromFile("C:\\Users\\Lenovo\\Desktop\\M.Bilal_22i-2395_C, AhadAli_22i-2384_C\\22i-2384_22i_2395_project\\KnightWarrior.otf");
            Text pauseText("Game Paused (Press 'p' to resume)", font, 30);
            pauseText.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2 - 25);
            pauseText.setFillColor(Color::White);
            window.draw(pauseText);

            Event e;            //unpause if 'p' key is pressed

            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
                else if (e.type == Event::KeyPressed && e.key.code == Keyboard::P)
                    togglePause();          //toggle pause state when 'p' is pressed
            }
        }
            window.display();
        }
        window.close();             //close the window explicitly
    }
};