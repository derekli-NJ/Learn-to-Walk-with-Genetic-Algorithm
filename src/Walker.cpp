//
//  Walker.cpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/15/19.
//

#include "Walker.h"

Walker::Walker() {
    //clear values
    //    x_position = 250;
    //    y_position = 250;
    node_count = 3;
    
    node_radius = {0.5, 0.5, 0.5};
    //    node_radius.push_back(0.5);
    //    node_radius.push_back(0.5);
    //    node_radius.push_back(0.5);
    
    joint_length = {1, 1};
    density = {1.0, 2.0, 2.0};
    friction = {0.0625, 0.3, 0.0625};
    restitution = {0.75, 0.75, 0.75};
    
    //revolute joints parameters
    lower_angle = -0.75f; //multiplied by pi
    upper_angle = 0.0f; //multiplied by pi
    max_motor_torque = 1000.0;
    motor_speed = 4.0f;
    
    //distance joint parameters
    damping_ratio = 1.0;
    frequency_hz = 0.0;
    fitness = -99999;
    Setup();
}

void Walker::Setup() {
    node_locations.clear();
    node_locations.reserve(node_count);
    float curr_x = x_position;
    
    node_locations.push_back({curr_x, y_position});
    for (int i = 1; i < node_count; i++){
        curr_x += node_radius[i-1] + node_radius[i] + joint_length[i-1];
        node_locations.push_back({curr_x, y_position});
    }
}

Walker::Walker(const Walker &walker) {
    node_count = walker.node_count;
    node_radius = walker.node_radius;
    joint_length = walker.joint_length;
    density = walker.density;
    friction = walker.friction;
    restitution = walker.restitution;
    
    lower_angle = walker.lower_angle;
    upper_angle = walker.upper_angle;
    max_motor_torque = walker.max_motor_torque;
    motor_speed = walker.motor_speed;
    
    damping_ratio = walker.damping_ratio;
    frequency_hz = walker.frequency_hz;
    
    node_locations = walker.node_locations;
    fitness = walker.fitness;
}


//Equal assignment operator overload
Walker& Walker::operator= (const Walker &walker) {
    // do the copy
    node_count = walker.node_count;
    node_radius = walker.node_radius;
    joint_length = walker.joint_length;
    density = walker.density;
    friction = walker.friction;
    restitution = walker.restitution;
    
    lower_angle = walker.lower_angle;
    upper_angle = walker.upper_angle;
    max_motor_torque = walker.max_motor_torque;
    motor_speed = walker.motor_speed;
    
    damping_ratio = walker.damping_ratio;
    frequency_hz = walker.frequency_hz;
    
    node_locations = walker.node_locations;
    fitness = walker.fitness;
    
    // Overloaded assignment
    return *this;
}
