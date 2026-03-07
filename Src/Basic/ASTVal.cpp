#include <marble/Basic/ASTVal.h>

namespace marble {
    std::string
    ASTVal::ToString() const {
        switch (_type.GetTypeKind()) {
            #define TO_STR(field) std::to_string(_data.field)
            case ASTTypeKind::Bool:
                return TO_STR(boolVal);
            case ASTTypeKind::Char:
                return std::string { _data.charVal };
            case ASTTypeKind::I16:
                return TO_STR(i16Val);
            case ASTTypeKind::I32:
                return TO_STR(i32Val);
            case ASTTypeKind::I64:
                return TO_STR(i64Val);
            case ASTTypeKind::F32:
                return TO_STR(f32Val);
            case ASTTypeKind::F64:
                return TO_STR(f64Val);
            case ASTTypeKind::String:
                return _data.str;
            case ASTTypeKind::Noth:
                return "noth";
            case ASTTypeKind::Struct:
            case ASTTypeKind::Trait:
                return _type.GetVal();
            case ASTTypeKind::Nil:
                return "nil";
        }
    }

    double
    ASTVal::AsDouble() const {
        switch (_type.GetTypeKind()) {
            case ASTTypeKind::Bool:
                return _data.boolVal;
            case ASTTypeKind::Char:
                return _data.charVal;
            case ASTTypeKind::I16:
                return _data.i16Val;
            case ASTTypeKind::I32:
                return _data.i32Val;
            case ASTTypeKind::I64:
                return _data.i64Val;
            case ASTTypeKind::F32:
                return _data.f32Val;
            case ASTTypeKind::F64:
                return _data.f64Val;
            case ASTTypeKind::String:
            case ASTTypeKind::Noth:
            case ASTTypeKind::Struct:
            case ASTTypeKind::Trait:
            case ASTTypeKind::Nil:
                return 0;
        }
    }

    ASTVal
    ASTVal::Cast(ASTType type) {
        if (_type == type) {
            return *this;
        }
        if (_type.GetTypeKind() >= ASTTypeKind::Char && _type.GetTypeKind() <= ASTTypeKind::F64 &&
            type.GetTypeKind() >= ASTTypeKind::Char && type.GetTypeKind() <= ASTTypeKind::F64) {
            switch (type.GetTypeKind()) {
                #define VAL(cast_type) ASTVal(type, ASTValData(static_cast<cast_type>(AsDouble())), false, false)
                case ASTTypeKind::Char:
                    return VAL(char);
                case ASTTypeKind::I16:
                    return VAL(short);
                case ASTTypeKind::I32:
                    return VAL(int);
                case ASTTypeKind::I64:
                    return VAL(long);
                case ASTTypeKind::F32:
                    return VAL(float);
                case ASTTypeKind::F64:
                    return VAL(double);
                default: {}
                #undef VAL
            }
        }
        return ASTVal::GetDefaultByType(ASTType::GetNothType());
    }

    ASTVal
    ASTVal::GetVal(double val, ASTType type) {
        switch (type.GetTypeKind()) {
            #define VAL(cast_type) ASTVal(type, ASTValData(static_cast<cast_type>(val)), false, false)
            case ASTTypeKind::Bool:
                return VAL(bool);
            case ASTTypeKind::Char:
                return VAL(char);
            case ASTTypeKind::I16:
                return VAL(short);
            case ASTTypeKind::I32:
                return VAL(int);
            case ASTTypeKind::I64:
                return VAL(long);
            case ASTTypeKind::F32:
                return VAL(float);
            case ASTTypeKind::F64:
                return VAL(double);
            case ASTTypeKind::Noth:
                return ASTVal(type, ASTValData(), false, false);
            case ASTTypeKind::Struct:
            case ASTTypeKind::Trait:
                return VAL(int);
            case ASTTypeKind::Nil:
                return ASTVal(type, ASTValData(static_cast<int>(val)), true, false);
            #undef VAL
        }
    }

    ASTVal
    ASTVal::GetDefaultByType(ASTType type) {
        #define VAL(type_cast) ASTVal(type, ASTValData(static_cast<type_cast>(0)), false, false)
        if (type.IsPointer()) {
            return VAL(int);
        }
        switch (type.GetTypeKind()) {
            case ASTTypeKind::Bool:
                return VAL(bool);
            case ASTTypeKind::Char:
                return VAL(char);
            case ASTTypeKind::I16:
                return VAL(short);
            case ASTTypeKind::I32:
                return VAL(int);
            case ASTTypeKind::I64:
                return VAL(long);
            case ASTTypeKind::F32:
                return VAL(float);
            case ASTTypeKind::F64:
                return VAL(double);
            case ASTTypeKind::String:
                return ASTVal(type, ASTValData(""), false, false);
            case ASTTypeKind::Noth:
            case ASTTypeKind::Struct:
            case ASTTypeKind::Trait:
                return VAL(int);
            case ASTTypeKind::Nil:
                return ASTVal(type, ASTValData(), true, false);
        }
        #undef VAL
    }
}
