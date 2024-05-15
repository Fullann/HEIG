#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include <memory>

class bad_expression{};

class Expression {
   bool is_leaf;
   union
   {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#pragma GCC diagnostic ignored "-Wnested-anon-types"
      struct {
         Expression* lhs;
         Expression* rhs;
         char op;
      };
#pragma GCC diagnostic pop
      double value;
   };

public:
    Expression(std::istream& in);
    ~Expression();
    explicit operator double() const noexcept;
    std::string to_rpn() const;
    std::string to_infix() const;
    std::string to_pn() const;
};

#endif //EXPRESSION_H
