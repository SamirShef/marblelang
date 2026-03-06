#pragma once
#include <marble/AST/Expr.h>
#include <marble/Basic/ASTType.h>
#include <vector>

namespace marble {
    class ArrAccessingExpr : public Expr {
        Expr *_arr;
        std::vector<Expr *> _depthAccessing;

    public:
        explicit ArrAccessingExpr(Expr *arr, std::vector<Expr *> depthAccessing, llvm::SMLoc startLoc, llvm::SMLoc endLoc) : _arr(arr), _depthAccessing(depthAccessing),
                                                                                                                             Expr(NkArrAccessingExpr, startLoc, endLoc) {}

        constexpr static bool
        classof(const Node *node) {
            return node->GetKind() == NkArrAccessingExpr;
        }

        Expr *
        GetArrExpr() const {
            return _arr;
        }

        std::vector<Expr *>
        GetDepthAccessing() const {
            return _depthAccessing;
        }
    };
}
