%{
#include "parser.tab.hh"
int count = 1;
%}


%%
 // attention aux espaces! et priorite des lignes
__ENV__ { yylval.lineNb = count; return ENV; }
"var"	{ yylval.lineNb = count; return VAR; }
"="	{  yylval.lineNb = count; return EQUAL; }
if	{  yylval.lineNb = count; return IF; }
else	{ yylval.lineNb = count; return ELSE; }
while	{ yylval.lineNb = count; return WHILE; }
print	{ yylval.lineNb = count; return PRINT; }
"+"	{  yylval.lineNb = count; return OPLUS; }
"-"	{  yylval.lineNb = count; return OMINUS; }
"*"	{  yylval.lineNb = count; return OTIMES; }
"/"	{  yylval.lineNb = count; return ODIV; }
"<"	{  yylval.lineNb = count; return OINF; }
"<="	{  yylval.lineNb = count;return OINFEG; }
">"	{  yylval.lineNb = count;return OSUP; }
">="	{  yylval.lineNb = count;return OSUPEG; }
";"	{ yylval.lineNb = count; return SEMI_COLON; }
"("	{ yylval.lineNb = count; return LPAR; }
")"	{ yylval.lineNb = count; return RPAR; }
"{"	{ yylval.lineNb = count; return LBR; }
"}"	{ yylval.lineNb = count; return RBR; }
"begin"	{ yylval.lineNb = count; return LBR; }
"end"	{ yylval.lineNb = count; return RBR; }

[a-zA-Z_][a-zA-Z0-9_]*	{ strcpy(yylval.ident,yytext); return ID; }
[-+]?[0-9]*([.][0-9]+)?([eE][+-]?[0-9]+)?	{ yylval.value = atof(yytext); return NUM; }

\n { count++; }

.  { }

%%
