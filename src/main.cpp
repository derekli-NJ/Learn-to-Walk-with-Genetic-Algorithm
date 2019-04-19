#include "ofMain.h"
#include "ofApp.h"

//#include "PhysicsWorld.h"
//#include "Walker.h"

#include <iostream>
using std::cout;
using std::endl;

//========================================================================
int main( ){
    
    
    
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    
    //transform the world to screen?
//    float lowerX = -25.0f, upperX = 25.0f, lowerY = -5.0f, upperY = 25.0f;
//    gluOrtho2D(lowerX, upperX, lowerY, upperY);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
    

//    setup();
//    std::cout << circlePosition[0].x << std::endl;


}
