#ifndef _ENV_H
#define _ENV_H

#include "inst.hh"

class Env : public Instruction {
public:
  Env() { }
  ~Env() { }
  double inter(Inter& visitor) const {
    return visitor.interEnv(this);
  };
  void visit(Visitor& visitor) const {};
};

#endif
