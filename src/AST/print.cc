#include "print.hh"

Print::Print(Expression* to_print) : to_print(to_print){

}
Print::~Print(){
    delete to_print;
}

  
void Print::visit(Visitor& visitor) const{
    return;
}

double Print::inter(Inter& visitor) const{
    return visitor.interPrint(this);
}
