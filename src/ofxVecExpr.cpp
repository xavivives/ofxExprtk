#include "ofxVecExpr.hpp"

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr() : ofParameterGroup() {
    const std::string names[4] = {"x", "y", "z", "w"};
    for (int i=0; i<ofxVecExpr<VecType>::dim(); i++) {
        std::shared_ptr<ofxExpr<float>> e = std::make_shared<ofxExpr<float>>();
        e->setName(names[i]);
        add(*e);
        expr.push_back(e);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr(float value) : ofxVecExpr() {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->set(value);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr(VecType value) : ofxVecExpr() {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->set(value[i]);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr(const ofxVecExpr<VecType>& other) : ofParameterGroup() {
    setName(other.getName());
    for (int i=0; i<other.size(); i++) {
        expr.push_back(other[i]);
    }
}

template<typename VecType>
ofxVecExpr<VecType>& ofxVecExpr<VecType>::operator= (const ofxVecExpr<VecType>& other) {
    if (this != &other) {
        setName(other.getName());
        for (int i=0; i<other.size(); i++) {
            *expr[i] = *other[i];
        }
    }
    return *this;
}

template<typename VecType>
VecType ofxVecExpr<VecType>::getMin() const {
    VecType min;
    for (int i=0; i<expr.size(); i++) {
        min[i] = expr[i]->getMin();
    }
    return min;
}

template<typename VecType>
VecType ofxVecExpr<VecType>::getMax() const {
    VecType max;
    for (int i=0; i<expr.size(); i++) {
        max[i] = expr[i]->getMax();
    }
    return max;
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const std::string &value) {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->set(value);
    }
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const VecType & v) {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->set(v[i]);
    }
    return *this;
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const std::string& name, const VecType & v, const VecType & min, const VecType & max) {
    setName(name);
    for (int i=0; i<expr.size(); i++) {
        expr[i]->set(v[i], min[i], max[i]);
    }
    return *this;
}

template<typename VecType>
void ofxVecExpr<VecType>::setMin(const VecType & min) {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->setMin(min[i]);
    }
}

template<typename VecType>
void ofxVecExpr<VecType>::setMax(const VecType & max) {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->setMax(max[i]);
    }
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::setSliderMinMax(const VecType &min, const VecType &max) {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->setSliderMinMax(min[i], max[i]);
    }
    return *this;
}

template<typename VecType>
void ofxVecExpr<VecType>::setRandom() {
    set(ofRandom(getMin(), getMax()));
}

template<typename VecType>
std::shared_ptr<ofAbstractParameter> ofxVecExpr<VecType>::newReference() const{
    return std::make_shared<ofxVecExpr<VecType>>(*this);
}

template<typename VecType>
void ofxVecExpr<VecType>::makeReferenceTo(ofxVecExpr<VecType> & mom) {
    setName(mom.getName());
    for (int i=0; i<expr.size(); i++) {
        expr[i] = mom[i];
    }
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

template class ofxVecExpr<glm::vec2>;
template class ofxVecExpr<glm::vec3>;
template class ofxVecExpr<glm::vec4>;
