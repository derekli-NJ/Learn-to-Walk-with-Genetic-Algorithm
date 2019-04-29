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

b2Body* groundBody;

World::World() {
	b2Vec2 gravity(0.0f, -9.8f);
    world = new b2World(gravity);
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position = b2Vec2(0.0, 1.0);
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    groundBody = world -> CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2PolygonShape groundBox;
    
    // The extents are the half-widths of the box.
    groundBox.SetAsBox(ground_width/2, ground_height/2);
    b2FixtureDef def;
    def.shape = &groundBox;
    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&def);
    
    
    b2Vec2 ground_position = groundBody -> GetPosition();
//    std::cout << ground_position.x << std::endl;
//    std::cout << ground_position.y << std::endl;
    
    ground_draw_parameters.push_back(ground_position.x - ground_width / 2);
    ground_draw_parameters.push_back(ground_position.y - ground_height / 2);
    ground_draw_parameters.push_back(ground_width);
    ground_draw_parameters.push_back(ground_height);
//
}

vector<LivingWalker> World::AddWalker(Walker walker) {
    bodies.clear();
    for (int i = 0; i < walker.node_count; i++) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(walker.node_locations[i][0], walker.node_locations[i][1]);
        b2Body* body = world -> CreateBody(&bodyDef);
        
        bodies.push_back(body);
        
        //set circle
        b2CircleShape circle;
        
//        std::cout << "X Position " << walker.node_locations[i][0] << std::endl;
        
//        circle.m_p.Set(walker.node_locations[i][0], walker.node_locations[i][1]);
        circle.m_radius = walker.node_radius[i];
        
        //set fixture
        b2FixtureDef fixture_def;
        fixture_def.shape = &circle;
        fixture_def.density = walker.density[i];
        fixture_def.friction = walker.friction[i];
        fixture_def.restitution = walker.restitution[i];
        body -> CreateFixture(&fixture_def);
        
        b2Vec2 position = body->GetPosition();
        positions.push_back(position);
    }

    b2DistanceJointDef distance_joint_0;
//    distance_joint_0.bodyA = bodies[0];
//    distance_joint_0.bodyB = bodies[1];

    distance_joint_0.Initialize(bodies[0], bodies[1], positions[0], positions[1]);
    distance_joint_0.collideConnected = true;

    //Defines softness of distance joint
    distance_joint_0.dampingRatio = walker.damping_ratio;
    distance_joint_0.frequencyHz = walker.frequency_hz;

    b2DistanceJoint* dist_joint_0 = (b2DistanceJoint*)world -> CreateJoint(&distance_joint_0);

    b2RevoluteJointDef revolute_joint;
    revolute_joint.Initialize(bodies[0], bodies[1], positions[1]);
    revolute_joint.collideConnected = false;
    revolute_joint.motorSpeed = walker.motor_speed;
    revolute_joint.maxMotorTorque = walker.max_motor_torque;
    
    revolute_joint.upperAngle = walker.upper_angle * b2_pi;
    revolute_joint.lowerAngle = walker.lower_angle * b2_pi;
    
    revolute_joint.enableLimit = true;

    revolute_joint.enableMotor = true;
    joint = (b2RevoluteJoint*)world->CreateJoint(&revolute_joint);

    b2PrismaticJointDef prismatic_joint;
    prismatic_joint.Initialize(bodies[1], bodies[2], positions[1], b2Vec2(0,1));
    prismatic_joint.enableMotor = false;
    prismatic_joint.enableLimit = false;
    (b2PrismaticJoint*)world -> CreateJoint(&prismatic_joint);
    
    b2DistanceJointDef distance_joint;
    

    //bodies connected to and world position of anchors
    distance_joint.Initialize(bodies[1], bodies[2], positions[1], positions[2]);
    distance_joint.collideConnected = true;

    //Defines softness of distance joint
    distance_joint.dampingRatio = walker.damping_ratio;
    distance_joint.frequencyHz = walker.frequency_hz;

    b2DistanceJoint* dist_joint = (b2DistanceJoint*)world -> CreateJoint(&distance_joint);
    
    LivingWalker living_walker(walker, bodies);
    living_walkers.push_back(living_walker);
    
    return living_walkers; 
}

void World::DeleteBody(b2Body* node) {
    world -> DestroyBody(node);
}


void World::TimeStep() {
//    revolute_joint -> SetMotorSpeed(cosf(0.5f * time));
//    joint->SetMotorSpeed(0.1);
    time += 1;
    if (time % 60 == 0) {
        joint -> SetMotorSpeed(-joint -> GetMotorSpeed());
    }
    
    vector<vector<float>> body_draw_parameters = living_walkers[0].Draw();
    float x_position = body_draw_parameters[1][0];
    float y_position = body_draw_parameters[1][1];
//
//    std::cout << "X-Position: " << x_position << std::endl;
//    std::cout << "Y-Position: " << y_position << std::endl;
//    std::cout << world->GetBodyCount() << std::endl;
    b2Vec2 ground_position = groundBody -> GetPosition();
//    std::cout << ground_position.x << std::endl;
//    std::cout << ground_position.y << std::endl;
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
