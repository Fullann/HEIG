#include "Particle.h"

std::vector<ParticleInfo> ParticleInfo::disintegrate() const {
    std::vector<ParticleInfo> children={};
    std::vector<Position> offsets = {
        {std::cos(M_PI/4), std::sin(M_PI/4)},
        {std::cos(3*M_PI/4), std::sin(3*M_PI/4)},
        {std::cos(-M_PI/4), std::sin(-M_PI/4)},
        {std::cos(-3*M_PI/4), std::sin(-3*M_PI/4)}
    };
    if (explosionTimes.size()==1) {
        return children;
    }
    else{
        for(size_t child = 0;child < 4;child++){
            ParticleInfo childParticle;
            Distance newRadius = radius / (1 + std::sqrt(2));

            childParticle.id= this->id+child;
            childParticle.position={
                position.x + offsets[child].x * (radius - newRadius),
                position.y + offsets[child].y * (radius - newRadius)
            };
            childParticle.radius = newRadius;
    for(size_t i = 0; i < this->explosionTimes.size()-1;i++){
        std::vector<Time>explosionTimesPerExlplosion;
        int indexLimit=pow(4,i);
            for(size_t j=0;j < indexLimit;j++){
                explosionTimesPerExlplosion.push_back(this->explosionTimes[i+1][indexLimit*child+j]);
            }
            childParticle.explosionTimes.push_back(explosionTimesPerExlplosion);
        }
    children.push_back(childParticle);
    }
}
    return children;
}

