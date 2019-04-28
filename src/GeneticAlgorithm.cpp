//
//  GeneticAlgorithm.cpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/26/19.
//

#include "GeneticAlgorithm.h"
#include <iostream>

//#include <math.h>

float CalculateFitness() {
    return -1.0f;
}

vector<float> Mate() {
    return {};
}

void MutateNodeGenes(vector<vector<float>>& walker_params) {
    //mutate node genes about the current parameter by a normal distribution and calculated standard deviation
    vector<float> node_radius_bound = {0.2, 1.0};
    vector<float> density_bound = {1.0, 4.0};
    vector<float> friction_bound = {0.05, 1};
    vector<float> restitution_bound = {0, 0.9};
    vector<float> joint_length_bound = {0.5, 2.5};
    vector<vector<float>> bounds = {node_radius_bound, density_bound, friction_bound, restitution_bound, joint_length_bound};
    
    //calculates standard deviation for each parameter
    vector<float> standard_deviation;
    for (int i = 0; i < bounds.size(); i++) {
        float std_dev = (bounds[i][1] - bounds[i][0]) / 4;
        standard_deviation.push_back(std_dev);
    }

    //calculates normal distribution and normalizes if outside of the bounds
    for (int i = 0; i < walker_params.size(); i++) {
        for (int j = 0; j < walker_params[i].size(); j++) {
            std::normal_distribution<float> distribution(walker_params[i][j], standard_deviation[i]);
            float number = distribution(generator);
            if ( number > bounds[i][1]) {
                walker_params[i][j] = bounds[i][1];
            }
            else if ( number < bounds[i][0]) {
                walker_params[i][j] = bounds[i][0];
            }
            else {
                walker_params[i][j] = number;
            }
        }
    }
    
    
}

void MutateJointGenes(vector<float>& joint_params) {
    //mutate joint genes about the current parameter by a normal distribution and calculated standard deviation
    
    //bounds of mutations
    vector<float> lower_angle_bound = {-0.75f,-0.1f};
    vector<float> upper_angle_bound = {0.1f, 0.5f};
    vector<float> motor_torque_bound = {400.0f, 1000.0f};
    vector<float> motor_speed_bound = {-10.0f, -0.5f};
    vector<vector<float>> bounds = {lower_angle_bound, upper_angle_bound, motor_torque_bound, motor_speed_bound};
    
    //calculates standard deviation for each parameter
    vector<float> standard_deviation;
    for (int i = 0; i < bounds.size(); i++) {
        float std_dev = (bounds[i][1] - bounds[i][0]) / 4;
        standard_deviation.push_back(std_dev);
    }
    //calculates normal distribution and normalizes if outside of the bounds
    for (int i = 0; i < joint_params.size(); i++) {
        std::normal_distribution<float> distribution(joint_params[i], standard_deviation[i]);
        float number = distribution(generator);
        if ( number > bounds[i][1]) {
            joint_params[i] = bounds[i][1];
        }
        else if ( number < bounds[i][0]) {
            joint_params[i] = bounds[i][0];
        }
        else {
            joint_params[i] = number;
        }
    }
}
