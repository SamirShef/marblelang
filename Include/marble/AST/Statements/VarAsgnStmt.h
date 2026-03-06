#pragma once
#include <marble/AST/Stmt.h>
#include <marble/AST/Expr.h>
#include <marble/Basic/ASTType.h>
#include <vector>

namespace marble {
    class VarAsgnStmt : public Stmt {
        std::string _name;
        Expr *_expr;
        unsigned char _derefDepth;
        std::vector<Expr *> _depthArrAccessing;

    public:
        explicit VarAsgnStmt(std::string name, Expr *expr, std::vector<Expr *> depthArrAccessing, AccessModifier access, llvm::SMLoc startLoc, llvm::SMLoc endLoc)
                           : _name(name), _expr(expr), _depthArrAccessing(depthArrAccessing), Stmt(NkVarAsgnStmt, access, startLoc, endLoc) {}

        constexpr static bool
        classof(const Node *node) {
            return node->GetKind() == NkVarAsgnStmt;
        }

        std::string
        GetName() const {
            return _name;
        }
        
        Expr *
        GetExpr() const {
            return _expr;
        }

        unsigned char
        GetDerefDepth() const {
            return _derefDepth;
        }

        void
        SetDerefDepth(unsigned char dd) {
            _derefDepth = dd;
        }

        std::vector<Expr *>
        GetDepthArrAccessing() const {
            return _depthArrAccessing;
        }

        void
        SetDepthArrAccessing(const std::vector<Expr *> &daa) {
            _depthArrAccessing = daa;
        }
    };
}
