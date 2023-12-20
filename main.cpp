#include <iostream>
#include "SFML/Graphics.hpp"
#include "Sphere.h"
#include "RigidBodyWorld.h"

int main() {
    float width = 750;
    float height = 750;


    RigidBodyWorld world{static_cast<int>(width),static_cast<int>(height)};

    //set up spheres in a billiard configuration, using proper colors
//    float vertical_offset = 40;
//    float horizontal_offset = 25;
//    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2,height/2,0}, sf::Color::Yellow));
//    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2 + horizontal_offset,height/2 - vertical_offset,0}, sf::Color::Blue));
//    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2 - horizontal_offset,height/2 - vertical_offset,0}, sf::Color::Red));
//    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2 + 2*horizontal_offset,height/2 - 2*vertical_offset,0}, sf::Color::Magenta));
//    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2,height/2 - 2*vertical_offset,0}, sf::Color::Green));
//    world.add(std::make_shared<Sphere>(2, Vec3{0,0,0}, Position3{width/2 - 2*horizontal_offset,height/2 - 2*vertical_offset,0}, sf::Color::Cyan));
//
//    //cue ball
//    world.add(std::make_shared<Sphere>(10, Vec3{200,-750,0}, Position3{width/2,3.5f*height/4, 0}, sf::Color::White));

//randomly generate spheres with random velocities and colors
    for (int i = 0; i < 10; ++i) {
        float mass = 2;
        float x = static_cast<float>(rand() % static_cast<int>(width));
        float y = static_cast<float>(rand() % static_cast<int>(height));
        float z = 0;
        float vx = static_cast<float>(rand() % 750 - 500);
        float vy = static_cast<float>(rand() % 750 - 500);
        float vz = 0;
        uint8_t r = static_cast<int>(rand() % 255);
        uint8_t g = static_cast<int>(rand() % 255);
        uint8_t b = static_cast<int>(rand() % 255);
        uint8_t a = 255;
        sf::Color color{r,g,b,a};
        world.add(std::make_shared<Sphere>(mass, Vec3{vx,vy,vz}, Position3{x,y,z}, color));
    }



    sf::RenderWindow window(sf::VideoMode(world.getWidth(), world.getHeight()), "Rigid Body Simulation");
    //Simulation becomes far less accurate if Vsync is on, since it uses actual time between frames instead of a constant dt
    //window.setVerticalSyncEnabled(true);



    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        std::cout << dt << std::endl;
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
