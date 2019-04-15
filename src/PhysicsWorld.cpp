//
//  physics.cpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/12/19.
//

#include "PhysicsWorld.h"

vector<b2Vec2> circlePosition;

void setup() {
    //Create world
    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    
    //Create dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    
    //Attach shape
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    

    //Define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    
    //Create fixture
    body->CreateFixture(&fixtureDef);
    
//    world->ClearForces();

    
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();
        
        circlePosition.push_back(position);
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }
    
    
}
