//
//  physics.cpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/12/19.
//

#include "PhysicsWorld.h"
#include <iostream>
using std::cout;
using std::endl;

World::World() {
	b2Vec2 gravity(0.0f, -9.8f);
//    b2World world(gravity);
    world = new b2World(gravity);
	
}

b2Body* World::AddWalker(Walker walker) {
    vector<b2Body*> bodies;
    vector<b2Vec2> positions;
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
        printf("%4.2f %4.2f\n", position.x, position.y);
    }
    b2RevoluteJointDef revolute_joint;
    revolute_joint.bodyA = bodies[0];
    revolute_joint.bodyB = bodies[1];
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

void World::Draw() {

}







//vector<b2Vec2> circlePosition;
//
//void setup() {
//    //Create world
//    b2Vec2 gravity(0.0f, -9.8f);
//    b2World world(gravity);
//
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.0f, -10.0f);
//
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);
//
//    b2PolygonShape groundBox;
//    groundBox.SetAsBox(50.0f, 10.0f);
//    groundBody->CreateFixture(&groundBox, 0.0f);
//
//
//    //Create dynamic body
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(0.0f, 4.0f);
//    b2Body* body = world.CreateBody(&bodyDef);
//
//    //Attach shape
//    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(1.0f, 1.0f);
//
//
//    //Define fixture
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &dynamicBox;
//    fixtureDef.density = 1.0f;
//    fixtureDef.friction = 0.3f;
//
//    //Create fixture
//    body->CreateFixture(&fixtureDef);
//
////    world->ClearForces();
//
//
//    float32 timeStep = 1.0f / 60.0f;
//    int32 velocityIterations = 6;
//    int32 positionIterations = 2;
//
//    for (int32 i = 0; i < 60; ++i)
//    {
//        world.Step(timeStep, velocityIterations, positionIterations);
//        b2Vec2 position = body->GetPosition();
//        float32 angle = body->GetAngle();
//
//        circlePosition.push_back(position);
//        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
//    }

    

