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
    ofSetLineWidth(8);

    vector<vector<vector<float>>> body_param = world.GetBodyDrawParameters();
    bool params_set = false;
    float x_position = 0;
    float y_position = 0;
    float radius = 0;
    int count = 0;
    for (int walker_num = 0; walker_num < body_param.size(); walker_num++) {
        for (int i = 0; i < body_param[walker_num].size(); i++) {
            for (int j = 0; j < body_param[walker_num][i].size(); j++) {
//                if (i == 0) {
//                    float radius = body_param[walker_num][i][j] * scaling_factor;
//                    std::cout<< "Radius: " << radius << std::endl;
//
//                }
//                else if (i == 1) {

                
//                if (i == 0) {
//                    radius = body_param[walker_num][0][j] * scaling_factor;
//                    std::cout<< "Radius: " << radius << std::endl;
//
//                    radius_set = true;
//                }
//                std::cout << "Count size " << body_param[walker_num][0].size() << std::endl;

                if (i == 1) {
                    x_position = body_param[walker_num][i][j] * scaling_factor;
                    y_position = body_param[walker_num][i][j+1] * scaling_factor;
                    radius = body_param[walker_num][0][count] * scaling_factor;
                    count++;
                    

//                    std::cout << count << std::endl;
                    params_set = true;
                }
            
                if (params_set) {
//                    std::cout<< "placing circle"<< std::endl;
//                    std::cout<< "Radius: " << radius << std::endl;
//
//                    std::cout<< "x_position: " << x_position << std::endl;
//                    std::cout<< "y_position: " << y_position << std::endl;
                    ofDrawCircle(x_position, y_position, radius);
                    //this is wrong need to go by nodes
                    if (j > 1) {
                        std::cout << "drawing lines" << std::endl;
                        float last_x_position = body_param[walker_num][i][j-2] * scaling_factor;
                        float last_y_position = body_param[walker_num][i][j-1] * scaling_factor;
                        ofDrawLine(x_position, y_position, last_x_position, last_y_position);
                    }
//                    count = 0;
                    //need to skip by 2 j
                    j++;
                    params_set = false;
                }

            }
        }
    }
//    for (int i = 0; i < body_param.size(); i++) {
//        if (i % 3 == 0) {
//            ofDrawCircle(body_param[i] * scaling_factor,body_param[i + 1] * scaling_factor,body_param[i + 2] * scaling_factor);
//        }
//    }
//    vector <b2Vec2> joint_param = world.GetJointDrawParameters();
//    ofSetLineWidth(8);
//
//
//    for (int i = 1; i < joint_param.size(); i++) {
//        ofDrawLine(joint_param[i].x * scaling_factor, joint_param[i].y * scaling_factor, joint_param[i - 1].x * scaling_factor, joint_param[i- 1].y * scaling_factor);
//    }
//
//    if(twoCircles){
//        ofDrawCircle(center->x-radius*.5, center->y, radius );
//        ofDrawCircle(center->x+radius*.5, center->y, radius );
//    }else{
//        ofDrawCircle((ofVec2f)center, radius );
//    }
////
    // auto draw?
    // should the gui control hiding?
    world.TimeStep();
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
