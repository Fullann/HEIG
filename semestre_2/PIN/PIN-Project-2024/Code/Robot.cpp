#include <cmath>
#include "Robot.h"


double angleBetween(const Position& p1, const Position& p2) {
    return std::atan2(p2.y - p1.y, p2.x - p1.x) * 180.0 / M_PI;
}

bool isWithinCaptureAngle(const RobotInfo& robot, const ParticleInfo& particle) {
    double angleToParticle = angleBetween(robot.position, particle.position);
    double robotDirection = robot.angle;
    double captureAngle = robot.captureAngle;

    double angleDifference = std::fabs(robotDirection - angleToParticle);
    if (angleDifference > 180.0) {
        angleDifference = 360.0 - angleDifference;
    }

    return angleDifference <= captureAngle;
}

/**
 * @brief RobotInfo::move - Method that calculates robot's position after a certain time frame.
 * @param timeFrame - time that passes after the initial state.
 */
void RobotInfo::move(Time timeFrame){
    if(this->leftSpeed == this->rightSpeed){
        this->position = this->position+Position{this->leftSpeed*cos(this->angle/180*M_PI)*timeFrame,this->leftSpeed*sin(this->angle/180*M_PI)*timeFrame};
    }
    else if(this->leftSpeed == -(this->rightSpeed)) {
        const Speed turningSpeed = (this->leftSpeed-this->rightSpeed)/this->radius/2;
        this->angle = this->angle+(turningSpeed*timeFrame/M_PI*180);
    }
    else {
        const Distance bigRadius = this->radius*(this->leftSpeed+this->rightSpeed)/(this->leftSpeed-this->rightSpeed);
        const Speed turningSpeed = (this->leftSpeed-this->rightSpeed)/this->radius/2;
        const Position tangentVector = Position{bigRadius*cos((this->angle)*M_PI/180),bigRadius*sin((this->angle)*M_PI/180)};
        const Position radiusVector = Position{bigRadius*(-sin((this->angle)*M_PI/180)),bigRadius*cos((this->angle)*M_PI/180)};
        const Position distance = tangentVector*sin(turningSpeed*timeFrame)+radiusVector*(1-cos(turningSpeed*timeFrame));
        this->angle = this->angle+turningSpeed*timeFrame/M_PI*180;
        this->position = this->position+distance;
    }
}

Position RobotInfo::findPotentialMove(Time timeFrame){
    if(this->leftSpeed == this->rightSpeed){
        return this->position+Position{this->leftSpeed*cos(this->angle/180*M_PI),this->leftSpeed*sin(this->angle/180*M_PI)};
    }
    else if(this->leftSpeed == -(this->rightSpeed)) {
        return this->position;
    }
    else {
        const Distance bigRadius = this->radius*(this->leftSpeed+this->rightSpeed)/(this->leftSpeed-this->rightSpeed);
        const Speed turningSpeed = (this->leftSpeed-this->rightSpeed)/this->radius/2;
        const Position tangentVector = Position{bigRadius*cos((this->angle)*M_PI/180),bigRadius*sin((this->angle)*M_PI/180)};
        const Position radiusVector = Position{bigRadius*(-sin((this->angle)*M_PI/180)),bigRadius*cos((this->angle)*M_PI/180)};
        const Position distance = tangentVector*sin(turningSpeed*timeFrame)+radiusVector*(1-cos(turningSpeed*timeFrame));
        return this->position+distance;
    }
}

Position operator+(const Position& vec1,const Position& vec2){
    return Position{vec1.x+vec2.x,vec1.y+vec2.y};
}

Position operator*(const Position& vec, double number){
    return Position{vec.x*number,vec.y*number};
}
