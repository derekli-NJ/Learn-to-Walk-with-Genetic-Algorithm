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
#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2World.h"
#include "PhysicsWorld.h"
#include "Walker.h"



using std::vector;

const int time_step_count = 1000;
const int generation_count = 100;
static int current_generation_count = 1;
const int population_size = 150;
const int parent_count = 25;
const int final_walker_count = 3;

static std::default_random_engine generator(2019);
//random is time(NULL)

//bounds of mutations for nodes
const vector<float> node_radius_bound = {0.2, 1.0};
const vector<float> density_bound = {1.0, 4.0};
const vector<float> friction_bound = {0.05, 1};
const vector<float> restitution_bound = {0, 0.9};
const vector<float> joint_length_bound = {0.5, 2.5};
const vector<vector<float>> node_bounds = {node_radius_bound, density_bound, friction_bound, restitution_bound, joint_length_bound};

//bounds of mutations for joints
const vector<float> lower_angle_bound = {-0.75f,-0.1f};
const vector<float> upper_angle_bound = {-0.05f, 0.1f};
const vector<float> motor_torque_bound = {400.0f, 1000.0f};
const vector<float> motor_speed_bound = {0.5f, 10.0f};

const vector<vector<float>> joint_bounds = {lower_angle_bound, upper_angle_bound, motor_torque_bound, motor_speed_bound};


float CalculateFitness(b2Body* node, float start_position);
vector<float> Mate();

void InitialJointGeneration(vector<float>& joint_params);

vector<vector<float>> InitialNodeGeneration(vector<vector<float>>& walker_params);

void MutateNodeGenes(vector<vector<float>>& walker_params);

void MutateJointGenes(vector<float>& joint_params);

vector<Walker> FindBestWalker(World world);

vector<Walker> InitialGeneration();

vector<Walker> Training(vector<Walker>& walkers, World& world);

vector<Walker> MakeChildren(vector<Walker>& parents);

float Simulation(Walker& walker, World& world);

void WriteWalkerToFile(vector<Walker>& best_walkers);

//#endif /* GeneticAlgorithm_h */
