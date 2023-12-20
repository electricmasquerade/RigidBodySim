#include "RigidBody.h"

RigidBody::RigidBody(float mass, Vec3 velocity, Position3 position, sf::Color color)
    : m_velocity{velocity}, m_position{position}, m_color{color} {
    if (mass <= 0) {
        throw std::invalid_argument("Mass must be greater than 0");
    }
    else {
        m_mass = mass;
    }
}


