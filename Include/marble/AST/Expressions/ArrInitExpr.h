#pragma once
#include <marble/AST/Expr.h>
#include <marble/Basic/ASTType.h>
#include <vector>

namespace marble {
    class ArrInitExpr : public Expr {
        std::vector<Expr *> _init;
        ASTType _arrType;

    public:
        explicit ArrInitExpr(std::vector<Expr *> init, llvm::SMLoc startLoc, llvm::SMLoc endLoc) : _init(init), Expr(NkArrInitExpr, startLoc, endLoc) {}

        constexpr static bool
        classof(const Node *node) {
            return node->GetKind() == NkArrInitExpr;
        }

        std::vector<Expr *>
        GetInit() {
            return _init;
        }

        ASTType &
        GetArrType() {
            return _arrType;
        }
    };
}
