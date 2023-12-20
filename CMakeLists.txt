cmake_minimum_required(VERSION 3.27)
project(RigidBodySim)

set(CMAKE_CXX_STANDARD 23)


add_executable(RigidBodySim main.cpp
        RigidBody.cpp
        RigidBody.h
        Sphere.cpp
        Sphere.h
        RigidBodyWorld.cpp
        RigidBodyWorld.h
        Vec3.cpp
        Vec3.h)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(RigidBodySim sfml-system sfml-window sfml-graphics)
