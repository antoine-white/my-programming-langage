cd src

g++    -c -o ../obj/affect.o       ./AST/affect.cc
g++    -c -o ../obj/var.o          ./AST/var.cc
g++    -c -o ../obj/block.o        ./AST/block.cc
g++    -c -o ../obj/cond.o         ./AST/cond.cc
g++    -c -o ../obj/decl.o         ./AST/decl.cc
g++    -c -o ../obj/float.o        ./AST/float.cc
g++    -c -o ../obj/ope.o          ./AST/ope.cc
g++    -c -o ../obj/print.o        ./AST/print.cc
g++    -c -o ../obj/while.o        ./AST/while.cc
g++    -c -o ../obj/seq.o          ./AST/seq.cc

g++    -c -o ../obj/compiler.o     ./visitors/compiler.cc
g++    -c -o ../obj/printer.o      ./visitors/printer.cc
g++    -c -o ../obj/interpreter.o  ./visitors/interpreter.cc

bison -d parser.yy
flex lexer.ll

g++    -c -o ../obj/parser.tab.o parser.tab.cc
g++    -c -o ../obj/main.o main.cc

cd ../obj
g++ -o ../interpreter.exe affect.o var.o compiler.o block.o cond.o decl.o float.o ope.o print.o while.o seq.o printer.o interpreter.o ../src/lex.yy.c parser.tab.o main.o -ll -Wl,--trace-symbol=yyerror