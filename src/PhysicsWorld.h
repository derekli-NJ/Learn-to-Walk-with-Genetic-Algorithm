//
//  physics.hpp
//  Final_Project_Without_Wrapper
//
//  Created by Derek Li on 4/12/19.
//
#pragma once
#ifndef physics_hpp
#define physics_hpp

#include <stdio.h>
#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2World.h"
#include <vector>

using std::vector;
using std::shared_ptr;

extern vector<b2Vec2> circlePosition;

void setup();
//vector<b2PolygonShape> polygons;

//vector <shared_ptr<b2PolygonShape>> polygons;


#endif /* physics_hpp */
