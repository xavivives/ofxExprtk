#include "ofxVecExprInputField.hpp"
#include "ofxExprInputField.hpp"

using namespace std;

template<class VecType>
ofxVecExprInputField<VecType>::ofxVecExprInputField(ofxVecExpr<VecType> value, float width, float height){
    sliderChanging = false;
    setup(value, width, height);
}

template<class VecType>
ofxVecExprInputField<VecType> * ofxVecExprInputField<VecType>::setup(ofxVecExpr<VecType> &value, float width, float height){
    ofxGuiGroup::setup(value.getName(), "", 0, 0);
    
    parameters.clear();
    
    this->value.makeReferenceTo(value);
    this->value.addListener(this, & ofxVecExprInputField::changeValue);
    
    ofxVecExpr<VecType> val = value;
    
    for (size_t i = 0; i < val.dim(); i++) {
        ofxExpr<float> p = val[i];
        add(new ofxExprInputField<float>(p, width, height));
        p.addListener(this, & ofxVecExprInputField::changeSlider);
        p.get_str_expr().addListener(this, & ofxVecExprInputField::changeInputField);
    }
    
    sliderChanging = false;
    return this;
    
}

template<class VecType>
ofxVecExprInputField<VecType> * ofxVecExprInputField<VecType>::setup(const std::string& controlName, const ofxVecExpr<VecType> & v, const ofxVecExpr<VecType> & min, const ofxVecExpr<VecType> & max, float width, float height){
    value.set(controlName,v,min,max);
    return setup(value,width,height);
}

template<class VecType>
void ofxVecExprInputField<VecType>::changeSlider(const void * parameter, float & _value){
    sliderChanging = true;
    ofxExpr<float> & param = *(ofxExpr<float>*)parameter;
    int i = parameters.getPosition(param.getName());
    ofxVecExpr<VecType> data = value;
    data[i] = _value;
    value = data;
    sliderChanging = false;
}

template<class VecType>
void ofxVecExprInputField<VecType>::changeInputField(const void * parameter, string & _value){
    sliderChanging = true;
    ofxExpr<float> & param = *(ofxExpr<float>*)parameter;
    int i = parameters.getPosition(param.getName());
    value[i].set_expr(_value);
    sliderChanging = false;
}

template<class VecType>
void ofxVecExprInputField<VecType>::changeValue(VecType & value){
    if (sliderChanging){
        return;
    }
    for (size_t i = 0; i < ofxVecExpr<VecType>::dim(); i++){
        parameters[i].template cast<ofxExpr<float>>() = value[i];
    }
}

template<class VecType>
ofAbstractParameter & ofxVecExprInputField<VecType>::getParameter(){
    return value;
}

template<class VecType>
ofxVecExpr<VecType> ofxVecExprInputField<VecType>::operator=(const ofxVecExpr<VecType> & v){
    value = v;
    return value;
}

template<class VecType>
ofxVecExprInputField<VecType>::operator const ofxVecExpr<VecType> & (){
    return value;
}

template<class VecType>
const VecType * ofxVecExprInputField<VecType>::operator->(){
    return &value.get();
}

template class ofxVecExprInputField<glm::vec2>;
template class ofxVecExprInputField<glm::vec3>;
template class ofxVecExprInputField<glm::vec4>;
