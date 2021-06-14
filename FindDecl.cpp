#include "DeclFindingAction.h"

#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

static llvm::cl::extrahelp
    CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);
llvm::cl::OptionCategory FindDeclCategory("find-decl options");

#define FIND_DECL_VERSION "0.0.1"

static void PrintVersion(llvm::raw_ostream &outs) {
  outs << "find-decl version: " << FIND_DECL_VERSION << "\n";
}

static char FindDeclUsage[] = "find-decl <source file>";

int main(int argc, const char **argv) {
  llvm::cl::SetVersionPrinter(PrintVersion);
  auto option = clang::tooling::CommonOptionsParser::create(argc, argv, FindDeclCategory, llvm::cl::OneOrMore,
                                             FindDeclUsage);
  if(!option)
  {
    option.takeError();
  }
  auto files = option->getSourcePathList();
  clang::tooling::ClangTool tool(option->getCompilations(), files);

  return tool.run(clang::tooling::newFrontendActionFactory<DeclFindingAction>().get());
}

