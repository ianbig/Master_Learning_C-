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
  NumExpression(long val_s) : val(val_s) {
    // std::cout << "NumExpression is Built" << std::endl;
  }
  virtual std::string toString() const {
    std::stringstream ss;
    ss << val;

    return ss.str();
  }

  virtual ~NumExpression() {  //std::cout << "~NumExpression() is called" << std::endl;
  }
};

class Operation : public Expression {
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  Operation(Expression * lhs_t, Expression * rhs_t) : lhs(lhs_t), rhs(rhs_t) {
    // std::cout << "Operation is constructed" << std::endl;
  }
  virtual std::string toString() const = 0;
  virtual ~Operation() {
    // std::cout << "~Operation() is callend" << std::endl;
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public Operation {
 public:
  PlusExpression(Expression * lhs_t, Expression * rhs_t) : Operation(lhs_t, rhs_t) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ss.str();
  }

  virtual ~PlusExpression() {
    // std::cout << "~PlusExpression() is called" << std::endl;
  }
};

class MinusExpression : public Operation {
 public:
  MinusExpression(Expression * lhs_t, Expression * rhs_t) : Operation(lhs_t, rhs_t) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return ss.str();
  }

  virtual ~MinusExpression() {
    // std::cout << "~MinusExpression() is called" << std::endl;
  }
};

class TimesExpression : public Operation {
 public:
  TimesExpression(Expression * lhs_t, Expression * rhs_t) : Operation(lhs_t, rhs_t) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return ss.str();
  }

  virtual ~TimesExpression() {
    // std::cout << "~TimesExpression() is called" << std::endl;
  }
};

class DivExpression : public Operation {
 public:
  DivExpression(Expression * lhs_t, Expression * rhs_t) : Operation(lhs_t, rhs_t) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return ss.str();
  }

  virtual ~DivExpression() {
    // std::cout << "~DivExpression() is called" << std::endl;
  }
};
#endif
