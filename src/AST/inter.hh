#pragma once 

class Print;
class Float;
class Operator;
class Affect;
class Block;
class Cond;
class Decl;
class While;
class Sequence;
class Var;
class Env;

class Inter {
public:
  virtual double interFloat(const Float *f) = 0;
  virtual double interVar(const Var *v) = 0;
  virtual double interOperator(const Operator *o) = 0;
  virtual double interAffect(const Affect *a) = 0;
  virtual double interBlock(const Block *b) = 0;
  virtual double interCond(const Cond *c) = 0;
  virtual double interDecl(const Decl *d) = 0;
  virtual double interWhile(const While *w) = 0;
  virtual double interSeq(const Sequence *s) = 0;
  virtual double interPrint(const Print *p) = 0;
  virtual double interEnv(const Env *p) = 0;
};