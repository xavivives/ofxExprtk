#pragma once

#ifndef PrefixHeader_pch
#include "ofxGuiGroup.h"
#include "ofxInputField.h"
#endif

#include "ofxExpr.hpp"

class ofxExprInputField : public ofxGuiGroup {
    
public:
    ofxExprInputField() {}
    ofxExprInputField(ofxExpr _val, float width = defaultWidth, float height = defaultHeight);
    
    ofxExprInputField * setup(ofxExpr &value, float width = defaultWidth, float height = defaultHeight);
    ofxExprInputField * setup(const std::string& controlName, const float & value, const float & min, const float & max, float width = defaultWidth, float height = defaultHeight);
    
    void clear();
    void minimize() {}
    void maximize() {}
    virtual bool mouseMoved(ofMouseEventArgs & args);
    virtual bool mousePressed(ofMouseEventArgs & args);
    virtual bool mouseDragged(ofMouseEventArgs & args);
    virtual bool mouseReleased(ofMouseEventArgs & args);
    virtual bool mouseScrolled(ofMouseEventArgs & args);
    void generateDraw();
    void render();
    void sizeChangedCB();
    
protected:
    void changeSlider(const void * parameter, float & value);
    void changeInputField(const void * parameter, std::string & value);
    void changeToggle(const void * parameter, bool & value);
    
    ofxExpr value;
    ofxTextField * textField = NULL;
    ofxSlider<float> * slider = NULL;
    
    ofVboMesh textMesh;
    
};
