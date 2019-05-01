#include "ofApp.h"

#include <vector>


 
using std::vector;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);

    if (training) {
        vector<Walker> best_walkers = FindBestWalker(world);
        Walker walker = best_walkers[0];
        fitness = walker.fitness;
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
        best_walkers = ReadWalkerFromFile();
        Walker walker = best_walkers[0];
        fitness = walker.fitness;
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
    
    screen_width = ofGetWidth();
    screen_height = ofGetHeight();
    line_x_position = screen_width / line_count;
    my_font.load("Avenir.ttf", 32);
//    ring.load("ring.wav");
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
//    ofDrawRect

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
                    float x_offset = 0;
                    if (body_param[walker_num][1][0] > 7.5) {
                        x_offset = (7.5 - body_param[walker_num][1][0]) * scaling_factor;
                    }
//                    for (int i = 0; i < 100; i++) {
//                        int x = i * scaling_factor + x_offset;
//                        ofDrawLine(x, (ground_param[1] + ground_param[3]) * y_scaling_factor + ofGetScreenHeight(), x, ground_param[1] * y_scaling_factor + ofGetScreenHeight());
                    for (int i = 0; i < line_x_position; i++) {
                        ofDrawLine( (line_x_position * i) + x_offset, (ground_param[1] + ground_param[3]) * y_scaling_factor + screen_height, (line_x_position * i) + x_offset, ground_param[1] * y_scaling_factor + screen_height);
                    }
//                    }
                    
                    x_position = body_param[walker_num][i][j] * scaling_factor;
                    y_position = body_param[walker_num][i][j+1] * y_scaling_factor + screen_height;
                    radius = body_param[walker_num][0][count] * scaling_factor;
                    if (j > 1) {
                        //                        std::cout << "drawing lines" << std::endl;
                        float last_x_position = body_param[walker_num][i][j-2] * scaling_factor;
                        float last_y_position = body_param[walker_num][i][j-1] * y_scaling_factor  + screen_height;
                        ofSetColor(0, 0, 0);
                        ofDrawLine(x_position + x_offset, y_position, last_x_position + x_offset, last_y_position);
                    }
                    
                    if (count == 1) {
                        ofSetColor(0, 0, 255);
                    }
                    if (count == 2) {
                        ofSetColor(255, 0, 0);
                    }
                    count++;

                    ofDrawCircle(x_position + x_offset, y_position, radius);

                    //need to skip by 2 j
                    j++;
                    params_set = false;
                }
            }
        }
    }
    ofSetColor(0, 0, 0);
    string fitness_string = "Fitness Score: " + std::to_string(fitness);
    string generation_string = "Generation: " + std::to_string(generation);
    if (fitness_string.size() > 21 || generation_string.size() > 21) {
        fitness_string = fitness_string.substr(0,21);
        generation_string = generation_string.substr(0,21);
    }
    my_font.drawString(fitness_string, screen_width - 450, screen_height - 700);
    my_font.drawString(generation_string, screen_width - 450, screen_height - 650);
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
        if (read_from_file) {
            if (generation < best_walkers.size()) {
                world.DeleteWorld();
                world = World();
                Walker walker = best_walkers[generation];
                fitness = walker.fitness;
                generation++;
                world.AddWalker(walker);
            }
            else {
                std::cout << "Last generation" << std::endl;
            }

        }
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
    screen_width = w;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
