#ifndef ROBOTS_STATE_H
#define ROBOTS_STATE_H

#include "json_util.h"
#include <vector>
#include "Robot.h"
#include "Particle.h"

struct State {
    Time time;
    Position worldOrigin;
    Position worldEnd;
    Robots robots;
    Particles particles;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(State, time, worldOrigin, worldEnd, robots, particles)
    JSON_DEFINE_FLUX_OPERATORS(State)
};

using States = std::vector<State>;

bool handleDecontamination(State& state);
bool isRobotsBlocked(State& state);

Distance calculDistance(Position a, Position b);
bool isColliding(const RobotInfo& robot, const ParticleInfo& particle);
bool isRobotColliding(const RobotInfo& robot1, const RobotInfo& robot2);

struct Timeline {
    States states;
    State tmpState;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Timeline, states)
    JSON_DEFINE_FLUX_OPERATORS(Timeline)
};

#endif // ROBOTS_STATE_H
