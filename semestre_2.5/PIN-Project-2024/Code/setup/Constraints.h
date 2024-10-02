#ifndef ROBOTS_CONSTRAINTS_H
#define ROBOTS_CONSTRAINTS_H

#include "Types.h"
#include "json_util.h"

struct Constraints {
    double CommandTimeInterval;
    double maxBackwardSpeed;
    double maxForwardSpeed;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Constraints, CommandTimeInterval, maxBackwardSpeed, maxForwardSpeed)
    JSON_DEFINE_FLUX_OPERATORS(Constraints)
};

#endif // ROBOTS_CONSTRAINTS_H
