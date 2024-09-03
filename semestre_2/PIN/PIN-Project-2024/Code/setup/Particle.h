#ifndef ROBOTS_PARTICLE_H
#define ROBOTS_PARTICLE_H

#include <vector>
#include <cmath>

#include "Position.h"
#include "Types.h"
#include "json_util.h"

struct ParticleInfo {
   UniqueId id;
   Position position; // (x, y) coordinates of the particle in the world
   Distance radius;
   std::vector<Times> explosionTimes;// vector of vectors

   //Desintegration method
   std::vector<ParticleInfo> disintegrate() const;

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(ParticleInfo, id, position, radius, explosionTimes)
   JSON_DEFINE_FLUX_OPERATORS(ParticleInfo)
};


using Particles = std::vector<ParticleInfo>;

#endif //ROBOTS_PARTICLE_H
