#ifndef RIGIDBODYSIM_SPHERE_H
#define RIGIDBODYSIM_SPHERE_H

#include <utility>
#include <memory>
#include "RigidBody.h"
#include "SFML/Graphics.hpp"

class Sphere : public RigidBody{
public:
    explicit Sphere(float mass, Vec3 velocity, Vec3 position, sf::Color color);

    [[nodiscard]] double getRadius() const { return m_radius; }

    void update(float dt) override;

    void checkWallCollisions(int width, int height) override;
    void checkCollision(const std::shared_ptr<RigidBody>& other) override;

    [[nodiscard]] const sf::Shape& getShape() const override {
        return *m_shape;
    }






private:
    float m_radius;
    std::unique_ptr<sf::CircleShape> m_shape;



};


#endif //RIGIDBODYSIM_SPHERE_H
