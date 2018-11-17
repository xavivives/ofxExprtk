#pragma once

#include "exprtk.hpp"

using namespace std;

template<class Type>
class ofxExpr_ {
    
public:
    ofxExpr_() {}
    ofxExpr_(const string &expression_string) : expression_string(expression_string) {}
    ofxExpr_(const Type &value) {
        set_explicit_value(value);
    }
    ofxExpr_(const ofxExpr_& other) {
        expression_string = other.get();
        if (other.get_explicit_value() != NULL) {
            set_explicit_value(*other.get_explicit_value());
        }
    }
    ofxExpr_& operator= (const ofxExpr_& other) {
        if (this != &other) {
            expression_string = other.get();
            if (other.get_explicit_value() != NULL) {
                set_explicit_value(*other.get_explicit_value());
            }
            else {
                unset_explicit_value();
            }
        }
        return *this;
    }
    const string & get() const {
        return expression_string;
    }
    void set(const string &value) {
        compiled = false;
        expression_string = value;
    }
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
            compiled = parser.compile(expression_string, expression);
        }
        return compiled;
    }
    Type value() const {
        if (explicit_value != NULL) {
            return *explicit_value;
        }
        return expression.value();
    }
    void set_explicit_value(const Type &value) {
        if (explicit_value == NULL) {
            explicit_value = shared_ptr<Type>(new Type);
        }
        *explicit_value = value;
    }
    void unset_explicit_value() {
        explicit_value = NULL;
    }
    const shared_ptr<Type> & get_explicit_value() const {
        return explicit_value;
    }
    bool is_set() const {
        return expression_string != "" || explicit_value != NULL;
    }
    
    bool operator== (const ofxExpr_<Type> &e2) const {
        return get_explicit_value() == e2.get_explicit_value() && get() == e2.get();
    }
    bool operator!= (const ofxExpr_<Type> &e2) const {
        return !(*this == e2);
    }
    
private:
    exprtk::symbol_table<Type> symbol_table;
    exprtk::expression<Type>   expression;
    exprtk::parser<Type>       parser;
    
    bool compiled = false;
    string expression_string = "";
    shared_ptr<Type> explicit_value = NULL;
};

typedef ofxExpr_<float> ofxExpr;
typedef ofxExpr_<double> ofxDoubleExpr;
