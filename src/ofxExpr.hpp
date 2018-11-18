#pragma once

#include "exprtk.hpp"
#include "ofParameter.h"

using namespace std;

template<class Type>
class ofxExpr : public ofParameter<Type> {
    
public:
    ofxExpr();
    ofxExpr(const string &expr);
    ofxExpr(const Type &value);
    ofxExpr(const string &name, const Type &value, const Type &min, const Type &max);
    ofxExpr(const ofxExpr<Type>& other);
    ofxExpr<Type>& operator= (const ofxExpr<Type>& other);
    
    ofxExpr<Type> & set(const Type &value);
    ofxExpr<Type> & set(const string &name, const Type &value);
    ofxExpr<Type> & set(const string &name, const Type &value, const Type &min, const Type &max);
    void setName(const std::string & name);
    
    bool add_var(const string &name, Type &value) {
        compiled = false;
        return symbol_table.add_variable(name, value);
    }
    bool add_const(const string &name, const Type &value) {
        compiled = false;
        return symbol_table.add_constant(name, value);
    }
    bool add_stringvar(const string &name, string &value) {
        compiled = false;
        return symbol_table.add_stringvar(name, value);
    }
    template<typename VecType>
    bool add_vector(const string &name, vector<VecType> &value) {
        compiled = false;
        return symbol_table.add_vector(name, value);
    }
    bool compile() {
        if (!compiled) {
            expression.register_symbol_table(symbol_table);
            compiled = parser.compile(str_expr.get(), expression);
        }
        return compiled;
    }
    Type value() const {
        if (use_explicit_value) {
            return this->get();
        }
        return expression.value();
    }
    const string & get_expr() const {
        return str_expr.get();
    }
    void set_expr(const string &value) {
        str_expr.set(value);
        compiled = false;
        use_explicit_value = false;
    }
    ofParameter<string> & get_str_expr() {
        return str_expr;
    }
    bool is_explicit_value() const {
        return use_explicit_value;
    }
    bool is_set() const {
        return str_expr.get() != "" || (use_explicit_value && this->get());
    }
    
    bool operator== (const ofxExpr<Type> &e2) const;
    bool operator!= (const ofxExpr<Type> &e2) const;
    shared_ptr<ofAbstractParameter> newReference() const;
    
private:
    exprtk::symbol_table<Type> symbol_table;
    exprtk::expression<Type>   expression;
    exprtk::parser<Type>       parser;
    
    bool compiled = false;
    bool use_explicit_value = false;
    ofParameter<string> str_expr;
};
