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
    
    
        int node_count = 3;
        float node_radius = 0.5;
        float joint_length = 1.0;
        float density = 1.0;
        float friction = 0.3;

        vector<vector<float>> node_locations;
//        vector<float> edge_locations;
    
    private:
    
        float x_position = 0;
        float y_position = 0;

    
    
};


#endif /* Walker_hpp */