#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H

#include "Position.h"
#include "Particle.h"
#include "Types.h"
#include "json_util.h"
#include <iostream>

Position operator+(const Position& vec1,const Position& vec2);
Position operator*(const Position& vec, double number);

struct RobotInfo {
   int id; // unique identifier
   Position position; // (x,y) coordinates of the robot in the world (in pixels)
   Distance radius; // radius of the circular robot. (pixels)
   Angle angle; // direction in which the robot moves. [0,360[ in degrees. 0 = 3 o'clock, 90 = noon
   Angle captureAngle; // ]0,180] in degrees. max angular difference between robot angle and robot/particle direction
   // so the particle is cleared when a robot/particle collision occurs. A robot with 180 degrees captureAngle always
   // clears the particles it collides with, regardless of the collision angle. A robot with captureAngle close to
   // zero needs to be perfectly aligned with the particle to clear it.
   Speed leftSpeed; // linear speed of the leftmost part of the robot in pixels/sec
   Speed rightSpeed; // linear speed of the rightmost part of the robot in pixels/sec
   Score score; // sum of the areas (pi*R^2) of all particles that this robot cleared.

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(RobotInfo, id, position, radius, angle, captureAngle, leftSpeed, rightSpeed, score)

   JSON_DEFINE_FLUX_OPERATORS(RobotInfo)

   void move(Time time);
   Position findPotentialMove(Time timeFrame);
};



using Robots = std::vector<RobotInfo>;

bool isWithinCaptureAngle(const RobotInfo& robot, const ParticleInfo& particle);


#endif //ROBOTS_ROBOT_H

