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
    Setup();
}

void Walker::Setup() {
	vector<float> node_location = {x_position, y_position};
	node_locations.push_back(node_location);
    for (int i = 1; i < node_count; i++) {
        node_location[0] = node_location[0] + node_radius[i-1] + node_radius[i] + joint_length[i-1];
        node_locations.push_back(node_location);
    }
}
