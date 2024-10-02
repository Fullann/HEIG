#include <iostream>
#include <fstream>
#include "json_util.h"
#include "Robot.h"
#include "Particle.h"
#include "State.h"
#include "Types.h"
#include "Constraints.h"
#include "Algo_traj.h"

using json = nlohmann::json;

bool updateState(const Time& time, State& state, std::vector<std::pair<RobotInfo, ParticleInfo>>& nextMove){
    bool flag = false;
    size_t index = 0;
    for(RobotInfo &robot : state.robots){

        if (handleDecontamination(state)){
            nextMove = SetOneParticleToRobots(state.robots, state.particles);
            flag = true;
        }

        if (isRobotsBlocked(state)){
            flag = true;
        }

        robot = nextMove[index].first;
        robot.move2(std::min(1/24.0, abs(robot.timeToNextMove - time)));
        nextMove[index].first.move2(std::min(1/24.0, abs(robot.timeToNextMove - time)));

        index++;
    }
    return flag;
}

void simulate(State& state, const Constraints& constraints, Timeline& timeline) {
    timeline.states.push_back(state);
    auto nextMove = SetOneParticleToRobots(state.robots, state.particles);

    while(!state.particles.empty()){
        bool hasChanged = false;
        if (setRobotsSpeed(constraints, nextMove, state.time)){
            hasChanged = true;
        }

        std::vector<ParticleInfo> newParticles;
        if(updateState(state.time, state, nextMove)){
            hasChanged = true;
        }

        for(auto& particle : state.particles){
            if(particle.explosionTimes[0][0] <= state.time){
                auto temp = particle.disintegrate();
                newParticles.insert(newParticles.end(), temp.begin(), temp.end());
                hasChanged = true;
            } else {
                newParticles.push_back(particle);
            }
        }

        if(hasChanged) {
            state.time += 1/24.0;
            state.particles = std::move(newParticles);
            timeline.states.push_back(state);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <constraints file> <state file> <timeline file>\n";
        return 1;
    }

    std::string constraintsFile = argv[1];
    std::string stateFile = argv[2];
    std::string timelineFile = argv[3];

    std::ifstream constraintsStream(constraintsFile);
    Constraints constraints;
    constraintsStream >> constraints;

    std::ifstream stateStream(stateFile);
    State state;
    stateStream >> state;

    Timeline timeline;
    simulate(state, constraints, timeline);

    std::ofstream timelineStream(timelineFile);
    json timelineJson = timeline;
    timelineStream << timelineJson.dump(4);

    return 0;
}
