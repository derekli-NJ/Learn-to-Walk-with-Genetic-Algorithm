#include "ofMain.h"
#include "ofApp.h"
#include "PhysicsWorld.h"
#include "Walker.h"

#include <iostream>
using std::cout;
using std::endl;

//========================================================================
int main( ){
    
    Walker walker;
    World world;
    
    walker.Setup();
    //    walker.node_locations;
    
    world.AddWalker(walker);
    
    
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
    

//    setup();
//    std::cout << circlePosition[0].x << std::endl;


}
