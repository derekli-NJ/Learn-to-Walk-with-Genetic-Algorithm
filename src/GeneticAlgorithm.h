//
//  GeneticAlgorithm.hpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/26/19.
//
#pragma once

#include <stdio.h>
#include <vector>

using std::vector;

const int time_step_count = 1000;
const int generation_count = 1;
const int population_size = 100;

float CalculateFitness();
vector<float> Mate();
vector<vector<float>> MutateNodeGenes(vector<vector<float>> walker_params);

void MutateJointGenes(vector<float>& joint_params);


vector<float> CalculateNodeMutations();
//vector<float> CalculateJointMutations();


//#endif /* GeneticAlgorithm_h */
