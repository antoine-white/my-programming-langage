#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <map> 
#include <string>
#include <vector>

#include "../visitors/visitor.hh"
#include "../AST/while.hh"
#include "../AST/affect.hh"
#include "../AST/block.hh"
#include "../AST/cond.hh"
#include "../AST/decl.hh"
#include "../AST/float.hh"
#include "../AST/var.hh"
#include "../AST/ope.hh"
#include "../AST/seq.hh"
#include "../AST/print.hh"
#include "../AST/env.hh"

extern std::vector<std::string> errors;
extern std::vector<std::string> infos;
extern std::vector<std::string> to_print;

class Interpreter : public Inter {
    std::map<std::string,double> env;
    void printEnv();
public:
    double interFloat(const Float *f) ;
    double interVar(const Var *v) ;
    double interOperator(const Operator *o) ;
    double interAffect(const Affect *a) ;
    double interBlock(const Block *b) ;
    double interCond(const Cond *c) ;
    double interDecl(const Decl *d) ;
    double interWhile(const While *w) ;
    double interSeq(const Sequence *s) ;
    double interPrint(const Print *p);
    double interEnv(const Env *p);
};


#endif
