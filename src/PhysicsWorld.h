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
#include "LivingWalker.h"

using std::vector;
using std::shared_ptr;

class World {
    public:
        //Constructor
        World();
    
        b2Body* AddWalker(Walker walker);
        void Clear();
        void TimeStep();
    
        
//        vector<b2Vec2> joint_draw_parameters;
    
        vector<float> ground_draw_parameters;
        vector<float>& GetGroundDrawParameters();
    
        vector<vector<vector<float>>> GetBodyDrawParameters();
        
//        const vector<b2Vec2>& GetJointDrawParameters();

        
    private:
        b2World* world;
        vector<b2Body*> bodies;
        vector<b2Vec2> positions;
        vector<LivingWalker> living_walkers;
    
    
        b2RevoluteJoint* joint;

    
        const float ground_width = 100.0f;
        const float ground_height = 2.0f;

        const float32 timeStep = 1/60.0;      //the length of time passed to simulate (seconds)
        const int32 velocityIterations = 10;   //how strongly to correct velocity
        const int32 positionIterations = 10;   //how strongly to correct position
    
};


#endif /* physics_hpp */
