#pragma once

#include "ofxGuiGroup.h"
#include "ofxVecExpr.hpp"

template<class VecType>
class ofxVecExprInputField : public ofxGuiGroup {
public:
    ofxVecExprInputField() {};
    ofxVecExprInputField(ofxVecExpr<VecType> value, float width = defaultWidth, float height = defaultHeight);
    
    ofxVecExprInputField<VecType> * setup(ofxVecExpr<VecType> &value, float width = defaultWidth, float height = defaultHeight);
    ofxVecExprInputField<VecType> * setup(const std::string& controlName, const VecType & value, const VecType & min, const VecType & max, float width = defaultWidth, float height = defaultHeight);
    
    ofAbstractParameter & getParameter();
    
    ofxVecExpr<VecType> operator=(const ofxVecExpr<VecType> & v);
    operator const ofxVecExpr<VecType> & ();
protected:
    void changeSlider(const void * parameter, float & value);
    void changeInputField(const void * parameter, std::string & value);
    ofxVecExpr<VecType> value;
};
