#include "affect.hh"


Affect::Affect(string var, Expression *expr)
  : var(var), expr(expr)
{
  
}

Affect::~Affect() {
  delete expr;
}

void Affect::visit(Visitor& visitor) const {
  return visitor.visitAffect(this);
}

double Affect::inter(Inter& visitor) const {
  return visitor.interAffect(this);
}