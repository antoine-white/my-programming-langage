#include "interpreter.hh"
#include <iostream>
#include <iterator>

using namespace std;

/*if (env.find(d->getVar()) == env.end())
    {
        cout << "create var : " << d->getVar() << endl{}      
        env.insert(pair<string, double>(d->getVar(),0.0)){}
    }
    else
    {
        errors.push_back("Variable " + d->getVar() + " already declared"){} 
    }*/

double Interpreter::interFloat(const Float *f)
{
    return f->getValue();
}

double Interpreter::interVar(const Var *v)
{
    if (env.find(v->getIdent()) == env.end())
    {
        errors.push_back("Variable " + v->getIdent() + " used without being declared");
        throw std::exception();
    }
    else
        return env[v->getIdent()];
}

double Interpreter::interOperator(const Operator *o)
{
    double left = o->getLeft()->inter(*this);
    double right = o->getRight()->inter(*this);
    switch (o->getSymbol())
    {
    case PLUS:
        return left + right;
    case MOINS:
        return left - right;
    case MULT:
        return left * right;
    case DIV:
        return left / right;
    case INF:
        return left < right;
    case INFEG:
        return left <= right;
    case SUP:
        return left > right;
    case SUPEG:
        return left >= right;
    case EGALITE:
        return left == right;
    case DIFF:
        return left != right;
    default:
        errors.push_back("Operator unknown between " + std::to_string(left) + " and " + std::to_string(right));
        throw std::exception();
    }
}

double Interpreter::interAffect(const Affect *a)
{
    if (env.find(a->getVar()) == env.end())
    {
        errors.push_back("Variable " + a->getVar() + " used without being declared");
        throw std::exception();
    }
    else
    {
        env[a->getVar()] = a->getExpr()->inter(*this);
        infos.push_back(a->getVar() + " = " + std::to_string(env[a->getVar()]));
    }
    return 0.0;
}

double Interpreter::interBlock(const Block *b)
{
    return b->getBody()->inter(*this);
}

double Interpreter::interCond(const Cond *c)
{
    if (c->getCond()->inter(*this) != 0)
    {
        c->getCons()->inter(*this);
    }
    else
    {
        c->getAlt()->inter(*this);
    }
    return 0.0;
}

double Interpreter::interDecl(const Decl *d)
{
    if (env.find(d->getVar()) == env.end())
    {
        infos.push_back("create var : " + d->getVar());
        env.insert(pair<string, double>(d->getVar(), 0.0));
    }
    else
    {
        errors.push_back("Variable " + d->getVar() + " already declared");
        throw std::exception();
    }
    return 0.0;
}

double Interpreter::interWhile(const While *w)
{
    while (w->getCond()->inter(*this) != 0){        
        w->getBody()->inter(*this);
    }
    return 0.0;
}

double Interpreter::interSeq(const Sequence *s)
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

void Interpreter::printEnv()
{
    std::string line = "=================================================";
    to_print.push_back("\n Enviromnemt : (symbol => value)\n" + line);
    for (auto const &x : env)
    {
        auto tmp = std::to_string(x.second);
        to_print.push_back("| " + x.first + " => " + tmp + '\n'+line); 
    }
}

double Interpreter::interPrint(const Print *p)
{
    to_print.push_back(std::to_string(p->getBody()->inter(*this)));
    return 0.0;
}

double Interpreter::interEnv(const Env *p)
{
    printEnv();
    return 0.0;
}

