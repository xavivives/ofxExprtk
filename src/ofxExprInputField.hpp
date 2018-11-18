#pragma once

#include "ofxGuiGroup.h"
#include "ofxInputField.h"
#include "ofxExpr.hpp"

template<class Type>
class ofxExprInputField : public ofxGuiGroup {
    
public:
    ofxExprInputField() {}
    ofxExprInputField(ofxExpr<Type> _val, float width = defaultWidth, float height = defaultHeight);
    
    ofxExprInputField<Type> * setup(ofxExpr<Type> &value, float width = defaultWidth, float height = defaultHeight);
    ofxExprInputField<Type> * setup(const std::string& controlName, const Type & value, const Type & min, const Type & max, float width = defaultWidth, float height = defaultHeight);
    
    void clear();
    void minimize() {}
    void maximize() {}
    virtual bool mouseMoved(ofMouseEventArgs & args);
    virtual bool mousePressed(ofMouseEventArgs & args);
    virtual bool mouseDragged(ofMouseEventArgs & args);
    virtual bool mouseReleased(ofMouseEventArgs & args);
    virtual bool mouseScrolled(ofMouseEventArgs & args);
    void render();
    void sizeChangedCB();
    
protected:
    void changeSlider(const void * parameter, float & value);
    void changeInputField(const void * parameter, std::string & value);
    void changeToggle(const void * parameter, bool & value);
    
    ofxExpr<Type> value;
    ofxTextField * textField = NULL;
    ofxSlider<Type> * slider = NULL;
    
};
