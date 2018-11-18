#pragma once

#include "ofxInputField.h"
#include "ofxExpr.hpp"

template<class Type>
class ofxExprInputField : public ofxTextField {
    
public:
    ofxExprInputField() : ofxTextField() {}
    ofxExprInputField(ofxExpr<Type> _val, float width = defaultWidth, float height = defaultHeight) : ofxTextField(_val.get_str_expr(), width, height), expr(_val) {}
    
protected:
    void parseInput();
    
    ofxExpr<Type> expr;
    
};
