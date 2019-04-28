//
//  GeneticAlgorithm.hpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/26/19.
//
#pragma once

#include <stdio.h>
#include <vector>
#include <random>


using std::vector;

const int time_step_count = 1000;
const int generation_count = 1;
const int population_size = 100;
static std::default_random_engine generator(time(NULL));


float CalculateFitness();
vector<float> Mate();

void MutateNodeGenes(vector<vector<float>>& walker_params);

void MutateJointGenes(vector<float>& joint_params);

//#endif /* GeneticAlgorithm_h */
