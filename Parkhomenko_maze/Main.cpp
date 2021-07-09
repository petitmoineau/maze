#include "Game.h"
#include <Windows.h>
#include "MainMenu.h"

State coreState;
bool quitGame = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1040), "Bonjour!");//border 70x80

    coreState.setWindow(&window);
    coreState.setState(new MainMenu());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (quitGame)
        {
            window.close();
        }

        window.clear(Color::White);
        coreState.Update();
        window.display();

    }

    return 0;
}