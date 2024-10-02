#include "State.h"
#include <cmath>

Distance calculDistance(Position a, Position b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
// Verify collision between a robot and a particle
bool isColliding(const RobotInfo& robot, const ParticleInfo& particle) {
    Distance limit = robot.radius + particle.radius + std::numeric_limits<float>::epsilon();
    Distance distance = calculDistance(robot.position, particle.position);
    return distance <= limit;
}
//Verify robots between each other
bool isRobotColliding(const RobotInfo& robot1, const RobotInfo& robot2) {
    Distance limit = robot1.radius + robot2.radius + std::numeric_limits<float>::epsilon();
    Distance distance = calculDistance(robot1.position, robot2.position);
    return distance <= limit;
}

//If robot meets particle.
void handleDecontamination(State& state) {
    for (auto& robot : state.robots) {
        for (auto it = state.particles.begin(); it != state.particles.end(); ) {
            if (isColliding(robot, *it) && isWithinCaptureAngle(robot, *it)) {
                double particleArea = M_PI * std::pow(it->radius, 2);
                robot.score += particleArea;
                it = state.particles.erase(it);
            } else {
                ++it;
            }
        }
    }
}

//If robot collides with another robot
void isRobotsBlocked(State& state){
    // Handle collision
    for (auto it1 = state.robots.begin(); it1 != state.robots.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != state.robots.end(); ++it2) {
            if (isRobotColliding(*it1, *it2)) {
                it1->leftSpeed = 0;
                it1->rightSpeed = 0;
                it2->leftSpeed = 0;
                it2->rightSpeed = 0;
            }
        }
    }
}
