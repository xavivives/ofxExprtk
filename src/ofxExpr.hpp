#pragma once

#include "exprtk.hpp"
#include "ofParameter.h"

template<class Type>
class ofxExpr : public ofParameterGroup {
    
public:
    static const std::string NAME_EXPR;
    static const std::string NAME_VALUE;
    static const std::string NAME_EXPLICIT;
    
    ofxExpr();
    ofxExpr(const std::string &name, const std::string &expression, const Type &value, const Type &min, const Type &max, bool isExplicit = false);
    ofxExpr(const std::string &name, const std::string &expression, const Type &value, bool isExplicit = false);
    ofxExpr(const std::string &name, const std::string &expr);
    ofxExpr(const std::string &name, const Type &value, bool isExplicit = true);
    ofxExpr(const std::string &name, const Type &value, const Type &min, const Type &max, bool isExplicit = true);
    ofxExpr(const ofxExpr<Type>& other);
    ofxExpr<Type>& operator= (const ofxExpr<Type>& other);
    
    Type get() const {
        if (isExplicit()) {
            return getValue();
        }
        return expression.value();
    }
    const std::string & getExpression() const {
        return pExpr->get();
    }
    const Type & getValue() const {
        return pValue->get();
    }
    Type getMin() const {
        return pValue->getMin();
    }
    Type getMax() const {
        return pValue->getMax();
    }
    const bool isExplicit() const {
        return pExplicit->get();
    }
    
    ofxExpr<Type> & set(const std::string &expression);
    ofxExpr<Type> & set(const Type &value, bool isExplicit = true);
    ofxExpr<Type> & set(const Type &value, const Type &min, const Type &max, bool isExplicit = true);
    ofxExpr<Type> & set(const std::string &name, const Type &value, bool isExplicit = true);
    ofxExpr<Type> & set(const std::string &name, const Type &value, const Type &min, const Type &max, bool isExplicit = true);
    ofxExpr<Type> & set(const std::string & name, const std::string &expression, const Type &value, const Type &min, const Type &max, bool isExplicit = false);
    ofxExpr<Type> & set(bool isExplicit);
    void setMin(const Type &min) {
        pValue->setMin(min);
    }
    void setMax(const Type &max) {
        pValue->setMax(max);
    }
    ofxExpr<Type> & setSliderMinMax(const Type &min, const Type &max) {
        pValue->setSliderMinMax(min, max);
        return *this;
    }
    void setRandom() {
        set(ofRandom(getMin(), getMax()));
    }
    
    bool add_var(const std::string &name, Type &value) {
        compiled = false;
        return symbol_table.add_variable(name, value);
    }
    bool add_const(const std::string &name, const Type &value) {
        compiled = false;
        return symbol_table.add_constant(name, value);
    }
    bool add_stringvar(const std::string &name, std::string &value) {
        compiled = false;
        return symbol_table.add_stringvar(name, value);
    }
    template<typename VecType>
    bool add_vector(const std::string &name, std::vector<VecType> &value) {
        compiled = false;
        return symbol_table.add_vector(name, value);
    }
    bool compile() {
        if (!compiled) {
            expression.register_symbol_table(symbol_table);
            compiled = parser.compile(pExpr->get(), expression);
        }
        return compiled;
    }
    const std::shared_ptr<ofParameter<std::string>> & getExpressionParameter() const {
        return pExpr;
    }
    const std::shared_ptr<ofParameter<Type>> & getValueParameter() const {
        return pValue;
    }
    const std::shared_ptr<ofParameter<bool>> & getExplicitParameter() const {
        return pExplicit;
    }

    template<typename ParameterType>
    const ofParameter<ParameterType> & get(const std::string& name) const {
        return ofParameterGroup::get<ParameterType>(name);
    }
    template<typename ParameterType>
    ofParameter<ParameterType> & get(const std::string& name) {
        return ofParameterGroup::get<ParameterType>(name);
    }
    
    bool operator== (const ofxExpr<Type> &e2) const;
    bool operator!= (const ofxExpr<Type> &e2) const;
    std::shared_ptr<ofAbstractParameter> newReference() const;
    void makeReferenceTo(ofxExpr<Type> & mom);
    
private:
    exprtk::symbol_table<Type> symbol_table;
    exprtk::expression<Type>   expression;
    exprtk::parser<Type>       parser;
    
    bool compiled = false;
    std::shared_ptr<ofParameter<std::string>> pExpr;
    std::shared_ptr<ofParameter<Type>> pValue;
    std::shared_ptr<ofParameter<bool>> pExplicit;
};
