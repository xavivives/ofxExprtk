#pragma once

#include "ofxExpr.hpp"
#include "ofxSliderGroup.h"

template<class VecType>
class ofxVecExpr_ {
    
public:
    ofxVecExpr_() {
        expr.resize(ofxVecSlider_<VecType>::dim());
    }
    ofxVecExpr_(float value) {
        expr.resize(ofxVecSlider_<VecType>::dim());
        for (int i=0; i<expr.size(); i++) {
            expr[i].set_explicit_value(value);
        }
    }
    ofxVecExpr_(VecType value) {
        expr.resize(ofxVecSlider_<VecType>::dim());
        for (int i=0; i<expr.size(); i++) {
            expr[i].set_explicit_value(value[i]);
        }
    }
    void set(const string &value) {
        for (int i=0; i<expr.size(); i++) {
            expr[i].set_expr(value);
        }
    }
    bool add_var(const string &name, float &value) {
        for (int i=0; i<expr.size(); i++) {
            expr[i].add_var(name, value);
        }
    }
    bool add_const(const string &name, const float &value) {
        for (int i=0; i<expr.size(); i++) {
            expr[i].add_const(name, value);
        }
    }
    bool add_stringvar(const string &name, string &value) {
        for (int i=0; i<expr.size(); i++) {
            expr[i].add_stringvar(name, value);
        }
    }
    template<typename VecType1>
    bool add_vector(const string &name, vector<VecType1> &value) {
        for (int i=0; i<expr.size(); i++) {
            expr[i].add_vector(name, value);
        }
    }
    bool compile() {
        for (int i=0; i<expr.size(); i++) {
            expr[i].compile();
        }
    }
    VecType value() const {
        VecType val;
        for (int i=0; i<expr.size(); i++) {
            val[i] = expr[i].value();
        }
        return val;
    }
    bool is_set() const {
        bool result = false;
        for (int i=0; i<expr.size(); i++) {
            result = result || expr[i].is_set();
        }
        return result;
    }
    
    float x() const {
        return expr[0].value();
    }
    
    float y() const {
        return expr[1].value();
    }
    
    float z() const {
        return expr[2].value();
    }
    
    float w() const {
        return expr[3].value();
    }
    
    const ofxExpr& operator [] (const int i) const {
        return expr[i];
    }
    
    friend bool operator== (const ofxVecExpr_<VecType> &c1, const ofxVecExpr_<VecType> &c2) {
        bool result = true;
        for (int i=0; i<ofxVecSlider_<VecType>::dim(); i++) {
            result = result && (c1[i] == c2[i]);
        }
        return result;
    }
    friend bool operator!= (const ofxVecExpr_<VecType> &c1, const ofxVecExpr_<VecType> &c2) {
        return !(c1 == c2);
    }
    
private:
    vector<ofxExpr> expr;
    
};

typedef ofxVecExpr_<glm::vec2> ofxVec2Expr;
typedef ofxVecExpr_<glm::vec3> ofxVec3Expr;
typedef ofxVecExpr_<glm::vec4> ofxVec4Expr;
