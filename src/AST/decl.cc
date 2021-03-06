#include "decl.hh"

Decl::Decl(string var) : var(var) {
}

Decl::~Decl() {
  
}

void Decl::visit(Visitor& visitor) const {
  return visitor.visitDecl(this);
}

double Decl::inter(Inter& visitor) const {
  return visitor.interDecl(this);
}
