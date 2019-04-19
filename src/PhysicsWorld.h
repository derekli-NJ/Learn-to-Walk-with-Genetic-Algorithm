//
//  physics.hpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/12/19.
//
#pragma once
#ifndef physics_hpp
#define physics_hpp

#include <stdio.h>
#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2World.h"
#include <vector>
#include "Walker.h"

using std::vector;
using std::shared_ptr;

class World {
    public:
        //Constructor
        World();
    
        b2Body* AddWalker(Walker walker);
        void Clear();
        void TimeStep();
    
        vector<float> body_draw_parameters;
        vector<b2Vec2> joint_draw_parameters;
    
        const vector<float>& GetBodyDrawParameters();
        const vector<b2Vec2>& GetJointDrawParameters();

        
    private:
        b2World* world;
        vector<b2Body*> bodies;
        vector<b2Vec2> positions;
    

        const float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
        const int32 velocityIterations = 8;   //how strongly to correct velocity
        const int32 positionIterations = 3;   //how strongly to correct position
    
};



//extern vector<b2Vec2> circlePosition;
//
//void setup();
////vector<b2PolygonShape> polygons;

//vector <shared_ptr<b2PolygonShape>> polygons;


#endif /* physics_hpp */
