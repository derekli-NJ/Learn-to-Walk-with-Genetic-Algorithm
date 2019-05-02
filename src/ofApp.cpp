#include "ofApp.h"

#include <vector>


 
using std::vector;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);

    gc_evans.load("/Users/derekli/Documents/CS126/final-project-derekli-NJ/data/gcevans.png");
    jordans.load("/Users/derekli/Documents/CS126/final-project-derekli-NJ/data/shoes.png");
    background.load("/Users/derekli/Documents/CS126/final-project-derekli-NJ/data/background.png");
    



    
    ofSetVerticalSync(true);
    
    // we add this listener before setting up so the initial circle resolution is correct
    circleResolution.addListener(this, &ofApp::circleResolutionChanged);
//    ringButton.addListener(this, &ofApp::ringButtonPressed);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(train.setup("Train", true));
//    gui.add(ringButton.setup("fill", true));
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(circleResolution.setup("circle res", 90, 3, 90));
    gui.add(generation_size.setup("Generation count", 10, 1, 250));
    gui.add(parent.setup("Parent count", 10, 1, 50));
    gui.add(population.setup("Population size", 250, 50, 300));
    gui.add(time_step.setup("Time-step count", 2400, 1200, 3600));

    ofSetCircleResolution(90);
    
    bHide = false;
    ofFill();
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
    ofSetCircleResolution(circleResolution);
    if (!pause_screen && !start_screen && trained) {
        world.TimeStep();
        time++;
    }
}

void ofApp::ReadFromFile() {
    best_walkers = ReadWalkerFromFile();
    Walker walker = best_walkers[0];
    fitness = walker.fitness;
    world.AddWalker(walker);
}

void ofApp::Training() {
    SetGenerationCount(generation_size);
    SetParentCount(parent);
    SetPopulationSize(population);
    SetTimeStepCount(time_step);
    
    best_walkers = FindBestWalker();
    std::cout << generation << std::endl;
    std::cout << best_walkers.size() << std::endl;
    Walker walker = best_walkers[generation - 1];
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


//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor::white, ofColor::gray);

    ofSetLineWidth(4);
    if (start_screen) {
        // auto draw?
        // should the gui control hiding?
        if(!bHide){
            gui.draw();
        }
        ofSetColor(0,0,0);
        my_font.drawString("Press Space to Enter", screen_width - 700, screen_height - 400);
        return;
    }
    if (!trained) {
        if (train) {
            Training();
        }
        else {
            ReadFromFile();
        }
        
        
        trained = true;
    }
    vector<float> ground_param = world.GetGroundDrawParameters();

    vector<vector<vector<float>>> body_param = world.GetBodyDrawParameters();
    float x_offset = 0;
    if (body_param[0][1][0] > 7.5) {
        x_offset = (7.5 - body_param[0][1][0]) * scaling_factor;
    }
    ofSetColor(255, 255, 255);
    float background_offset = x_offset;
    
    while (background_offset <= -screen_width) {
        background_offset += screen_width;
    }
    background.draw(background_offset , 0, screen_width, screen_height);
    background.draw(background_offset + screen_width, 0, screen_width, screen_height);
    ofSetColor(color);
    ofDrawRectangle(ground_param[0] * scaling_factor, (ground_param[1] + ground_param[3]) * y_scaling_factor + screen_height, ground_param[2] * scaling_factor, ground_param[3] * scaling_factor);

    bool params_set = false;
    float x_position = 0;
    float y_position = 0;
    float radius = 0;
    int count = 0;
    for (int walker_num = 0; walker_num < body_param.size(); walker_num++) {
        for (int i = 0; i < body_param[walker_num].size(); i++) {
            for (int j = 0; j < body_param[walker_num][i].size(); j++) {
                if (i == 1) {

                    for (int i = 0; i < line_x_position; i++) {
                        ofDrawLine( (line_x_position * i) + x_offset, (ground_param[1] + ground_param[3]) * y_scaling_factor + screen_height, (line_x_position * i) + x_offset, ground_param[1] * y_scaling_factor + screen_height);
                    }
                    
                    x_position = body_param[walker_num][i][j] * scaling_factor;
                    y_position = body_param[walker_num][i][j+1] * y_scaling_factor + screen_height;
                    radius = body_param[walker_num][0][count] * scaling_factor;
                    if (j > 1) {
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

                    if ((j == 0 || j == 4) && toggle) {
                        ofSetColor(255, 255, 255);
                        jordans.draw(x_position + x_offset - radius, y_position - radius * 0.5 , 2 * radius, 2 *  radius);
                    }
                    if (j == 2 && toggle) {
                        ofSetColor(255, 255, 255);
                        gc_x_position = x_position + x_offset - radius;
                        gc_y_position = y_position - radius;
                        gc_radius = 2 * radius;
                    }
                    else if (!toggle) {
                        ofDrawCircle(x_position + x_offset, y_position, radius);
                    }
                    //need to skip by 2 j
                    j++;
                    params_set = false;
                }
            }
        }
    }
    if (toggle) {
        gc_evans.draw(gc_x_position, gc_y_position, gc_radius, gc_radius);
    }
    float distance = body_param[0][1][0] - 1.5;
    
    string fitness_string = "Fitness Score: " + std::to_string(fitness);
    string generation_string = "Generation: " + std::to_string(generation);
    string timer_string = "Time: " + std::to_string(time / 60);
    timer_string = timer_string.substr(0, 11);
    timer_string +=  "s";
    string distance_string = "Distance: " + std::to_string(distance);
    fitness_string = fitness_string.substr(0, 21);
    generation_string = generation_string.substr(0, 21);
    distance_string = distance_string.substr(0, 17);
    
    ofSetColor(255, 255, 255);
    ofDrawPlane(screen_width - 275, screen_height - 750, 375, 300);
    ofDrawPlane(screen_width - 750, screen_height - 750, 325, 300);
    ofSetColor(0, 0, 0);
    my_font.drawString(fitness_string, screen_width - 450, screen_height - 700);
    if (train) {
        string walkers_from_last_gen = "Walker Rank: " + std::to_string(generation);
        my_font.drawString(walkers_from_last_gen, screen_width - 450, screen_height - 650);
    }
    else {
        my_font.drawString(generation_string, screen_width - 450, screen_height - 650);
    }
    my_font.drawString(timer_string, screen_width - 875, screen_height - 700);
    my_font.drawString(distance_string, screen_width - 875, screen_height - 650);
    
    if (pause_screen) {
        ofSetColor(255, 255, 255);
        ofDrawPlane(screen_width - 500, screen_height - 400, 200, 100);
        ofSetColor(0, 0, 0);
        my_font.drawString( "Paused", screen_width - 550, screen_height - 400);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'h'){
        bHide = !bHide;
    }
    else if(key == 's'){
        if (pause_screen) {
            world.TimeStep();
            time++;
        }
    }
    else if(key == 'l'){
        gui.loadFromFile("settings.xml");
    }
    else if(key == ' '){
        if (start_screen) {
            start_screen = false;
        }
        else if (!start_screen) {
            toggle = !toggle;
        }
    }
    else if (key == 'n') {
        if (read_from_file && !train) {
            if (generation < best_walkers.size()) {
                time = 0;
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
        else {
            if (generation < best_walkers.size() - 1) {
                time = 0;
                world.DeleteWorld();
                world = World();
                Walker walker = best_walkers[generation];
                fitness = walker.fitness;
                generation++;
                world.AddWalker(walker);
            }
        }
    }
    else if (key == 'b') {
        if (read_from_file) {
            if (generation > 1) {
                time = 0;
                world.DeleteWorld();
                world = World();
                Walker walker = best_walkers[generation];
                fitness = walker.fitness;
                generation--;
                world.AddWalker(walker);
            }
            else {
                std::cout << "First generation" << std::endl;
            }
        }
    }
    else if (key == 'p') {
        pause_screen = !pause_screen;
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
