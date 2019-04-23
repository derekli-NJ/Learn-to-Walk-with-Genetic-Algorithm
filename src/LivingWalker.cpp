//
//  LivingWalker.cpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/20/19.
//

#include "LivingWalker.h"
#include <iostream>




LivingWalker::LivingWalker(const Walker &walker, const vector<b2Body*>& bodies) {
    node_radius = walker.node_radius;
    

    
    for (int i = 0; i < bodies.size(); i++) {
        body_storage.push_back(bodies[i]);
//        b2Vec2 position = bodies[i] -> GetPosition();
//        walker_position.push_back(position.x);
//        walker_position.push_back(position.y);
//        body_draw_parameters.push_back(walker.node_radius);
    }
}

void LivingWalker::Update() {
    
}

vector<vector<float>> LivingWalker::Draw() { 
    vector<vector<float>> body_draw_parameters;
    body_draw_parameters.push_back(node_radius);
//    std::cout<< "Radius: " << node_radius[0] << std::endl;
        
    for (int i = 0; i < body_storage.size(); i++) {
        b2Vec2 position = body_storage[i] -> GetPosition();
        walker_position.push_back(position.x);
        walker_position.push_back(position.y);
    }
    body_draw_parameters.push_back(walker_position);
    
//    std::cout << "Radius size" << body_draw_parameters[0].size() << std::endl;
//    std::cout << "Position size" << body_draw_parameters[1].size() << std::endl;
//    
    return body_draw_parameters;
//    return body_draw_parameters;
}
