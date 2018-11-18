#pragma once

#include "ofxGuiGroup.h"
#include "ofxVecExpr.hpp"

template<class VecType>
class ofxVecExprInputField : public ofxGuiGroup {
public:
    ofxVecExprInputField(){
        sliderChanging = false;
    };
    ofxVecExprInputField(ofxVecExpr<VecType> value, float width = defaultWidth, float height = defaultHeight);
    
    ofxVecExprInputField<VecType> * setup(ofxVecExpr<VecType> &value, float width = defaultWidth, float height = defaultHeight);
    ofxVecExprInputField<VecType> * setup(const std::string& controlName, const ofxVecExpr<VecType> & value, const ofxVecExpr<VecType> & min, const ofxVecExpr<VecType> & max, float width = defaultWidth, float height = defaultHeight);
    
    ofAbstractParameter & getParameter();
    
    ofxVecExpr<VecType> operator=(const ofxVecExpr<VecType> & v);
    operator const ofxVecExpr<VecType> & ();
    const VecType * operator->();
protected:
    void changeSlider(const void * parameter, float & value);
    void changeInputField(const void * parameter, string & value);
    void changeValue(VecType & value);
    static size_t dim();
    ofxVecExpr<VecType> value;
    bool sliderChanging;
};
