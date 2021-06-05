#ifndef _PRINT_H
#define _PRINT_H

#include "inst.hh"
#include "expr.hh"

class Print : public Instruction {
  Expression* to_print;
public:
  Print(Expression* to_print);
  ~Print();

  inline const Expression* getBody() const { return to_print; }
  
  void visit(Visitor& visitor) const;
  double inter(Inter& visitor) const;
  
};

#endif
