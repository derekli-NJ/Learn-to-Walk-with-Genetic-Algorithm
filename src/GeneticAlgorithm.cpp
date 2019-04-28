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

void InitialNodeGeneration(vector<vector<float>>& walker_params) {
    //mutate node genes about the current parameter by a normal distribution and calculated standard deviation
    srand (time(NULL));
    for (int i = 0; i < node_bounds.size();i++) {
        for (int j = 0; j < walker_params.size();j++) {
            float random_number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float range = node_bounds[i][1] - node_bounds[i][0];
            walker_params[i][j] = random_number * range + node_bounds[i][0];
        }
    }
}


void InitialJointGeneration(vector<float>& joint_params) {
    //mutate joint genes about the current parameter by a normal distribution and calculated standard deviation
    srand (time(NULL));
    for (int i = 0; i < joint_bounds.size(); i++) {
        float random_number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float range = joint_bounds[i][1] - joint_bounds[i][0];
        joint_params[i] = random_number * range + joint_bounds[i][0];
    }
}


void MutateNodeGenes(vector<vector<float>>& walker_params) {
    //mutate node genes about the current parameter by a normal distribution and calculated standard deviation
    
    //calculates standard deviation for each parameter
    vector<float> standard_deviation;
    for (int i = 0; i < node_bounds.size(); i++) {
        float std_dev = (node_bounds[i][1] - node_bounds[i][0]) / 4;
        standard_deviation.push_back(std_dev);
    }

    //calculates normal distribution and normalizes if outside of the bounds
    for (int i = 0; i < walker_params.size(); i++) {
        for (int j = 0; j < walker_params[i].size(); j++) {
            std::normal_distribution<float> distribution(walker_params[i][j], standard_deviation[i]);
            float number = distribution(generator);
            if ( number > node_bounds[i][1]) {
                walker_params[i][j] = node_bounds[i][1];
            }
            else if ( number < node_bounds[i][0]) {
                walker_params[i][j] = node_bounds[i][0];
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
    vector<float> upper_angle_bound = {-0.05f, 0.1f};
    vector<float> motor_torque_bound = {400.0f, 1000.0f};
    vector<float> motor_speed_bound = {0.5f, 10.0f};
    
    //calculates standard deviation for each parameter
    vector<float> standard_deviation;
    for (int i = 0; i < joint_bounds.size(); i++) {
        float std_dev = (joint_bounds[i][1] - joint_bounds[i][0]) / 4;
        standard_deviation.push_back(std_dev);
    }
    //calculates normal distribution and normalizes if outside of the bounds
    for (int i = 0; i < joint_params.size(); i++) {
        std::normal_distribution<float> distribution(joint_params[i], standard_deviation[i]);
        float number = distribution(generator);
        if ( number > joint_bounds[i][1]) {
            joint_params[i] = joint_bounds[i][1];
        }
        else if ( number < joint_bounds[i][0]) {
            joint_params[i] = joint_bounds[i][0];
        }
        else {
            joint_params[i] = number;
        }
    }
}
