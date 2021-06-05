#include "compiler.hh"
#include <iostream>
#include <iterator>

using namespace std;

double Compiler::interFloat(const Float *f)
{
    code += to_string(f->getValue());
    return f->getValue();
}

double Compiler::interVar(const Var *v)
{
    if (env.find(v->getIdent()) == env.end())
    {
        errors.push_back("Variable " + v->getIdent() + " used without being declared");
        throw std::exception();
    }
    else{
        code += v->getIdent();
        return env[v->getIdent()];
    }

}

double Compiler::interOperator(const Operator *o)
{
    double left = o->getLeft()->inter(*this);
    switch (o->getSymbol())
    {
    case PLUS:
        code += "+";
        break;
    case MOINS:
        code += "-";
        break;
    case MULT:
        code += "*";
        break;
    case DIV:
        code += "/";
        break;
    case INF:
        code += "<";
        break;
    case INFEG:
        code += "<=";
        break;
    case SUP:
        code += ">";
        break;
    case SUPEG:
        code += ">=";
        break;
    case EGALITE:
        code += "==";
        break;
    case DIFF:
        code += "!=";
        break;
    default:
        errors.push_back("Operator unknown");
        throw std::exception();
    }    
    double right = o->getRight()->inter(*this);
    return 0.0;
}

double Compiler::interAffect(const Affect *a)
{
    if (env.find(a->getVar()) == env.end())
    {
        errors.push_back("Variable " + a->getVar() + " used without being declared");
        throw std::exception();
    }
    else
    {
        code += "\n" + a->getVar() + " = ";
        env[a->getVar()] = a->getExpr()->inter(*this);
        infos.push_back(a->getVar() + " = " + std::to_string(env[a->getVar()]));
        code += ";";
    }
    return 0.0;
}

double Compiler::interBlock(const Block *b)
{
    code += "\n{ "; 
    b->getBody()->inter(*this);
    code += "\n}";
    return 0.0;
}

double Compiler::interCond(const Cond *c)
{
    code += "\nif(";
    c->getCond()->inter(*this);
    code += ")";
    c->getCons()->inter(*this);
    code += "\nelse";
    c->getAlt()->inter(*this);    
    return 0.0;
}

double Compiler::interDecl(const Decl *d)
{
    if (env.find(d->getVar()) == env.end())
    {
        infos.push_back("create var : " + d->getVar());
        env.insert(pair<string, double>(d->getVar(), 0.0));
        code += "\ndouble " + d->getVar() + ";";
    }
    else
    {
        errors.push_back("Variable " + d->getVar() + " already declared");
        throw std::exception();
    }
    return 0.0;
}

double Compiler::interWhile(const While *w)
{
    code += "\nwhile(";
    w->getCond()->inter(*this);
    code += ")";
    w->getBody()->inter(*this);
    return 0.0;
}

double Compiler::interSeq(const Sequence *s)
{
    SeqItem *t = s->getFirst();

    while (t != NULL)
    {
        try
        {
            t->getInst()->inter(*this);
        }
        catch (const std::exception &e)
        {
            return -1.0;
        }
        t = t->getNext();
    }

    return 0.0;
}

double Compiler::interPrint(const Print *p)
{
    code += "\nstd::cout << std::to_string(";
    p->getBody()->inter(*this);
    code += ") << std::endl;";
    //to_print.push_back(std::to_string());
    return 0.0;
}

double Compiler::interEnv(const Env *p)
{
    errors.push_back("__ENV__ instruction only available interpreter");
    throw std::exception();
}

std::string Compiler::to_cpp(const Instruction *i)
{
    i->inter(*this);
    return code;
}