#include "robotwidget.h"
#include "math.h"


Distance calculDistance(Position a, Position b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/*
 * True = there is a collision
 * False = there isn't a collision
*/
bool isColision(const RobotInfo& robot){
    //robots
    //particles

    for(RobotInfo& robotOther : state.robots) {
        if (robot.id != robotOther.id){
            Distance limit = robot.radius + robotOther.radius + std::numeric_limits<float>::epsilon();
            Distance distance = calculDistance(robot.position, robotOther.position);
            if (distance <= limit) return true;
        }
    }
    for(ParticleInfo& particle : state.particles) {
        Distance limit = robot.radius + particle.radius + std::numeric_limits<float>::epsilon();
        Distance distance = calculDistance(robot.position, particle.position);
        if (distance <= limit) return true;
    }

    return false;
}
