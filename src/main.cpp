#include "Boundary.h"
#include "Ray.h"
#include "Light.h"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(nullptr));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(600, 600), "Raycaster", sf::Style::Default, settings);

    ///********************* Setup 
    sf::CircleShape lightCentre(6.f);
    lightCentre.setFillColor(sf::Color(255, 255, 255, 180));

    Light light({ 200, 200 }, 0.4);
    

    Boundary* wallz = new Boundary[8];
    for (int i = 0; i < 4; i++)
    {
        Vec a(rand() % 600, rand() % 600);
        Vec b(rand() % 600, rand() % 600);
        wallz[i] = Boundary(a, b);
        wallz[4] = { { 0, 0 }, { 0, 600 } };
        wallz[5] = { { 0, 0 }, { 600, 0 } };
        wallz[6] = { { 600, 600 }, { 0, 600 } };
        wallz[7] = { { 600, 600 }, { 600, 0 } };
    }
    //********************** Setup
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        Vec a(rand() % 600, rand() % 600);
                        Vec b(rand() % 600, rand() % 600);
                        wallz[i] = Boundary(a, b);
                    }
                    light.setPos({ (float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y });
                    light.cast(wallz, 8);
                }
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                light.setPos({ (float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y });
                light.cast(wallz, 8);
            }
        }

        // Draw
        window.clear();
        for (int i = 0; i < 4; i++)
            wallz[i].draw(&window);


        light.draw(&window, &lightCentre);
        //window.draw(hit);
        window.display();
    }

    light.~Light();
    delete[] wallz;
    return 0;
}
