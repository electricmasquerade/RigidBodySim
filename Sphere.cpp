#include "Sphere.h"

Sphere::Sphere(float mass, Vec3 velocity, Vec3 position, sf::Color color)
    : RigidBody(mass, velocity, position, color){
    m_radius = 10*m_mass;
    m_shape = std::make_unique<sf::CircleShape>(m_radius);
    m_shape->setFillColor(m_color);
    m_shape->setPosition(m_position.x(), m_position.y());
    m_shape->setOrigin(m_radius, m_radius);
}

void Sphere::update(float dt) {
    m_position += m_velocity * dt;
    m_shape->setPosition(m_position.x(), m_position.y());
}

void Sphere::checkWallCollisions(int width, int height) {
    if (m_position.x() < m_radius || m_position.x() + m_radius > width){
        m_velocity.setX(-m_velocity.x());
        //Set position directly in contact with wall
        if (m_position.x() < m_radius){
            m_position.setX(m_radius);
        } else {
            m_position.setX(width - m_radius);
        }
    }
    if (m_position.y() < m_radius || m_position.y() + m_radius > height){
        m_velocity.setY(-m_velocity.y());
        //Set position directly in contact with wall
        if (m_position.y() < m_radius){
            m_position.setY(m_radius);
        } else {
            m_position.setY(height - m_radius);
        }
    }

}

void Sphere::checkCollision(const std::shared_ptr<RigidBody>& other) {
    auto other_sphere = std::dynamic_pointer_cast<Sphere>(other);

    if (other_sphere) {
        Vec3 other_position = other_sphere->getPosition();
        Vec3 other_velocity = other_sphere->getVelocity();

        float distance = (m_position - other_position).length();
        float collision_dist = m_radius + other_sphere->getRadius();

        Vec3 normal = unitNormal(m_position, other_position);

        float m1 = m_mass;
        float m2 = other_sphere->getMass();

        Vec3 v1 = m_velocity;
        Vec3 v2 = other_velocity;

        if (distance <= collision_dist) {
            //debugging print statements
//            std::cout << "Collision detected!\n";
//            std::cout << "Old velocities: " << m_velocity << " " << other_velocity << "\n";
//            std::cout << "Normal: " << normal << "\n";

            //Calculate new velocities, equation is from https://en.wikipedia.org/wiki/Elastic_collision#Two-dimensional_collision_with_two_moving_objects
            Vec3 v1_prime = v1 - ((2 * m2) / (m1 + m2)) * (dot((v1 - v2),normal)) * normal;
            Vec3 v2_prime = v2 - ((2 * m1) / (m1 + m2)) * (dot((v2 - v1),-normal)) * -normal;

            //Set new velocities
            m_velocity = v1_prime;
            other_sphere->setVelocity(v2_prime);

            //std::cout << "New velocities: " << m_velocity << " " << other_sphere->getVelocity() << "\n";

            //Set positions so that spheres are no longer colliding

            //TODO: figure out how to do this without making it awful

            //This absolutely does not work at all
//            float overlap = 0.5f * (collision_dist - distance);
//            Vec3 displacement = overlap * normal;
//
//            m_position += displacement;
//            other_sphere->setPosition(other_position - displacement);




        }
    }
}

