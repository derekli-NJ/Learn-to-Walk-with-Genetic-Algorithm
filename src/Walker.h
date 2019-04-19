//
//  Walker.hpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/15/19.
//

#ifndef Walker_hpp
#define Walker_hpp

#include <stdio.h>
#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2World.h"
#include <vector>

using std::vector;

class Walker {
    public:
        //Default constructor (reset values)
        Walker();
        void Setup();
    
        //node parameters
        int node_count = 3;
        float node_radius = 0.5;
        float joint_length = 1;
        float density = 1.0;
        float friction = 0.3;
    
        //revolute joints parameters
        float lower_angle = -0.5f; //multiplied by pi
        float upper_angle = 0.25f; //multiplied by pi
        float max_motor_torque = 10.0;
        float motor_speed = 1.0f;

        //distance joint parameters
        float damping_ratio = 1.0;
        float frequency_hz = 0.0;
    
        vector<vector<float>> node_locations;
    private:
    
        float x_position = 8;
        float y_position = 10;

    
    
};


#endif /* Walker_hpp */
