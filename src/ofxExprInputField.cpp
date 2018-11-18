#include "ofxExprInputField.hpp"

ofxExprInputField::ofxExprInputField(ofxExpr value, float width, float height){
    setup(value, width, height);
}

ofxExprInputField * ofxExprInputField::setup(ofxExpr &value, float width, float height){
    ofxGuiGroup::setup(value.getName(), "", 0, 0);
    
    clear();
    
    this->value.makeReferenceTo(value);
    
    ofParameter<std::string> pExpr = *(value.getExpressionParameter());
    pExpr.setName(value.getName() + "E");
    ofParameter<float> pValue = *(value.getValueParameter());
    pValue.setName(value.getName() + "V");
    
    textField = new ofxTextField(pExpr, width, height);
    add(textField);
    pExpr.addListener(this, & ofxExprInputField::changeInputField);
    
    b.height -= textField->getHeight() + spacing;
    
    slider = new ofxSlider<float>(pValue, width, height);
    add(slider);
    pValue.addListener(this, & ofxExprInputField::changeSlider);
    
    return this;
    
}

ofxExprInputField * ofxExprInputField::setup(const std::string& controlName, const float & v, const float & min, const float & max, float width, float height){
    value.set(controlName,v,min,max);
    return setup(value,width,height);
}

void ofxExprInputField::changeSlider(const void * parameter, float & _value){
    value.set(_value);
}

void ofxExprInputField::changeInputField(const void * parameter, std::string & _value){
    value.set(_value);
}

void ofxExprInputField::changeToggle(const void * parameter, bool & _value){
    value.set(_value);
}

void ofxExprInputField::clear(){
    collection.clear();
    parameters.clear();
    b.height = 0;
    sizeChangedCB();
}

bool ofxExprInputField::mouseMoved(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mouseMoved(args);
    }
    else {
        return textField->mouseMoved(args);
    }
}

bool ofxExprInputField::mousePressed(ofMouseEventArgs & mouse){
    if(mouse.button == OF_MOUSE_BUTTON_RIGHT){
        if(b.inside(mouse)){
            value.setExplicit(!value.isExplicit());
            return true;
        }else{
            return false;
        }
    }else{
        if (value.isExplicit()) {
            return slider->mousePressed(mouse);
        }
        else {
            return textField->mousePressed(mouse);
        }
    }
}

bool ofxExprInputField::mouseDragged(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mouseDragged(args);
    }
    else {
        return textField->mouseDragged(args);
    }
}

bool ofxExprInputField::mouseReleased(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mouseReleased(args);
    }
    else {
        return textField->mouseReleased(args);
    }
}

bool ofxExprInputField::mouseScrolled(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mouseScrolled(args);
    }
    else {
        return textField->mouseScrolled(args);
    }
}

void ofxExprInputField::generateDraw(){
    textMesh = getTextMesh("!", textPadding + b.x, 4 + b.y + spacingNextElement);
}

void ofxExprInputField::render(){
    ofBlendMode blendMode = ofGetStyle().blendingMode;
    if(blendMode != OF_BLENDMODE_ALPHA){
        ofEnableAlphaBlending();
    }

    if (value.isExplicit()) {
        slider->draw();
    }
    else {
        textField->draw();
        
        if (value.hasError()) {
            ofColor c = ofGetStyle().color;
            ofSetColor(ofColor::red);

            bindFontTexture();
            textMesh.draw();
            unbindFontTexture();
            
            ofSetColor(c);
        }
    }
    
    if(blendMode != OF_BLENDMODE_ALPHA){
        ofEnableBlendMode(blendMode);
    }
}

void ofxExprInputField::sizeChangedCB(){
    for(std::size_t i = 0; i < collection.size(); i++){
        collection[i]->setPosition(collection[i]->getPosition().x, b.y);
    }
    if (value.isExplicit()) {
        b.height = slider != NULL ? slider->getHeight() + spacing : 0;
    }
    else {
        b.height = textField != NULL ? textField->getHeight() + spacing : 0;
    }
    if(parent){
        parent->sizeChangedCB();
    }
    setNeedsRedraw();
}
