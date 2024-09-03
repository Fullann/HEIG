//
// Created by Matheo on 27.08.2024.
//

#include "Algo_traj.h"

std::vector<std::pair<RobotInfo, ParticleInfo>> SetOneParticleToRobots(Robots& robots, Particles& particles){
    std::vector<std::pair<RobotInfo, ParticleInfo>> idRobot_idParticle {};

    for(auto itR = robots.begin(); itR != robots.end(); ++itR){
        auto temp = particles.begin();
        for (auto it = particles.begin(); it != particles.end(); ++it){
            if (calculDistance(temp->position, itR->position) > calculDistance(it->position, itR->position)){
                temp = it;
            }
        }
        idRobot_idParticle.push_back(std::make_pair(*itR, *temp));
    }
    return idRobot_idParticle;
}

double angleBetween2(const Position& p1, const Position& p2) {
    return std::atan2(p2.y - p1.y, p2.x - p1.x) * 180.0 / M_PI;
}

bool setRobotsSpeed(Constraints constraints, std::vector<std::pair<RobotInfo, ParticleInfo>>& idRobot_idParticle, const Time& CurrentTime){
    bool flag = false;
    for(std::pair<RobotInfo, ParticleInfo>& pair : idRobot_idParticle){
        double oldLeftSpeed = pair.first.leftSpeed;
        double oldRightSpeed = pair.first.rightSpeed;
        double angleBetween = angleBetween2(pair.first.position, pair.second.position);

        if ((angleBetween <= pair.first.angle + 2
        && angleBetween >= pair.first.angle - 2)){
            pair.first.leftSpeed = pair.first.rightSpeed = constraints.maxForwardSpeed;
        }else{
            double maxspeed = std::min(abs(constraints.maxForwardSpeed), abs(constraints.maxBackwardSpeed));

            if (angleBetween < 0){
                maxspeed *= -1;
            }

            double angularspeed = maxspeed / pair.first.radius;
            double timewithoutconstraints = abs((angleBetween - pair.first.angle) / 180 * M_PI / angularspeed) + constraints.CommandTimeInterval;

            pair.first.timeToNextMove += timewithoutconstraints;
            pair.first.leftSpeed = (angleBetween - pair.first.angle) / 180 * M_PI / timewithoutconstraints * pair.first.radius;
            pair.first.rightSpeed = -pair.first.leftSpeed;
        }

        if (oldLeftSpeed != pair.first.leftSpeed || oldRightSpeed != pair.first.rightSpeed){
            flag = true;
        }
    }
    return flag;
}
