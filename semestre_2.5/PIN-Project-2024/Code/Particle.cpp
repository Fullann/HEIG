#include "Particle.h"

std::vector<ParticleInfo> ParticleInfo::disintegrate() const {
    std::vector<ParticleInfo> children;
    if (explosionTimes.empty()) return children;

    double newRadius = radius / (1 + std::sqrt(2));
    std::vector<Position> offsets = {
        {std::cos(M_PI/4), std::sin(M_PI/4)},
        {std::cos(3*M_PI/4), std::sin(3*M_PI/4)},
        {std::cos(-M_PI/4), std::sin(-M_PI/4)},
        {std::cos(-3*M_PI/4), std::sin(-3*M_PI/4)}
    };

    for (int i = 0; i < 4; ++i) {
        Position newPos = {position.x + offsets[i].x * (radius - newRadius),
                           position.y + offsets[i].y * (radius - newRadius)};
        children.push_back({id * 10 + i + 1, newPos, newRadius, explosionTimes});
    }

    return children;
}
