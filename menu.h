//Muhammad Bilal 22i-2395
//Ahad Ali 22i-2384
#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu();
    ~Menu();

    int displayMenu(sf::RenderWindow& window);
};

Menu::Menu()
{
    //constructor (if needed)
}

Menu::~Menu()
{
    //destructor (if needed)
}

int Menu::displayMenu(sf::RenderWindow& window)
{
    sf::Font font;

    font.loadFromFile("C:\\Users\\Lenovo\\Desktop\\M.Bilal_22i-2395_C, AhadAli_22i-2384_C\\22i-2384_22i_2395_project\\KnightWarrior.otf");

    sf::Text titleText("DODGE 'EM ALL", font, 30);
    titleText.setPosition(window.getSize().x / 2 - 180, window.getSize().y / 2 - 50);
    titleText.setFillColor(sf::Color::White);

    sf::Text startText("1. Start Game", font, 20);
    startText.setPosition(window.getSize().x / 2 - 60, window.getSize().y / 2 + 50);
    startText.setFillColor(sf::Color::White);

    sf::Text muteText("2. Mute Music", font, 20);           //mute music
    muteText.setPosition(window.getSize().x / 2 - 60, window.getSize().y / 2 + 100);
    muteText.setFillColor(sf::Color::White);

    sf::Text exitText("3. Exit Game", font, 20);        //exit game
    exitText.setPosition(window.getSize().x / 2 - 60, window.getSize().y / 2 + 150);
    exitText.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return -1;                  //return -1 to indicate the program should exit
            }

            else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Num1)
            {
                return 0;                   //return 0 to indicate the game should start
            }

            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
			{
				return 1;                   //return 1 to indicate the music should be muted
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
			{
				return 2;                   //return 2 to indicate the game should exit
			}
        }

        window.clear(sf::Color::Black);

        window.draw(titleText);
        window.draw(startText);
        window.draw(muteText);
        window.draw(exitText);

        window.display();
    }
    return -1;                 //default return (should not reach here)
}