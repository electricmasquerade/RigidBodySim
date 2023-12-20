#include "RigidBodyWorld.h"

RigidBodyWorld::RigidBodyWorld(int width, int height): m_width{width}, m_height{height}{}

RigidBodyWorld::RigidBodyWorld(const std::shared_ptr<RigidBody>& rigid_body, int width, int height)
    : m_width{width}, m_height{height} {
    add(rigid_body);
}


//check for collisions between rigid bodies
void RigidBodyWorld::checkCollisions (){
    //Checks for collisions with walls by calling the checkWallCollisions method of each rigid body
    for (auto& rigid_body : rigid_bodies){
        rigid_body->checkWallCollisions(m_width, m_height);
    }

    for (size_t i = 0; i < rigid_bodies.size(); ++i) {
        for (size_t j = i + 1; j < rigid_bodies.size(); ++j) {
            auto &body1 = rigid_bodies[i];
            auto &body2 = rigid_bodies[j];
            if (body1 && body2) {
                body1->checkCollision(body2);
            }
        }
    }
}

//Update position and velocity of all rigid bodies
void RigidBodyWorld::update(float dt){
    for (auto& rigid_body : rigid_bodies){
        rigid_body->update(dt);
        //TODO: update velocity? Maybe? Consider adding friction, etc
    }
}

//Draw all rigid bodies
void RigidBodyWorld::draw(sf::RenderWindow& window){
    for (auto& rigid_body : rigid_bodies){
        if (rigid_body){
            window.draw(rigid_body->getShape());
        } else {
            std::cerr << "Null or invalid shape encountered.\n";
        }
    }
}