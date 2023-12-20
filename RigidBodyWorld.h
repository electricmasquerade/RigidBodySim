#ifndef RIGIDBODYSIM_RIGIDBODYWORLD_H
#define RIGIDBODYSIM_RIGIDBODYWORLD_H

#include <vector>
#include <memory>
#include "RigidBody.h"


class RigidBodyWorld{
public:
    std::vector<std::shared_ptr<RigidBody>> rigid_bodies;
    explicit RigidBodyWorld(int width, int height);
    explicit RigidBodyWorld(const std::shared_ptr<RigidBody>& rigid_body, int width, int height);

    [[nodiscard]] int getWidth() const { return m_width; }
    [[nodiscard]] int getHeight() const { return m_height; }

    void add(const std::shared_ptr<RigidBody>& rigid_body){
        //Add a new rigid body to the simulation
        rigid_bodies.push_back(rigid_body);
    }

    void clear(){ rigid_bodies.clear(); }

    void checkCollisions();

    void update(float dt);

    void draw(sf::RenderWindow& window);

private:
    int m_width;
    int m_height;


};


#endif //RIGIDBODYSIM_RIGIDBODYWORLD_H
