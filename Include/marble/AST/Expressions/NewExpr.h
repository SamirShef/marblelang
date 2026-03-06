#pragma once
#include <marble/AST/Expressions/ArrInitExpr.h>
#include <marble/AST/Expressions/StructExpr.h>
#include <marble/Basic/ASTType.h>

namespace marble {
    class NewExpr : public Expr {
        ASTType _type;
        StructExpr *_se;
        ArrInitExpr *_arrInit;

    public:
        explicit NewExpr(ASTType type, StructExpr *se, ArrInitExpr *arrInit, llvm::SMLoc startLoc, llvm::SMLoc endLoc) : _type(type), _se(se), _arrInit(arrInit),
                                                                                                                         Expr(NkNewExpr, startLoc, endLoc) {}

        constexpr static bool
        classof(const Node *node) {
            return node->GetKind() == NkNewExpr;
        }

        ASTType &
        GetType() {
            return _type;
        }

        StructExpr *
        GetStructExpr() const {
            return _se;
        }

        ArrInitExpr *
        GetArrInitExpr() const {
            return _arrInit;
        }
    };
}
