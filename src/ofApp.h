#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "PhysicsWorld.h"
#include "Walker.h"
#include "GeneticAlgorithm.h"
#include <string>

using std::string;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void circleResolutionChanged(int & circleResolution);
    void ringButtonPressed();
    
    bool bHide;
        
    ofxFloatSlider radius;
    ofxColorSlider color;
    ofxVec2Slider center;
    ofxIntSlider circleResolution;
    ofxToggle filled;
    ofxButton twoCircles;
    ofxButton ringButton;
    ofxLabel screenSize;
    
    ofxPanel gui;
    
    World world;
    
    ofSoundPlayer ring;

    ofTrueTypeFont my_font;
    
    
    
    float scaling_factor = 50.0;
    
    int screen_height;
    int screen_width;
    int line_count = 10;
    int line_x_position;
    
    float y_scaling_factor = -1 * scaling_factor;
    
    bool training = true;
    bool read_from_file = false;
    bool no_gui = false;
    
    vector<Walker> best_walkers;
    
//    int count = 1;
    
    float fitness;
    int generation = 1;
//    float x_offset = 5;

};

