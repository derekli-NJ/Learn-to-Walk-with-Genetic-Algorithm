//
//  GeneticAlgorithm.cpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/26/19.
//

#include "GeneticAlgorithm.h"
#include <iostream>
#include <fstream>
using std::ofstream;

//#include <math.h>

vector<Walker> InitialGeneration() {
    vector<Walker> walkers;
    walkers.reserve(population_size);
    //Walker walker;
    for (int i = 0; i < population_size; i++) {
        //walker = Walker();
        Walker walker;
        vector<float> joint_param = {walker.lower_angle, walker.upper_angle, walker.max_motor_torque, walker.motor_speed};
        vector<float> test1 = joint_param;
        
        InitialJointGeneration(joint_param);
//        for (int i = 0; i < joint_param.size(); i++) {
//            std::cout << "Old value: " << test1[i] << " New Value: " << joint_param[i] << std::endl;
//        }
        walker.lower_angle = joint_param[0];
        walker.upper_angle = joint_param[1];
        walker.max_motor_torque = joint_param[2];
        walker.motor_speed = joint_param[3];
        
        //node parameter mutations
        vector<vector<float>> node_param0 = {walker.node_radius, walker.density, walker.friction, walker.restitution, walker.joint_length};
        
        vector<vector<float>> node_param = InitialNodeGeneration(node_param0);
        
        walker.node_radius = node_param[0];
        walker.density = node_param[1];
        walker.friction = node_param[2];
        walker.restitution = node_param[3];
        walker.joint_length = node_param[4];
//        std::cout << &walker << std::endl;
        
        //Walker local_walker;
        //walkers.push_back(local_walker);
        walker.Setup();
        walkers.push_back(walker);
//        vector<LivingWalker> living_walker = world.AddWalker(walker);
    }
//    walkers.push_back(Walker());
    return walkers;
}

vector<Walker> FindBestWalker(World world) {
    srand (2019);
    vector<Walker> children = InitialGeneration();
    vector<Walker> parents;
    for (int i = 0; i < generation_count; i++) {
        std::cout<<current_generation_count<<std::endl;
        parents = Training(children, world);
        children = MakeChildren(parents);
        current_generation_count += 1;
    }
    std::cout << "Training"<<std::endl;
    return (Training(children, world));
    return vector<Walker>();
}

vector<Walker> Training(vector<Walker>& walkers, World& world) {
    vector<float> fitness_scores;
    vector<Walker> parents;
    for (Walker& walker : walkers) {
        fitness_scores.push_back(Simulation(walker, world));
    }
    for (int i = 0; i < parent_count; i++) {
        int max_element_index = std::max_element(fitness_scores.begin(), fitness_scores.end()) - fitness_scores.begin();
        parents.push_back(walkers[max_element_index]);
        walkers.erase(walkers.begin() + max_element_index);
        fitness_scores.erase(fitness_scores.begin() + max_element_index);
    }
    return parents;
}


float Simulation(Walker& walker, World& world) {
    float start_position = walker.x_position;
    vector<LivingWalker> living_walker = world.AddWalker(walker);
    for (int i = 0; i < time_step_count; i++) {
        world.TimeStep();
    }
    float fitness = CalculateFitness(living_walker[0].body_storage[0], walker.x_position);
    for (int i = 0; i < living_walker[0].body_storage.size(); i++) {
        world.DeleteBody(living_walker[0].body_storage[i]);
    }
    return fitness;
}

vector<Walker> MakeChildren(vector<Walker>& parents) {
    vector<Walker> children;
    int children_per_parent = population_size / parent_count;
    int count = 0;
    for (Walker& parent: parents) {
        for (int i = 0; i < children_per_parent; i++) {
            
            Walker child;
            child.Setup();
            vector<float> joint_param = {parent.lower_angle, parent.upper_angle, parent.max_motor_torque, parent.motor_speed};
            vector<float> test1 = joint_param;
            
            MutateJointGenes(joint_param);

            child.lower_angle = joint_param[0];
            child.upper_angle = joint_param[1];
            child.max_motor_torque = joint_param[2];
            child.motor_speed = joint_param[3];
            
            //node parameter mutations
            vector<vector<float>> node_param = {parent.node_radius, parent.density, parent.friction, parent.restitution, parent.joint_length};
            
            vector<vector<float>> test = node_param;
            MutateNodeGenes(node_param);
            
            child.node_radius = node_param[0];
            child.density = node_param[1];
            child.friction = node_param[2];
            child.restitution = node_param[3];
            child.joint_length = node_param[4];
            
            children.push_back(child);
            count++;
            //safety check
            if (count >= population_size) {
                return children;
            }
        }
    }
    return children;
}

float CalculateFitness(b2Body* node, float start_position) {
    b2Vec2 position = node -> GetPosition();
    return position.x - start_position;
}

vector<float> Mate() {
    return {};
}

vector<vector<float>> InitialNodeGeneration(vector<vector<float>>& walker_params) {
    vector<vector<float>> tmp;
    //mutate node genes about the current parameter by a normal distribution and calculated standard deviation
    for (int i = 0; i < node_bounds.size();i++) {
        vector<float> tmp2;
        for (int j = 0; j < walker_params.size();j++) {
            float random_number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//            float random_number = 1.0f;
            float range = node_bounds[i][1] - node_bounds[i][0];
            tmp2.push_back(random_number * range + node_bounds[i][0]);
//            walker_params[i][j] = random_number * range + node_bounds[i][0];
        }
        tmp.push_back(tmp2);
    }
    return tmp;
//    for (auto v : walker_params) {
//        for (float x : v) {
//            std::cout << x << ", ";
//        }
//        std::cout << std::endl;
//    }
}


void InitialJointGeneration(vector<float>& joint_params) {
    //mutate joint genes about the current parameter by a normal distribution and calculated standard deviation
//    srand (time(NULL));
    for (int i = 0; i < joint_bounds.size(); i++) {
        float random_number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        float random_number = 1.0f;
        float range = joint_bounds[i][1] - joint_bounds[i][0];
        joint_params[i] = random_number * range + joint_bounds[i][0];
    }
}


void MutateNodeGenes(vector<vector<float>>& walker_params) {
    //mutate node genes about the current parameter by a normal distribution and calculated standard deviation
    
    //calculates standard deviation for each parameter
    vector<float> standard_deviation;
    for (int i = 0; i < node_bounds.size(); i++) {
        float std_dev = (node_bounds[i][1] - node_bounds[i][0]) / 8;
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

    //calculates standard deviation for each parameter
    vector<float> standard_deviation;
    for (int i = 0; i < joint_bounds.size(); i++) {
        float std_dev = (joint_bounds[i][1] - joint_bounds[i][0]) / 8;
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


void WriteWalkerToFile(vector<Walker>& best_walkers) {
    std::cout << "Writing to file" <<std::endl;
    ofstream my_file;
    my_file.open("/Users/derekli/Documents/CS126/final-project-derekli-NJ/data/Walker.txt");
    if (my_file.is_open()) {
        std::cout << "File is open!" << std::endl;
    }
    for (Walker& walker: best_walkers) {
        my_file << walker.node_count << std::endl;
        for (int i = 0; i < walker.node_radius.size();i++) {
            my_file << walker.node_radius[i] << std::endl;
        }
        for (int i = 0; i < walker.joint_length.size();i++) {
            my_file << walker.joint_length[i] << std::endl;
        }
        for (int i = 0; i < walker.density.size();i++) {
            my_file << walker.density[i] << std::endl;
        }
        for (int i = 0; i < walker.restitution.size();i++) {
            my_file << walker.restitution[i] << std::endl;
        }
        for (int i = 0; i < walker.friction.size();i++) {
            my_file << walker.friction[i] << std::endl;
        }
        for (int i = 0; i < walker.restitution.size();i++) {
            my_file << walker.restitution[i] << std::endl;
        }
        my_file << walker.lower_angle << std::endl;
        my_file << walker.upper_angle << std::endl;
        my_file << walker.max_motor_torque << std::endl;
        my_file << walker.motor_speed << std::endl;
        
        my_file << walker.damping_ratio << std::endl;
        my_file << walker.frequency_hz << std::endl;
        for (int i = 0; i < walker.node_locations.size(); i++) {
            for (int j = 0; j < walker.node_locations[i].size(); j++) {
                my_file << walker.node_locations[i][j] << std::endl;
            }
        }
    }
    my_file.close();
}
