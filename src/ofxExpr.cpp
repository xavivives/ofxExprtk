#include "ofxExpr.hpp"

const std::string ofxExpr::NAME_EXPR = "expression";

const std::string ofxExpr::NAME_VALUE = "value";

const std::string ofxExpr::NAME_EXPLICIT = "explicit";

ofxExpr::ofxExpr() : ofParameterGroup() {
    pExpr = std::make_shared<ofParameter<std::string>>(NAME_EXPR, "");
    add(*pExpr);
    pValue = std::make_shared<ofParameter<float>>(NAME_VALUE, 0.f);
    add(*pValue);
    pExplicit = std::make_shared<ofParameter<bool>>(NAME_EXPLICIT, false);
    add(*pExplicit);
}

ofxExpr::ofxExpr(const std::string &name, const std::string &expression, const float &value, bool isExplicit) : ofxExpr() {
    set(expression);
    set(name, value, isExplicit);
}

ofxExpr::ofxExpr(const std::string &name, const std::string &expr) : ofxExpr() {
    setName(name);
    set(expr);
}

ofxExpr::ofxExpr(const std::string &name, const float &value, bool isExplicit) : ofxExpr() {
    set(value, isExplicit);
}

ofxExpr::ofxExpr(const std::string &name, const float &value, const float &min, const float &max, bool isExplicit) : ofxExpr(name, "", value, min, max, isExplicit) {}

ofxExpr::ofxExpr(const ofxExpr& other) : ofParameterGroup() {
    setName(other.getName());
    pExpr = other.getExpressionParameter();
    pValue = other.getValueParameter();
    pExplicit = other.getExplicitParameter();
}

ofxExpr& ofxExpr::operator= (const ofxExpr& other) {
    if (this != &other) {
        setName(other.getName());
        set(other.getExpression());
        set(other.getName(), other.getValue(), other.getMin(), other.getMax(), other.isExplicit());
    }
    return *this;
}

ofxExpr & ofxExpr::set(const std::string &expression) {
    pExpr->set(expression);
    pExplicit->set(false);
    compile();
    return *this;
}

ofxExpr & ofxExpr::set(const float &value, bool isExplicit) {
    pValue->set(value);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::set(const float &value, const float &min, const float &max, bool isExplicit) {
    pValue->set(NAME_VALUE, value, min, max);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::set(const std::string &name, const float &value, bool isExplicit) {
    setName(name);
    pValue->set(value);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::set(const std::string &name, const float &value, const float &min, const float &max, bool isExplicit) {
    setName(name);
    pValue->set(NAME_VALUE, value, min, max);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::set(const std::string &name, const std::string &expression, const float &value, const float &min, const float &max, bool isExplicit) {
    setName(name);
    pExpr->set(expression);
    pValue->set(NAME_VALUE, value, min, max);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::setExplicit(bool isExplicit) {
    pExplicit->set(isExplicit);
    return *this;
}

bool ofxExpr::operator== (const ofxExpr &e2) const {
    std::string v1 = isExplicit() ? ofToString(getValue()) : pExpr->get();
    std::string v2 = e2.isExplicit() ? ofToString(e2.getValue()) : e2.getExpression();
    return v1 == v2;
}

bool ofxExpr::operator!= (const ofxExpr &e2) const {
    return !(*this == e2);
}

std::shared_ptr<ofAbstractParameter> ofxExpr::newReference() const{
    return std::make_shared<ofxExpr>(*this);
}

void ofxExpr::makeReferenceTo(ofxExpr & mom) {
    pExpr = mom.getExpressionParameter();
    pValue = mom.getValueParameter();
    pExplicit = mom.getExplicitParameter();
}
