#ifndef _PRINTER_H
#define _PRINTER_H


#include "visitor.hh"
#include "../AST/while.hh"
#include "../AST/affect.hh"
#include "../AST/block.hh"
#include "../AST/cond.hh"
#include "../AST/decl.hh"
#include "../AST/float.hh"
#include "../AST/var.hh"
#include "../AST/ope.hh"
#include "../AST/seq.hh"


class Printer : public Visitor {
public:
  void visitFloat(const Float *f);
  void visitVar(const Var *v);
  void visitOperator(const Operator *o);
  void visitAffect(const Affect *a);
  void visitBlock(const Block *b);
  void visitCond(const Cond *c);
  void visitDecl(const Decl *d);
  void visitWhile(const While *w);
  void visitSeq(const Sequence *s);
};


#endif
