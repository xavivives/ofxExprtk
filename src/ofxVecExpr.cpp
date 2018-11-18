#include "ofxVecExpr.hpp"

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr() : ofParameter<VecType>() {
    const string names[4] = {"x", "y", "z", "w"};
    for (int i=0; i<ofxVecExpr<VecType>::dim(); i++) {
        ofxExpr<float> e;
        e.setName(names[i]);
        expr.push_back(e);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr(float value) : ofxVecExpr() {
    for (int i=0; i<expr.size(); i++) {
        expr[i].set(value);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr(VecType value) : ofxVecExpr() {
    for (int i=0; i<expr.size(); i++) {
        expr[i].set(value[i]);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr (const ofxVecExpr<VecType>& other) : ofxVecExpr() {
    *this = other;
}

template<typename VecType>
ofxVecExpr<VecType>& ofxVecExpr<VecType>::operator= (const ofxVecExpr<VecType>& other) {
    if (this != &other) {
        for (int i=0; i<ofxVecExpr<VecType>::dim(); i++) {
            expr[i].set_expr(other[i].get_expr());
            if (other[i].is_explicit_value()) {
                expr[i].set(other[i].get());
            }
        }
        ofParameter<VecType>::set(other.get());
        ofParameter<VecType>::setName(other.getName());
        setMin(other.getMin());
        setMax(other.getMax());
    }
    return *this;
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const VecType & v) {
    ofParameter<VecType>::set(v);
    return *this;
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const std::string& name, const VecType & v, const VecType & min, const VecType & max) {
    ofParameter<VecType>::set(name, v, min, max);
    return *this;
}

template<typename VecType>
void ofxVecExpr<VecType>::setMin(const VecType & min) {
    ofParameter<VecType>::setMin(min);
    for (int i=0; i<expr.size(); i++) {
        expr[i].setMin(min[i]);
    }
}

template<typename VecType>
void ofxVecExpr<VecType>::setMax(const VecType & max) {
    ofParameter<VecType>::setMax(max);
    for (int i=0; i<expr.size(); i++) {
        expr[i].setMax(max[i]);
    }
}

template<typename VecType>
std::shared_ptr<ofAbstractParameter> ofxVecExpr<VecType>::newReference() const{
    return std::make_shared<ofxVecExpr<VecType>>(*this);
}

template<>
size_t ofxVecExpr<glm::vec2>::dim(){
    return 2;
}

template<>
size_t ofxVecExpr<glm::vec3>::dim(){
    return 3;
}

template<>
size_t ofxVecExpr<glm::vec4>::dim(){
    return 4;
}

template<>
size_t ofxVecExpr<ofVec2f>::dim(){
    return 2;
}

template<>
size_t ofxVecExpr<ofVec3f>::dim(){
    return 3;
}

template<>
size_t ofxVecExpr<ofVec4f>::dim(){
    return 4;
}

template class ofxVecExpr<ofVec2f>;
template class ofxVecExpr<ofVec3f>;
template class ofxVecExpr<ofVec4f>;
template class ofxVecExpr<glm::vec2>;
template class ofxVecExpr<glm::vec3>;
template class ofxVecExpr<glm::vec4>;
