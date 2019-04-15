//
//  Walker.cpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/15/19.
//

#include "Walker.h"

Walker::Walker() {
	//clear values
	x_position = 0;
	y_position = 0;
    Setup();
}

void Walker::Setup() {
	vector<float> node_location = {x_position, y_position};
	node_locations.push_back(node_location);
//    edge_locations.push_back(node_location[0] + node_radius, y_position);
	for (int i = 1; i < node_count; i++) {
		node_location[0] = node_location[0] + 2 * node_radius + joint_length; 
		node_locations.push_back(node_location);
//        edge_locations.push_back(node_location[0] + node_radius, )
	}
}
