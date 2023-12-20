#include <iostream>
#include "SFML/Graphics.hpp"
#include "Sphere.h"
#include "RigidBodyWorld.h"

int main() {
    float width = 750;
    float height = 750;

    float vertical_offset = 40;
    float horizontal_offset = 25;
    RigidBodyWorld world{static_cast<int>(width),static_cast<int>(height)};

    //set up spheres in a billiard configuration, using proper colors
    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2,height/2,0}, sf::Color::Yellow));
    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2 + horizontal_offset,height/2 - vertical_offset,0}, sf::Color::Blue));
    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2 - horizontal_offset,height/2 - vertical_offset,0}, sf::Color::Red));
    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2 + 2*horizontal_offset,height/2 - 2*vertical_offset,0}, sf::Color::Magenta));
    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2,height/2 - 2*vertical_offset,0}, sf::Color::Green));
    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2 - 2*horizontal_offset,height/2 - 2*vertical_offset,0}, sf::Color::Cyan));


    //cue ball
    world.add(std::make_shared<Sphere>(2, Vec3{500,-750,0}, Position3{width/2,3*height/4, 0}, sf::Color::White));



    sf::RenderWindow window(sf::VideoMode(world.getWidth(), world.getHeight()), "Rigid Body Simulation");
    //window.setVerticalSyncEnabled(true);


    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        //std::cout << dt << std::endl;
        sf::Event event{};

        world.checkCollisions();
        world.update(dt);


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        world.draw(window);
        window.display();
    }
}
