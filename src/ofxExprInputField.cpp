#include "ofxExprInputField.hpp"

//-----------------------------------------------------------
template<class Type>
void ofxExprInputField<Type>::parseInput(){
    value = input;
}

template class ofxExprInputField<float>;
