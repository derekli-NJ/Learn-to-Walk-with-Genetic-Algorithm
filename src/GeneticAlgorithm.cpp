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
using std::ifstream;
using std::stof;

vector<Walker> InitialGeneration() {
    vector<Walker> walkers;
    walkers.reserve(population_size);
    for (int i = 0; i < population_size; i++) {
        Walker walker;
        vector<float> joint_param = {walker.lower_angle, walker.upper_angle, walker.max_motor_torque, walker.motor_speed};
        vector<float> test1 = joint_param;
        
        InitialJointGeneration(joint_param);

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

        walker.Setup();
        walkers.push_back(walker);
    }
    return walkers;
}

vector<Walker> FindBestWalker(World world) {
    srand (1);
    vector<Walker> children = InitialGeneration();
    vector<Walker> parents;
    for (int i = 0; i < generation_count; i++) {
        std::cout<<current_generation_count<<std::endl;
        parents = Training(children, world);
        children = MakeChildren(parents);
        current_generation_count += 1;
    }
    std::cout << "Training"<<std::endl;
    vector<Walker> best_walkers = Training(children, world);
    
    WriteWalkerToFile(best_from_generation);
    return (best_walkers);
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
        if (i == 0) {
            best_from_generation.push_back(walkers[max_element_index]);
            best_fitness_from_generation.push_back(fitness_scores[max_element_index]);
        }
        walkers.erase(walkers.begin() + max_element_index);
        fitness_scores.erase(fitness_scores.begin() + max_element_index);
    }
    return parents;
}


float Simulation(Walker& walker, World& world) {
    World world2;
    float start_position = walker.x_position;
    vector<LivingWalker> living_walker = world2.AddWalker(walker);

    for (int i = 0; i < time_step_count; i++) {
        world2.TimeStep();
    }

    float fitness = CalculateFitness(living_walker[0].body_storage[0], walker.x_position);
    for (int i = 0; i < living_walker[0].body_storage.size(); i++) {
        world2.DeleteBody(living_walker[0].body_storage[i]);
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
            
            child.Setup();
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
        for (int j = 0; j < walker_params[i].size();j++) {
            float random_number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float range = node_bounds[i][1] - node_bounds[i][0];
            tmp2.push_back(random_number * range + node_bounds[i][0]);
        }
        tmp.push_back(tmp2);
    }
    return tmp;
}


void InitialJointGeneration(vector<float>& joint_params) {
    //mutate joint genes about the current parameter by a normal distribution and calculated standard deviation
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
        float std_dev = (node_bounds[i][1] - node_bounds[i][0]) / 12;
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
    
    //calculates standard deviation for each parameter
    vector<float> standard_deviation;
    for (int i = 0; i < joint_bounds.size(); i++) {
        float std_dev = (joint_bounds[i][1] - joint_bounds[i][0]) / 12;
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

vector<Walker> ReadWalkerFromFile() {
    vector<Walker> walkers;
    string line;
    ifstream my_file;
    my_file.open(file_path);
    if (my_file.is_open()) {
        std::cout << "File is open for reading!" << std::endl;
        while (true) {
            std::cout << "Entering file" << std::endl;
            Walker walker;
            
            string node_count;
            my_file >> node_count;
            if (my_file.eof()) {
                break;
            }
            std:: cout << node_count << std::endl;
            float converted_node_count = stof(node_count);
            walker.node_count = converted_node_count;
            
            for (int i = 0; i < walker.node_radius.size(); i++) {
                string node_radius;
                my_file >> node_radius;
                float converted_node_radius = stof(node_radius);
                walker.node_radius[i] = converted_node_radius;
            }
            for (int i = 0; i < walker.joint_length.size(); i++) {
                string joint_length;
                my_file >> joint_length;
                float converted_joint_length = stof(joint_length);
                walker.joint_length[i] = converted_joint_length;
            }
            for (int i = 0; i < walker.density.size(); i++) {
                string density;
                my_file >> density;
                float converted_density = stof(density);
                walker.density[i] = converted_density;
            }
            for (int i = 0; i < walker.friction.size(); i++) {
                string friction;
                my_file >> friction;
                float converted_friction = stof(friction);
                walker.friction[i] = converted_friction;
            }
            for (int i = 0; i < walker.restitution.size(); i++) {
                string restitution;
                my_file >> restitution;
                float converted_restitution = stof(restitution);
                walker.restitution[i] = converted_restitution;
            }
            string lower_angle;
            my_file >> lower_angle;
            float converted_lower_angle = stof(lower_angle);
            walker.lower_angle = converted_lower_angle;
            
            string upper_angle;
            my_file >> upper_angle;
            float converted_upper_angle = stof(upper_angle);
            walker.upper_angle = converted_upper_angle;
            
            string max_motor_torque;
            my_file >> max_motor_torque;
            float converted_max_motor_torque = stof(max_motor_torque);
            walker.max_motor_torque = converted_max_motor_torque;
            
            string motor_speed;
            my_file >> motor_speed;
            float converted_motor_speed = stof(motor_speed);
            walker.motor_speed = converted_motor_speed;
            
            string damping_ratio;
            my_file >> damping_ratio;
            float converted_damping_ratio = stof(damping_ratio);
            walker.damping_ratio = converted_damping_ratio;
            
            string frequency_hz;
            my_file >> frequency_hz;
            float converted_frequency_hz = stof(frequency_hz);
            walker.frequency_hz = converted_frequency_hz;
            
            for (int i = 0; i < walker.node_locations.size(); i++) {
                for (int j = 0; j < walker.node_locations[i].size(); j++) {
                    string node_location;
                    my_file >> node_location;
                    float converted_node_location = stof(node_location);
                    walker.node_locations[i][j] = converted_node_location;
                }
            }
            string fitness;
            my_file >> fitness;
            float converted_fitness = stof(fitness);
            walker.fitness = converted_fitness;
            
            walker.Setup();
            walkers.push_back(walker);
        }
        my_file.close();
    }
    return walkers;
}


void WriteWalkerToFile(vector<Walker>& best_walkers) {
    std::cout << "Writing to file" <<std::endl;
    ofstream my_file;
    my_file.open(file_path);
    if (my_file.is_open()) {
        std::cout << "File is open for writing!" << std::endl;
    }
    if (best_walkers.size() != best_fitness_from_generation.size()) {
        std::cout << "Failed when building vectors" << std::endl;
    }
    for (int ind = 0; ind < best_walkers.size(); ind++) {
        my_file << best_walkers[ind].node_count << std::endl;
        for (int i = 0; i < best_walkers[ind].node_radius.size();i++) {
            my_file << best_walkers[ind].node_radius[i] << std::endl;
        }
        for (int i = 0; i < best_walkers[ind].joint_length.size();i++) {
            my_file << best_walkers[ind].joint_length[i] << std::endl;
        }
        for (int i = 0; i < best_walkers[ind].density.size();i++) {
            my_file << best_walkers[ind].density[i] << std::endl;
        }
        for (int i = 0; i < best_walkers[ind].friction.size();i++) {
            my_file << best_walkers[ind].friction[i] << std::endl;
        }
        for (int i = 0; i < best_walkers[ind].restitution.size();i++) {
            my_file << best_walkers[ind].restitution[i] << std::endl;
        }
        my_file << best_walkers[ind].lower_angle << std::endl;
        my_file << best_walkers[ind].upper_angle << std::endl;
        my_file << best_walkers[ind].max_motor_torque << std::endl;
        my_file << best_walkers[ind].motor_speed << std::endl;
        
        my_file << best_walkers[ind].damping_ratio << std::endl;
        my_file << best_walkers[ind].frequency_hz << std::endl;
        for (int i = 0; i < best_walkers[ind].node_locations.size(); i++) {
            for (int j = 0; j < best_walkers[ind].node_locations[i].size(); j++) {
                my_file << best_walkers[ind].node_locations[i][j] << std::endl;
            }
        }
        my_file << best_fitness_from_generation[ind] << std::endl;
        
    }
    my_file.close();
}
