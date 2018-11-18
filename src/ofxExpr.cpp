#include "ofxExpr.hpp"

template<typename Type>
ofxExpr<Type>::ofxExpr() : ofParameter<Type>() {}

template<typename Type>
ofxExpr<Type>::ofxExpr(const string &expr) : ofParameter<Type>() {
    set_expr(expr);
}

template<typename Type>
ofxExpr<Type>::ofxExpr(const Type &value) : ofParameter<Type>(value) {
    use_explicit_value = true;
}

template<typename Type>
ofxExpr<Type>::ofxExpr(const string &name, const Type &value, const Type &min, const Type &max) : ofParameter<Type>(name, value, min, max) {
    use_explicit_value = true;
}

template<typename Type>
ofxExpr<Type>::ofxExpr(const ofxExpr<Type>& other) : ofParameter<Type>() {
    *this = other;
}

template<typename Type>
ofxExpr<Type>& ofxExpr<Type>::operator= (const ofxExpr<Type>& other) {
    if (this != &other) {
        set_expr(other.get_expr());
        set(other.get());
        use_explicit_value = other.is_explicit_value();
        ofParameter<Type>::setName(other.getName());
        ofParameter<Type>::setMin(other.getMin());
        ofParameter<Type>::setMax(other.getMax());
    }
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const Type &value) {
    use_explicit_value = true;
    ofParameter<Type>::set(value);
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const string &name, const Type &value) {
    use_explicit_value = true;
    ofParameter<Type>::set(name, value);
    return *this;
}

template<typename Type>
ofxExpr<Type> & ofxExpr<Type>::set(const string &name, const Type &value, const Type &min, const Type &max) {
    use_explicit_value = true;
    ofParameter<Type>::set(name, value, min, max);
    return *this;
}

template<typename Type>
void ofxExpr<Type>::setName(const std::string & name) {
    ofParameter<Type>::setName(name);
    str_expr.setName(name);
}

template<typename Type>
bool ofxExpr<Type>::operator== (const ofxExpr<Type> &e2) const {
    string v1 = is_explicit_value() ? ofToString(this->get()) : str_expr.get();
    string v2 = e2.is_explicit_value() ? ofToString(e2.get()) : e2.get_expr();
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

template class ofxExpr<float>;
template class ofxExpr<double>;
