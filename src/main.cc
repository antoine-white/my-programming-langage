
#define INTERPRETER
#include "../VERSION"


#include "./visitors/printer.hh"
#include "./visitors/interpreter.hh"
#include "./visitors/compiler.hh"
#include "vector"
#include "parser.tab.hh"
#include <errno.h>
#include <string.h>
#include <fstream>
#include <cstdlib> 

Instruction *fullinstruction = NULL; // variable retenant le resultat final du parser...
std::vector<std::string> errors;
std::vector<std::string> infos;
std::vector<std::string> to_print;
std::vector<Sequence *> previous;

bool handleErrors(std::vector<std::string> err)
{
  if (err.size() == 0)
  {
    return true;
  }
  else
  {
    std::cout << "Found "
              << err.size()
              << " errors ! " << std::endl;
    for (auto error : err)
    {
      std::cout << error << std::endl;
    }
    return false;
  }
}

void displayInfos(std::vector<std::string> i)
{
  for (auto info : i)
  {
    std::cout << info << std::endl;
  }
}

extern FILE *yyin;
// buffer state. This is used to parse string in memory
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char *str); // it does not work.
extern YY_BUFFER_STATE yy_scan_buffer(char *, size_t);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern void yy_switch_to_buffer(YY_BUFFER_STATE buffer);
extern void yy_flush_buffer(YY_BUFFER_STATE buffer);

int main(int argc, char **argv)
{
  /*extern int yydebug;
  yydebug = 1;*/

#ifdef INTERPRETER
  if (argc == 2)
  {
    yyin = fopen(argv[1], "r");
    if (yyin == NULL)
    {
      std::cerr << "Cannot open file : " << argv[1] << std::endl
                << strerror(errno) << std::endl;
      return EXIT_FAILURE;
    }
    yyparse();

    if (handleErrors(errors) && fullinstruction)
    {
      Interpreter i;
      Printer p;
      fullinstruction->inter(i);
      handleErrors(errors);
      displayInfos(to_print);
      fullinstruction->visit(p);
      //i.printEnv();
    }
  }
  else
  {

    Interpreter i;
    std::string version = VERSION;
    std::cout << "Interpreter TLC\nVersion " << version << std::endl;

    std::string code;
    std::cout << "\n>>> ";
    std::getline(std::cin, code);
    char *char_arr = &code[0];
    while (code != ".exit")
    {

      YY_BUFFER_STATE buffer = yy_scan_string(char_arr);
      yy_switch_to_buffer(buffer);
      yyparse();
      yy_flush_buffer(buffer);
      yy_delete_buffer(buffer);

      if (handleErrors(errors) && fullinstruction)
      {
        fullinstruction->inter(i);
        handleErrors(errors);
        displayInfos(to_print);
        //i.printEnv();
      }
      errors.clear();
      to_print.clear();
      infos.clear();
      fullinstruction = NULL;
      previous.clear();
      std::cout << "\n>>> ";
      std::getline(std::cin, code);
      char_arr = &code[0];
    }
    /*

    if (handleErrors(errors) && fullinstruction)
    {
      Interpreter i;
      fullinstruction->inter(i);
      handleErrors(errors);
      displayInfos(infos);
      //i.printEnv();
    }*/
  }
#else
  //compiler
  std::string outpoutFile = "a.exe";
  std::string inFile;
  switch (argc)
  {
  case 3:
    outpoutFile = argv[2];
  case 2:
    inFile = argv[1];
    break;
  default:
    std::cout << "usage : $ compiler inputFile [outputFile]" << std::endl;
    return EXIT_FAILURE;
  }
  yyin = fopen(argv[1], "r");
    if (yyin == NULL)
    {
      std::cerr << "Cannot open file : " << argv[1] << std::endl
                << strerror(errno) << std::endl;
      return EXIT_FAILURE;
    }
    yyparse();

    if (handleErrors(errors) && fullinstruction)
    {
      Compiler i;
      std::string code = "#include <iostream>\n#include <string>\nint main(){\n";
      code += i.to_cpp(fullinstruction);
      code += "\nreturn 0;}";
      if (handleErrors(errors))
      {
        std::ofstream out(".tmp.cpp");
        out << code;
        out.close();
        system("g++ -c -o a.o .tmp.cpp");
        system(("g++ -o " + outpoutFile + " a.o").c_str());
        remove(".tmp.cpp");
        remove("a.o");
      }      
    }

#endif // INTERPRETER

  return 0;
}
