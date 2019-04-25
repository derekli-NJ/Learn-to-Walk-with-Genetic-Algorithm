//
//  LivingWalker.hpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/20/19.
//

#ifndef LivingWalker_hpp
#define LivingWalker_hpp

#include <stdio.h>
#include <vector>

#include "Walker.h"
#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2World.h"

using std::vector;

class LivingWalker {
    
    public:
        LivingWalker(const Walker &walker, const vector<b2Body*> &bodies);
    
        vector<float> node_radius;
        
        vector<b2Body*> body_storage;
    
        void Update();
        vector<vector<float>> Draw();
    
    
};

#endif /* LivingWalker_hpp */
