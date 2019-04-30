#include "ofApp.h"

#include <vector>



using std::vector;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
//    int time_step_count = 1000;
//    int generation_count = 1;
//    int population_size = 100;

    
//    float start_position = walker.x_position;
    if (training) {
        vector<Walker> best_walkers = FindBestWalker(world);
        WriteWalkerToFile(best_walkers);
        Walker walker = best_walkers[0];
        std::cout << "---Best Walker Params---" << std::endl;
        for (int i = 0; i < walker.joint_length.size(); i++) {
            std::cout<< "Joint length " << walker.joint_length[i] << std::endl;
        }
        for (int i = 0; i < walker.node_radius.size(); i++) {
            std::cout<< "Node radius " << walker.node_radius[i] << std::endl;
        }
        world.AddWalker(walker);
    }
    else if (read_from_file) {
        vector<Walker> best_walkers = ReadWalkerFromFile();
//        if (ind < )
        Walker walker = best_walkers[3];
        world.AddWalker(walker);
    }

    
    ofSetVerticalSync(true);
    
    // we add this listener before setting up so the initial circle resolution is correct
    circleResolution.addListener(this, &ofApp::circleResolutionChanged);
    ringButton.addListener(this, &ofApp::ringButtonPressed);
    
    

    
    gui.setup(); // most of the time you don't need a name
    gui.add(filled.setup("fill", true));
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(circleResolution.setup("circle res", 90, 3, 90));
    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    
    gui.add(ringButton.setup("Time Step"));
    bHide = false;
    
    std::cout << "what the hell" <<std::endl;
//    ring.load("ring.wav");
    
    std::cout << "1" <<std::endl;

//    }
}




//--------------------------------------------------------------
void ofApp::exit(){
    ringButton.removeListener(this, &ofApp::ringButtonPressed);
    world.DeleteWorld();
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
//    std::cout << "2" <<std::endl;

    ofSetCircleResolution(circleResolution);
    world.TimeStep();
    
//    std::cout << "3" <<std::endl;


}

//--------------------------------------------------------------
void ofApp::draw(){
//    std::cout << "4" <<std::endl;

    if (no_gui) {
        return;
    }
    ofBackgroundGradient(ofColor::white, ofColor::gray);
//    std::cout << "5" <<std::endl;

    if(filled){
        ofFill();
    }else{
        ofNoFill();
    }
    ofSetColor(color);
    ofSetLineWidth(4);
    
    vector<float> ground_param = world.GetGroundDrawParameters();
//    std::cout << "6" << std::endl;
//    ground_param[0] -= ground_param[2];
//    ground_param[1] -= ground_param[3];
    ofDrawRectangle(ground_param[0] * scaling_factor, (ground_param[1] + ground_param[3]) * y_scaling_factor + screen_height, ground_param[2] * scaling_factor, ground_param[3] * scaling_factor);
//    }

    vector<vector<vector<float>>> body_param = world.GetBodyDrawParameters();
    bool params_set = false;
    float x_position = 0;
    float y_position = 0;
    float radius = 0;
    int count = 0;
    for (int walker_num = 0; walker_num < body_param.size(); walker_num++) {
        for (int i = 0; i < body_param[walker_num].size(); i++) {
            for (int j = 0; j < body_param[walker_num][i].size(); j++) {
                if (i == 1) {
                    x_position = body_param[walker_num][i][j] * scaling_factor;
                    y_position = body_param[walker_num][i][j+1] * y_scaling_factor + screen_height;
                    radius = body_param[walker_num][0][count] * scaling_factor;
                    if (j > 1) {
                        //                        std::cout << "drawing lines" << std::endl;
                        float last_x_position = body_param[walker_num][i][j-2] * scaling_factor;
                        float last_y_position = body_param[walker_num][i][j-1] * y_scaling_factor  + screen_height;
                        ofSetColor(0, 0, 0);
                        ofDrawLine(x_position, y_position, last_x_position, last_y_position);
                    }
                    
                    if (count == 1) {
                        ofSetColor(0, 0, 255);
                    }
                    if (count == 2) {
                        ofSetColor(255, 0, 0);
                    }
                    count++;

                    ofDrawCircle(x_position, y_position, radius);

                    //need to skip by 2 j
                    j++;
                    params_set = false;
                }
            }
        }
    }
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
        ringButtonPressed();
    }
    else if (key == 'n') {
//        world.joint -> EnableMotor(!world.joint -> IsMotorEnabled());
        world.joint -> SetMotorSpeed(-world.joint -> GetMotorSpeed());
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
    screen_height = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
