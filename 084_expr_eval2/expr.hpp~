#ifndef _EXPR_HPP_
#define _EXPR_HPP_

#include <iostream>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {  // std::cout << "~Expression is called" << std::endl;
  }
};

class NumExpression : public Expression {
  int val;

 public:
  NumExpression(long val_s) : val(val_s) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << val;

    return ss.str();
  }

  virtual ~NumExpression() {  //std::cout << "~NumExpression() is called" << std::endl;
  }
};

class PlusExpression : public Expression {
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs_t, Expression * rhs_t) : lhs(lhs_t), rhs(rhs_t) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ss.str();
  }

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
    // std::cout << "~PlusExpression() is called" << std::endl;
  }
};
#endif
