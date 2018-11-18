#pragma once

#include "ofxExpr.hpp"

template<class VecType>
class ofxVecExpr : public ofParameter<VecType> {
    
public:
    ofxVecExpr();
    ofxVecExpr(float value);
    ofxVecExpr(VecType value);
    ofxVecExpr(const ofxVecExpr<VecType> &other);
    ofxVecExpr<VecType>& operator= (const ofxVecExpr<VecType>& other);
    
    ofxVecExpr<VecType> & set(const VecType & v);
    ofxVecExpr<VecType> & set(const std::string& name, const VecType & v, const VecType & min, const VecType & max);
    void setMin(const VecType & min);
    void setMax(const VecType & max);
    
    void set_expr(const string &value) {
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
    
    const ofxExpr<float>& operator [] (const int i) const {
        return expr[i];
    }
    
    ofxExpr<float>& operator [] (const int i) {
        return expr[i];
    }
    
    friend bool operator== (const ofxVecExpr<VecType> &c1, const ofxVecExpr<VecType> &c2) {
        bool result = true;
        for (int i=0; i<ofxVecExpr<VecType>::dim(); i++) {
            result = result && (c1[i] == c2[i]);
        }
        return result;
    }
    friend bool operator!= (const ofxVecExpr<VecType> &c1, const ofxVecExpr<VecType> &c2) {
        return !(c1 == c2);
    }
    
    shared_ptr<ofAbstractParameter> newReference() const;
    static size_t dim();
    
private:
    vector<ofxExpr<float>> expr;
    
};
