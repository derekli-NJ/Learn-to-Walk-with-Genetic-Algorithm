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
        int node_count;
    
        vector<float> node_radius;
        vector<float> joint_length;
        vector<float> density;
        vector<float> friction;
        vector<float> restitution;
    
        //revolute joints parameters
        float lower_angle; //multiplied by pi
        float upper_angle; //multiplied by pi
        float max_motor_torque;
        float motor_speed;

        //distance joint parameters
        float damping_ratio;
        float frequency_hz;
    
        vector<vector<float>> node_locations;
    
        const float x_position = 1.5;
        const float y_position = 4;
    
    
        // Overloaded assignment operator
        Walker& operator= (const Walker &walker);
    
        //Overloaded copy constructor
        Walker(const Walker& walker);
    
};


#endif /* Walker_hpp */
