#pragma once
#include <marble/AST/Stmt.h>
#include <marble/AST/Expr.h>
#include <marble/Basic/ASTType.h>
#include <vector>

namespace marble {
    class FieldAsgnStmt : public Stmt {
        Expr *_object;
        std::string _name;
        Expr *_expr;
        std::vector<Expr *> _depthArrAccessing;
        ASTType _objType;

    public:
        explicit FieldAsgnStmt(Expr *obj, std::string name, Expr *expr, std::vector<Expr *> depthArrAccessing, AccessModifier access, llvm::SMLoc startLoc, llvm::SMLoc endLoc)
                             : _object(obj), _name(name), _expr(expr), _depthArrAccessing(depthArrAccessing), Stmt(NkFieldAsgnStmt, access, startLoc, endLoc) {}

        constexpr static bool
        classof(const Node *node) {
            return node->GetKind() == NkFieldAsgnStmt;
        }

        Expr *
        GetObject() const {
            return _object;
        }

        std::string
        GetName() const {
            return _name;
        }
        
        Expr *
        GetExpr() const {
            return _expr;
        }

        ASTType
        GetObjType() const {
            return _objType;
        }

        void
        SetObjType(ASTType t) {
            _objType = t;
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
