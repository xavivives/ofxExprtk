#include "ofApp.h"
#include "ofxExpr.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    float x = 123.0;
    float y = 678.0;
    
    ofxExpr expr("x * y + 3");
    expr.add_var("x", x);
    expr.add_var("y", y);
    expr.compile();
    cout << expr.value() << endl;
    
    x = 2;
    y = 3;
    cout << expr.value() << endl;
    
    ofxExpr expr2("sin(x)");
    expr2.add_var("x", x);
    expr2.compile();
    cout << expr2.value() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
