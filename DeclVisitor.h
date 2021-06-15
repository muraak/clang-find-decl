#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/raw_ostream.h"

#include <string>
#include <sstream>

class DeclVisitor : public clang::RecursiveASTVisitor<DeclVisitor> {
  clang::SourceManager &SourceManager;

public:
  DeclVisitor(clang::SourceManager &SourceManager)
      : SourceManager(SourceManager) {}

  bool VisitFunctionDecl(clang::FunctionDecl *D) {
      llvm::outs() << "$Func:" << D->getQualifiedNameAsString() << "$"
                 << getDeclLocation(D->getBeginLoc()) << "\n";
    return true;
  }

  bool VisitParmVarDecl(clang::ParmVarDecl * D) {
    llvm::outs() << "$Param:" << D->getQualifiedNameAsString() << "\n";
    return true;
  }

private:
  std::string getDeclLocation(clang::SourceLocation Loc) const {
    std::ostringstream OSS;
    OSS /*<< SourceManager.getFilename(Loc).str() << "@"*/
        << SourceManager.getSpellingLineNumber(Loc) << "$"
        << SourceManager.getSpellingColumnNumber(Loc);
    return OSS.str();
  }
};
