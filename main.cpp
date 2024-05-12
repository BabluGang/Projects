//Muhammad Bilal 22i-2395
//Ahad Ali 22i-2384
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow menuWindow(sf::VideoMode(700, 700), "Game Menu");

    Menu menu;
    int menuResult = menu.displayMenu(menuWindow);


    sf::Music music;

    if (!music.openFromFile("C:\\Users\\Lenovo\\Desktop\\M.Bilal_22i-2395_C, AhadAli_22i-2384_C\\22i-2384_22i_2395_project\\pacman.ogg"))
	    return -1;          //error
    music.play();


    if (menuResult == 0)
    {
        Game game;          //start the game
        game.start_game();
    }

    if (menuResult == 1)
	{
        music.pause();      //mute the music
        Game game;
        game.start_game();	
	}

    if (menuResult == 2)
	{
		return 0;           //exit the game
	}
    return 0;
}