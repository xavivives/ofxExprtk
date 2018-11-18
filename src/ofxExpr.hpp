#pragma once

#ifndef PrefixHeader_pch
#include "exprtk.hpp"
#endif

#include "ofParameter.h"

class ofxExpr : public ofParameterGroup {
    
public:
    static const std::string NAME_EXPR;
    static const std::string NAME_VALUE;
    static const std::string NAME_EXPLICIT;
    
    ofxExpr();
    ofxExpr(const std::string &name, const std::string &expression, const float &value, const float &min, const float &max, bool isExplicit = false);
    ofxExpr(const std::string &name, const std::string &expression, const float &value, bool isExplicit = false);
    ofxExpr(const std::string &name, const std::string &expr);
    ofxExpr(const std::string &name, const float &value, bool isExplicit = true);
    ofxExpr(const std::string &name, const float &value, const float &min, const float &max, bool isExplicit = true);
    ofxExpr(const ofxExpr& other);
    ofxExpr& operator= (const ofxExpr& other);
    
    float get() const {
        if (isExplicit()) {
            return getValue();
        }
        float val = expression.value();
        return std::isnan(val) ? 0 : val;
    }
    const std::string & getExpression() const {
        return pExpr->get();
    }
    const float & getValue() const {
        return pValue->get();
    }
    float getMin() const {
        return pValue->getMin();
    }
    float getMax() const {
        return pValue->getMax();
    }
    const bool isExplicit() const {
        return pExplicit->get();
    }
    const bool hasError() const {
        return !compiled;
    }
    
    ofxExpr & set(const std::string &expression);
    ofxExpr & set(const float &value, bool isExplicit = true);
    ofxExpr & set(const float &value, const float &min, const float &max, bool isExplicit = true);
    ofxExpr & set(const std::string &name, const float &value, bool isExplicit = true);
    ofxExpr & set(const std::string &name, const float &value, const float &min, const float &max, bool isExplicit = true);
    ofxExpr & set(const std::string & name, const std::string &expression, const float &value, const float &min, const float &max, bool isExplicit = false);
    ofxExpr & setExplicit(bool isExplicit);
    void setMin(const float &min) {
        pValue->setMin(min);
    }
    void setMax(const float &max) {
        pValue->setMax(max);
    }
    ofxExpr & setSliderMinMax(const float &min, const float &max) {
        pValue->setSliderMinMax(min, max);
        return *this;
    }
    void setRandom() {
        set(ofRandom(getMin(), getMax()));
    }
    
    bool addVar(const std::string &name, float &value, bool recompile = true) {
        bool result = symbol_table.add_variable(name, value);
        if (result && recompile) compile();
        return result;
    }
    bool addConst(const std::string &name, const float &value, bool recompile = true) {
        bool result = symbol_table.add_constant(name, value);
        if (result && recompile) compile();
        return result;
    }
    bool addStringvar(const std::string &name, std::string &value, bool recompile = true) {
        bool result = symbol_table.add_stringvar(name, value);
        if (result && recompile) compile();
        return result;
    }
    template<typename VecType>
    bool addVector(const std::string &name, std::vector<VecType> &value, bool recompile = true) {
        bool result = symbol_table.add_vector(name, value);
        if (result && recompile) compile();
        return result;
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
    const std::shared_ptr<ofParameter<float>> & getValueParameter() const {
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
    
    bool operator== (const ofxExpr &e2) const;
    bool operator!= (const ofxExpr &e2) const;
    std::shared_ptr<ofAbstractParameter> newReference() const;
    void makeReferenceTo(ofxExpr & mom);
    
private:
    exprtk::symbol_table<float> symbol_table;
    exprtk::expression<float>   expression;
    exprtk::parser<float>       parser;
    
    bool compiled = false;
    std::shared_ptr<ofParameter<std::string>> pExpr;
    std::shared_ptr<ofParameter<float>> pValue;
    std::shared_ptr<ofParameter<bool>> pExplicit;
};
