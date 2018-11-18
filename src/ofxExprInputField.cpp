#include "ofxExprInputField.hpp"

template<class Type>
ofxExprInputField<Type>::ofxExprInputField(ofxExpr<Type> value, float width, float height){
    setup(value, width, height);
}

template<class Type>
ofxExprInputField<Type> * ofxExprInputField<Type>::setup(ofxExpr<Type> &value, float width, float height){
    ofxGuiGroup::setup(value.getName(), "", 0, 0);
    
    clear();
    
    this->value.makeReferenceTo(value);
    
    ofParameter<std::string> pExpr = *(value.getExpressionParameter());
    pExpr.setName(value.getName() + "E");
    ofParameter<Type> pValue = *(value.getValueParameter());
    pValue.setName(value.getName() + "V");
    
    textField = new ofxTextField(pExpr, width, height);
    add(textField);
    pExpr.addListener(this, & ofxExprInputField::changeInputField);
    
    b.height -= textField->getHeight() + spacing;
    
    slider = new ofxSlider<Type>(pValue, width, height);
    add(slider);
    pValue.addListener(this, & ofxExprInputField::changeSlider);
    
    return this;
    
}

template<class Type>
ofxExprInputField<Type> * ofxExprInputField<Type>::setup(const std::string& controlName, const Type & v, const Type & min, const Type & max, float width, float height){
    value.set(controlName,v,min,max);
    return setup(value,width,height);
}

template<class Type>
void ofxExprInputField<Type>::changeSlider(const void * parameter, float & _value){
    value.set(_value);
}

template<class Type>
void ofxExprInputField<Type>::changeInputField(const void * parameter, std::string & _value){
    value.set(_value);
}

template<class Type>
void ofxExprInputField<Type>::changeToggle(const void * parameter, bool & _value){
    value.set(_value);
}

template<class Type>
void ofxExprInputField<Type>::clear(){
    collection.clear();
    parameters.clear();
    b.height = 0;
    sizeChangedCB();
}

template<class Type>
bool ofxExprInputField<Type>::mouseMoved(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mouseMoved(args);
    }
    else {
        return textField->mouseMoved(args);
    }
}

template<class Type>
bool ofxExprInputField<Type>::mousePressed(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mousePressed(args);
    }
    else {
        return textField->mousePressed(args);
    }
}

template<class Type>
bool ofxExprInputField<Type>::mouseDragged(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mouseDragged(args);
    }
    else {
        return textField->mouseDragged(args);
    }
}

template<class Type>
bool ofxExprInputField<Type>::mouseReleased(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mouseReleased(args);
    }
    else {
        return textField->mouseReleased(args);
    }
}

template<class Type>
bool ofxExprInputField<Type>::mouseScrolled(ofMouseEventArgs & args){
    if (value.isExplicit()) {
        return slider->mouseScrolled(args);
    }
    else {
        return textField->mouseScrolled(args);
    }
}


template<class Type>
void ofxExprInputField<Type>::render(){
    ofBlendMode blendMode = ofGetStyle().blendingMode;
    if(blendMode != OF_BLENDMODE_ALPHA){
        ofEnableAlphaBlending();
    }
    ofColor c = ofGetStyle().color;
    ofSetColor(thisTextColor);

    if (value.isExplicit()) {
        slider->draw();
    }
    else {
        textField->draw();
    }
    
    ofSetColor(c);
    if(blendMode != OF_BLENDMODE_ALPHA){
        ofEnableBlendMode(blendMode);
    }
}

template<class Type>
void ofxExprInputField<Type>::sizeChangedCB(){
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

template class ofxExprInputField<float>;
