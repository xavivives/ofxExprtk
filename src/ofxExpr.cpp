#include "ofxExpr.hpp"

template<typename Type>
const std::string ofxExpr<Type>::NAME_EXPR = "expression";

template<typename Type>
const std::string ofxExpr<Type>::NAME_VALUE = "value";

template<typename Type>
const std::string ofxExpr<Type>::NAME_EXPLICIT = "explicit";

template<typename Type>
ofxExpr<Type>::ofxExpr() : ofParameterGroup() {
    pExpr = std::make_shared<ofParameter<std::string>>();
    pExpr->setName(NAME_EXPR);
    add(*pExpr);
    pValue = std::make_shared<ofParameter<Type>>();
    pValue->setName(NAME_VALUE);
    add(*pValue);
    pExplicit = std::make_shared<ofParameter<bool>>();
    pExplicit->setName(NAME_EXPLICIT);
    add(*pExplicit);
}

template<typename Type>
ofxExpr<Type>::ofxExpr(const std::string &name, const std::string &expression, const Type &value, bool isExplicit) : ofxExpr() {
    set(expression);
    set(name, value, isExplicit);
}

template<typename Type>
ofxExpr<Type>::ofxExpr(const std::string &name, const std::string &expr) : ofxExpr() {
    setName(name);
    set(expr);
}

template<typename Type>
ofxExpr<Type>::ofxExpr(const std::string &name, const Type &value, bool isExplicit) : ofxExpr() {
    set(value, isExplicit);
}

template<typename Type>
ofxExpr<Type>::ofxExpr(const std::string &name, const Type &value, const Type &min, const Type &max, bool isExplicit) : ofxExpr(name, "", value, min, max, isExplicit) {}

template<typename Type>
ofxExpr<Type>::ofxExpr(const ofxExpr<Type>& other) : ofParameterGroup() {
    setName(other.getName());
    pExpr = other.getExpressionParameter();
    pValue = other.getValueParameter();
    pExplicit = other.getExplicitParameter();
}

template<typename Type>
ofxExpr<Type>& ofxExpr<Type>::operator= (const ofxExpr<Type>& other) {
    if (this != &other) {
        setName(other.getName());
        set(other.getExpression());
        set(other.getName(), other.getValue(), other.getMin(), other.getMax(), other.isExplicit());
    }
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const std::string &expression) {
    pExpr->set(expression);
    pExplicit->set(false);
    compiled = false;
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const Type &value, bool isExplicit) {
    pValue->set(value);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const Type &value, const Type &min, const Type &max, bool isExplicit) {
    pValue->set(NAME_VALUE, value, min, max);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const std::string &name, const Type &value, bool isExplicit) {
    setName(name);
    pValue->set(value);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const std::string &name, const Type &value, const Type &min, const Type &max, bool isExplicit) {
    setName(name);
    pValue->set(NAME_VALUE, value, min, max);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const std::string &name, const std::string &expression, const Type &value, const Type &min, const Type &max, bool isExplicit) {
    setName(name);
    pExpr->set(expression);
    pValue->set(NAME_VALUE, value, min, max);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(bool isExplicit) {
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
bool ofxExpr<Type>::operator== (const ofxExpr<Type> &e2) const {
    std::string v1 = isExplicit() ? ofToString(getValue()) : pExpr->get();
    std::string v2 = e2.isExplicit() ? ofToString(e2.getValue()) : e2.getExpression();
    return v1 == v2;
}

template<typename Type>
bool ofxExpr<Type>::operator!= (const ofxExpr<Type> &e2) const {
    return !(*this == e2);
}

template<typename Type>
std::shared_ptr<ofAbstractParameter> ofxExpr<Type>::newReference() const{
    return std::make_shared<ofxExpr<Type>>(*this);
}

template<typename Type>
void ofxExpr<Type>::makeReferenceTo(ofxExpr<Type> & mom) {
    pExpr = mom.getExpressionParameter();
    pValue = mom.getValueParameter();
    pExplicit = mom.getExplicitParameter();
}

template class ofxExpr<float>;
template class ofxExpr<double>;
