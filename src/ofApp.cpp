#include "ofApp.h"
#include <vector>

using std::vector;
//--------------------------------------------------------------
void ofApp::setup(){
    

    walker.Setup();
    world.AddWalker(walker);
    
    
    ofSetVerticalSync(true);
    
    // we add this listener before setting up so the initial circle resolution is correct
    circleResolution.addListener(this, &ofApp::circleResolutionChanged);
    ringButton.addListener(this, &ofApp::ringButtonPressed);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(filled.setup("fill", true));
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(circleResolution.setup("circle res", 90, 3, 90));
    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    
    bHide = false;
    
    ring.load("ring.wav");
}

//--------------------------------------------------------------
void ofApp::exit(){
    ringButton.removeListener(this, &ofApp::ringButtonPressed);
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int &circleResolution){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
    ring.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    
    
    
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    
    if(filled){
        ofFill();
    }else{
        ofNoFill();
    }
    ofSetColor(color);
    std::cout<< "hi"<< std::endl;
    vector <float> body_param = world.GetBodyDrawParameters();
    for (int i = 0; i < body_param.size(); i++) {
        if (i % 3 == 0) {
            ofDrawCircle(body_param[i] * scaling_factor,body_param[i + 1] * scaling_factor,body_param[i + 2] * scaling_factor);
        }
    }
    vector <b2Vec2> joint_param = world.GetJointDrawParameters();
    ofSetLineWidth(8);
    for (int i = 1; i < joint_param.size(); i++) {
        
        ofDrawLine(joint_param[i].x * scaling_factor, joint_param[i].y * scaling_factor, joint_param[i - 1].x * scaling_factor, joint_param[i- 1].y * scaling_factor);
    }

//    if(twoCircles){
//        ofDrawCircle(center->x-radius*.5, center->y, radius );
//        ofDrawCircle(center->x+radius*.5, center->y, radius );
//    }else{
//        ofDrawCircle((ofVec2f)center, radius );
//    }
//
    // auto draw?
    // should the gui control hiding?
    if(!bHide){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'h'){
        bHide = !bHide;
    }
    else if(key == 's'){
        gui.saveToFile("settings.xml");
    }
    else if(key == 'l'){
        gui.loadFromFile("settings.xml");
    }
    else if(key == ' '){
        color = ofColor(255);
    }
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
    screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
