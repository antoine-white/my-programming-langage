#ifndef _TERM_H
#define _TERM_H

#include <iostream>
#include <string>
using namespace std;

#include "../visitors/visitor.hh"
#include "inter.hh"

class Term {
 public:
  virtual ~Term() { }
  
  virtual void visit(Visitor& visitor) const = 0;

  virtual double inter(Inter& visitor) const = 0;
};

#endif
