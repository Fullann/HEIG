//
// Created by Matheo on 27.08.2024.
//

#include "Robot.h"
#include "State.h"
#include "Constraints.h"
#ifndef PIN_2024_ALGO_TRAJ_H
#define PIN_2024_ALGO_TRAJ_H

std::vector<std::pair<RobotInfo, ParticleInfo>> SetOneParticleToRobots(Robots& robots, Particles& particles);

double angleBetween2(const Position& p1, const Position& p2);
bool setRobotsSpeed(Constraints constraints, std::vector<std::pair<RobotInfo, ParticleInfo>>& idRobot_idParticle, const Time& CurrentTime);

#endif //PIN_2024_ALGO_TRAJ_H
