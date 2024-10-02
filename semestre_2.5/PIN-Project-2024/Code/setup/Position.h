#ifndef ROBOTS_POSITION_H
#define ROBOTS_POSITION_H

#include "json_util.h"

struct Position {
   double x;
   double y;

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(Position, x, y)
   JSON_DEFINE_FLUX_OPERATORS(Position)

public:
   friend double distanceBetween(Position const& p, Position const& q) {
      return hypot(p.x - q.x, p.y - q.y);
   }
   // Operator +
   friend Position operator+(const Position& vec1, const Position& vec2) {
      return Position{vec1.x + vec2.x, vec1.y + vec2.y};
   }

   // Operator -
   friend Position operator-(const Position& vec1, const Position& vec2) {
      return Position{vec1.x - vec2.x, vec1.y - vec2.y};
   }

   // Operator *
   friend Position operator*(const Position& vec, double number) {
      return Position{vec.x * number, vec.y * number};
   }
};

#endif //ROBOTS_POSITION_H
