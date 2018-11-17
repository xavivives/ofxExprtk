#pragma once

#include "exprtk.hpp"
#include "glm/detail/type_vec.hpp"

using namespace std;

template<class T>
class ofxExpr_ {
    
public:
    ofxExpr_(const string &expression_string) : expression_string(expression_string) {
        expression.register_symbol_table(symbol_table);
    }
    bool add_var(const string &name, T &value) {
        return symbol_table.add_variable(name, value);
    }
    bool add_const(const string &name, const T &value) {
        return symbol_table.add_constant(name, value);
    }
    bool add_stringvar(const string &name, string &value) {
        return symbol_table.add_stringvar(name, value);
    }
    template<typename T1>
    bool add_vector(const string &name, vector<T1> &value) {
        return symbol_table.add_vector(name, value);
    }
    bool compile() {
        return parser.compile(expression_string, expression);
    }
    T value() const {
        return expression.value();
    }
    
private:
    exprtk::symbol_table<double> symbol_table;
    exprtk::expression<double>   expression;
    exprtk::parser<double>       parser;
    
    string expression_string;
};

typedef ofxExpr_<double> ofxExpr;
typedef ofxExpr_<float> ofxFloatExpr;
typedef ofxExpr_<int> ofxIntExpr;
typedef ofxExpr_<glm::vec2> ofxVec2Expr;
typedef ofxExpr_<glm::vec3> ofxVec3Expr;
typedef ofxExpr_<glm::vec4> ofxVec4Expr;
