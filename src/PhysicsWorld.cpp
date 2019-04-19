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
        circle.m_radius = walker.node_radius;
        
        //set fixture
        b2FixtureDef fixture_def;
        fixture_def.shape = &circle;
        fixture_def.density = walker.density;
        fixture_def.friction = walker.friction;
        body -> CreateFixture(&fixture_def);
        
        b2Vec2 position = body->GetPosition();
        positions.push_back(position);
        
        body_draw_parameters.push_back(position.x);
        body_draw_parameters.push_back(position.y);
        body_draw_parameters.push_back(walker.node_radius);
        printf("%4.2f %4.2f\n", position.x, position.y);
    }
    b2RevoluteJointDef revolute_joint;
    revolute_joint.bodyA = bodies[0];
    revolute_joint.bodyB = bodies[1];
    
        //gets position of joints
    for (int i = 0; i < bodies.size(); i++) {
        b2Vec2 body_position = bodies[i]->GetPosition();
        //    b2Vec2 body_b_position = bodies[1]->GetPosition();
        joint_draw_parameters.push_back(body_position);
        //    joint_draw_parameters.push_back(body_b_position);
    }
    
    
    
    //set to relative position (coordinate system rotates with revolution)
    revolute_joint.localAnchorA.Set(2 * walker.node_radius + walker.joint_length, 0);
    
    //parameters of revolute joint
    revolute_joint.lowerAngle = walker.lower_angle * b2_pi; // -90 degrees
    revolute_joint.upperAngle = walker.upper_angle * b2_pi; // 45 degrees
    revolute_joint.enableLimit = true;
    revolute_joint.maxMotorTorque = walker.max_motor_torque;
    revolute_joint.motorSpeed = walker.motor_speed;
    revolute_joint.enableMotor = true;
    b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&revolute_joint);
    
    
    
    b2DistanceJointDef distance_joint;
    //bodies connected to and world position of anchors
    distance_joint.Initialize(bodies[1], bodies[2], positions[1], positions[2]);
    distance_joint.collideConnected = true;
    
    //Defines softness of distance joint
    distance_joint.dampingRatio = walker.damping_ratio;
    distance_joint.frequencyHz = walker.frequency_hz;
    
    return bodies[0];
}
void World::TimeStep() {
    world->Step( timeStep, velocityIterations, positionIterations);
}

void World::Clear() {

}

const vector<float>& World::GetBodyDrawParameters() {
    return body_draw_parameters;
}

const vector<b2Vec2>& World::GetJointDrawParameters() {
    return joint_draw_parameters;
}

