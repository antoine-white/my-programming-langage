#include "block.hh"

Block::Block(Instruction *body)
  : body(body)
{
}

Block::~Block() {
  delete body;
}

void Block::visit(Visitor& visitor) const {
  return visitor.visitBlock(this);
}

double Block::inter(Inter& visitor) const {
  return visitor.interBlock(this);
}