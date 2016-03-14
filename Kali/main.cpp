//
// Disclamer:
// ----------
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "kali.hpp"
#include <iostream>
using namespace std;

int main(int, char const**)
{
    double_t triSize = 100;
    double_t sin60 = sqrt(3)/2.f;
    
    // Load a texture to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "wildflowers.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Vector2u texSize = texture.getSize();
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(6*triSize, (6*sin60*triSize + (6*triSize/texSize.x)*texSize.y)), "Kaleidoscope");
    window.setVerticalSyncEnabled(true);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    sf::ConvexShape tri;
    tri.setPointCount(3);
    tri.setPoint(0,sf::Vector2f(texSize.x/2,texSize.y/2));
    tri.setPoint(1,sf::Vector2f(texSize.x/2 + 300,texSize.y/2));
    tri.setPoint(2,sf::Vector2f(texSize.x/2 + 150,texSize.y/2 + sin60*300));
    tri.setFillColor(sf::Color::Transparent);
    tri.setOutlineColor(sf::Color::Red);
    tri.setScale(6*triSize/texSize.x,6*triSize/texSize.x);
    tri.setPosition(0,6*sin60*triSize);
    
    snowflake s(triSize, tri);
    
    sf::RectangleShape canvas(sf::Vector2f(texSize.x, texSize.y));
    canvas.setTexture(&texture);
    canvas.setScale(6*triSize/texSize.x,6*triSize/texSize.x);
    canvas.setPosition(0,6*sin60*triSize);
    
    
    
    float speed = 25.f;
    sf::Clock clock;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        window.clear();
        
        float delta = clock.restart().asSeconds();
        
        tri = s.rollTexture(speed*delta);
        tri.setFillColor(sf::Color::Transparent);
        tri.setOutlineColor(sf::Color::Red);
        tri.setOutlineThickness(5);
        tri.setScale(6*triSize/texSize.x,6*triSize/texSize.x);
        tri.setPosition(0,6*sin60*triSize);
        
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++){
                s.setPosition(1.5*s.getSize()*j,
                              sqrt(3)*s.getSize()*i + (sqrt(3)/2.f)*s.getSize()*(j%2));
                window.draw(s,&texture);
            }
        }
        
        //window.draw(s,&texture);
        window.draw(canvas);
        window.draw(tri);
        window.display();
        
        
    }
    
    return EXIT_SUCCESS;
}
