//
//  GeneticAlgorithm.cpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/26/19.
//

#include "GeneticAlgorithm.h"
#include <iostream>
#include <random>

//#include <math.h>


float CalculateFitness() {
    return -1.0f;
}

vector<float> Mate() {
    return {};
}

int dummy () {
    return 0;
}

vector<vector<float>> MutateNodeGenes(vector<vector<float>> walker_params) {
    return {{}};
}

//void MutateJointGenes(vector<float> &joint_params) {
//    vector<float> mutations = CalculateJointMutations();
//    if (joint_params.size() != mutations.size()) {
//        std::cout << "Sizes not equal" << std::endl;
//        throw (-1);
//    }
//
//    for (int i = 0; i < mutations.size(); i++) {
//        joint_params[i] += mutations[i];
//    }
//}

vector<float> CalculateNodeMutations() {
    return {};
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
    std::default_random_engine generator;
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
