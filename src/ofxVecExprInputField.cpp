#include "ofxVecExprInputField.hpp"
#include "ofxExprInputField.hpp"

using namespace std;

template<class VecType>
ofxVecExprInputField<VecType>::ofxVecExprInputField(ofxVecExpr<VecType> value, float width, float height){
    setup(value, width, height);
}

template<class VecType>
ofxVecExprInputField<VecType> * ofxVecExprInputField<VecType>::setup(ofxVecExpr<VecType> &value, float width, float height){
    ofxGuiGroup::setup(value.getName(), "", 0, 0);
    
    parameters.clear();
    
    this->value.makeReferenceTo(value);
    
    for (size_t i = 0; i < value.dim(); i++) {
        ofxExpr p = *value[i];
        add(new ofxExprInputField(p, width, height));
    }
    
    return this;
    
}

template<class VecType>
ofxVecExprInputField<VecType> * ofxVecExprInputField<VecType>::setup(const std::string& controlName, const VecType & v, const VecType & min, const VecType & max, float width, float height){
    value.set(controlName,v,min,max);
    return setup(value,width,height);
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

template class ofxVecExprInputField<glm::vec2>;
template class ofxVecExprInputField<glm::vec3>;
template class ofxVecExprInputField<glm::vec4>;
