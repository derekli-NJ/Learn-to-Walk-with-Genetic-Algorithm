//
//  physics.cpp
//  Final_Project
//
//  Created by Derek Li on 4/12/19.
//

#include <iostream>
#include "PhysicsWorld.h"


using std::cout;
using std::endl;

World::World() {
	b2Vec2 gravity(0.0f, -9.8f);
    world = new b2World(gravity);
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0, 6.0);
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world -> CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2PolygonShape groundBox;
    
    // The extents are the half-widths of the box.
    groundBox.SetAsBox(ground_width, ground_height);
    
    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    b2Vec2 ground_position = groundBody -> GetPosition();
    
    ground_draw_parameters.push_back(ground_position.x);
    ground_draw_parameters.push_back(ground_position.y);
    ground_draw_parameters.push_back(ground_width);
    ground_draw_parameters.push_back(ground_height);
    
    std::cout << ground_position.x << std::endl;
    std::cout << ground_position.y << std::endl;
}

b2Body* World::AddWalker(Walker walker) {
    for (int i = 0; i < walker.node_count; i++) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(walker.node_locations[i][0], walker.node_locations[i][1]);
        b2Body* body = world -> CreateBody(&bodyDef);
        
        bodies.push_back(body);
        
        //set circle
        b2CircleShape circle;
        circle.m_p.Set(walker.node_locations[i][0], walker.node_locations[i][1]);
        circle.m_radius = walker.node_radius[i];
        
        //set fixture
        b2FixtureDef fixture_def;
        fixture_def.shape = &circle;
        fixture_def.density = walker.density[i];
        fixture_def.friction = walker.friction[i];
        body -> CreateFixture(&fixture_def);
        
        b2Vec2 position = body->GetPosition();
        positions.push_back(position);
    }
    revolute_joint.bodyA = bodies[0];
    revolute_joint.bodyB = bodies[1];

    //set to relative position (coordinate system rotates with revolution)
    revolute_joint.localAnchorA.Set(2 * walker.node_radius[0] + walker.joint_length[0], 0);
    //revolute_joint.localAnchorA.Set(walker.joint_length[0], 0);

    revolute_joint.localAnchorB.Set(0, 0);

    //parameters of revolute joint
    revolute_joint.lowerAngle = walker.lower_angle * b2_pi; // -90 degrees
    revolute_joint.upperAngle = walker.upper_angle * b2_pi; // 45 degrees
    revolute_joint.enableLimit = true;
    revolute_joint.maxMotorTorque = walker.max_motor_torque;
    revolute_joint.motorSpeed = 0.1;

//    revolute_joint.motorSpeed = walker.motor_speed;
//    revolute_joint.enableMotor = true;
    b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&revolute_joint);

//    joint->SetMotorSpeed(1);

    b2DistanceJointDef distance_joint;
    //bodies connected to and world position of anchors
    distance_joint.Initialize(bodies[1], bodies[2], b2Vec2_zero, b2Vec2_zero);

//    distance_joint.localAnchorA(2 * walker.node_radius[1] + walker.joint_length[1], 0);
    distance_joint.collideConnected = true;

    //Defines softness of distance joint
    distance_joint.dampingRatio = walker.damping_ratio;
    distance_joint.frequencyHz = walker.frequency_hz;

    b2DistanceJoint* dist_joint = (b2DistanceJoint*)world -> CreateJoint(&distance_joint);
    
    LivingWalker living_walker(walker, bodies);
    living_walkers.push_back(living_walker);
    
    return bodies[0];
}

void World::TimeStep() {
//    revolute_joint -> SetMotorSpeed(cosf(0.5f * time));
    vector<vector<float>> body_draw_parameters = living_walkers[0].Draw();
    float x_position = body_draw_parameters[1][0];
    float y_position = body_draw_parameters[1][1];
    
    std::cout << "X-Position: " << x_position << std::endl;
    std::cout << "Y-Position: " << y_position << std::endl;
//    x_position = body_param[walker_num][i][j] * scaling_factor;
//    y_position = body_param[walker_num][i][j+1] * scaling_factor;
    world->Step( timeStep, velocityIterations, positionIterations);
}

void World::Clear() {

}

vector<vector<vector<float>>> World::GetBodyDrawParameters() {
    vector<vector<vector<float>>> body_draw_parameters;
    for ( LivingWalker living_walker : living_walkers ) {
        body_draw_parameters.push_back(living_walker.Draw());
    }
    return body_draw_parameters;
}

vector<float>& World::GetGroundDrawParameters() {
    return ground_draw_parameters;
}
