%{
 /* Fais un copier coller dans le fichier parser.tab.hh */
#include <iostream>
#include "./visitors/printer.hh"	
#include <vector>
#include <algorithm>


using namespace std;

extern std::vector<std::string> errors;

void yyerror(const char *s) {
  errors.push_back(s);
}
extern int yylex();
extern Instruction *fullinstruction;
extern std::vector<Sequence*> previous;

int count_seq = 0;
%}

%debug

%define parse.error verbose

%code requires {
  /* Fais un copier coller dans le fichier parser.tab.cc */
  #include "visitors/printer.hh"
  
  #include "AST/print.hh"
  #include "AST/env.hh"
}
%union {
	char ident[255];
	double value;
  int lineNb;
  Expression* exp;
  Instruction* instr;
  Sequence* seqq;
}

%token<lineNb> VAR EQUAL IF ELSE WHILE SEMI_COLON LPAR RPAR LBR RBR PRINT ENV
%token<lineNb> OPLUS OMINUS OTIMES ODIV
%token<lineNb> OINF OINFEG OSUP OSUPEG

%token<ident> ID
%token<value> NUM



%left OPLUS OMINUS
%left OTIMES ODIV

%type<value> litteral
%type<exp> expr
%type<exp> exprbool
%type<instr> bloc

%type<instr> affect
%type<seqq> decl 
%type<instr> while
%type<instr> cond 
%type<instr> print
%type<instr> env
%type<instr> instruction 
%type<seqq> seq

%start prog
%%

prog: seq { fullinstruction = $1;}
;

seq: seq instruction { 
  if ($1 == NULL
  ||std::find(previous.begin(),previous.end(),$1) == previous.end()
  ||previous.size() < count_seq)
  {    
    printf("==newSeqence==\n");
    auto tmp = new Sequence($2);
    previous.push_back(tmp);    
    $$ = tmp;
  } 
  else 
  {
    printf("add\n");
    $1->add($2);    
  }
}
| { printf("==fin \n"); count_seq++;  }
;

instruction: affect { $$ = $1; }
|  decl  { $$ = $1; }
|  bloc  { $$ = $1; }
|  while { $$ = $1; }
|  cond  { $$ = $1; }
|  print { $$ = $1; }
|  env   { $$ = $1; }
;

env : ENV SEMI_COLON{ $$ = new Env();}
;

print: PRINT expr SEMI_COLON{$$ = new Print($2);}
;

affect: ID EQUAL expr SEMI_COLON { printf("affect: %s = \n",$1); $$ = (new Affect($1,$3)); }
;

decl: VAR ID SEMI_COLON { $$ = new Sequence(new Decl($2)); }
|  VAR ID EQUAL expr SEMI_COLON { 
    printf("affect: %s = \n",$2);
    Sequence* tmp = new Sequence(new Decl($2)); 
    tmp->add(new Affect($2,$4));
    $$ = tmp;
  }
;

cond: IF LPAR exprbool RPAR instruction ELSE instruction { $$ = (new Cond($3,$5,$7));  }
;

while: WHILE LPAR exprbool RPAR instruction { printf("while\n"); $$ = new While($3,$5); }
;

bloc: LBR seq RBR { printf("block\n");$$ = new Block($2); }
;


expr: litteral { $$ = new Float($1); }
| ID { printf("id: %s\n",$1); $$ = new Var($1); }
| expr OPLUS expr { $$ = new Operator(PLUS,$1,$3); }
| expr OMINUS expr { $$ = new Operator(MOINS,$1,$3);  }
| expr OTIMES expr { $$ = new Operator(MULT,$1,$3);  }
| expr ODIV expr { $$ = new Operator(DIV,$1,$3);  }
| LPAR expr RPAR { $$ = $2; }
;

exprbool:
  expr OINF expr { $$ = new Operator(INF,$1,$3); }
| expr OINFEG expr { $$ = new Operator(INFEG,$1,$3); }
| expr OSUP expr { $$ = new Operator(SUP,$1,$3);  }
| expr OSUPEG expr { $$ = new Operator(SUPEG,$1,$3); }
;

litteral: NUM { printf("%f\n",$1); $$ = $1; }
;

%%

//kicfvszi
