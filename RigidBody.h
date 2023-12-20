#ifndef RIGIDBODYSIM_RIGIDBODY_H
#define RIGIDBODYSIM_RIGIDBODY_H

#include <SFML/Graphics.hpp>
#include "Vec3.h"

class RigidBody {
public:
    explicit RigidBody(float mass, Vec3 velocity, Position3 position, sf::Color color);

    [[nodiscard]] float getMass() const { return m_mass; }
    [[nodiscard]] Vec3 getVelocity() const { return m_velocity; }

    void setVelocity(const Vec3& velocity) { m_velocity = velocity; }

    [[nodiscard]] Vec3 getPosition() const { return m_position; }
    void setPosition(const Position3& position) { m_position = position; }

    [[nodiscard]] sf::Color getColor() const { return m_color; }

    virtual void update(float dt) = 0;
    virtual void checkWallCollisions(int width, int height) = 0;
    virtual void checkCollision(const std::shared_ptr<RigidBody>& other) = 0;


    [[nodiscard]] virtual const sf::Shape& getShape() const { return *m_shape; }

protected:
    float m_mass;
    Vec3 m_velocity;

    Position3 m_position;

    sf::Color m_color; //Color can be a predefined SFML color or a RGBa value.
    std::unique_ptr<sf::Shape> m_shape;

};


#endif //RIGIDBODYSIM_RIGIDBODY_H
