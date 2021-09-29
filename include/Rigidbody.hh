#pragma once
#include<box2d/box2d.h>

class Rigidbody
{
private:
  b2World* world{};
  b2Fixture* fixture{};
  b2FixtureDef* fixtureDef{};
  b2Body* body{};
  b2BodyDef* bodyDef{};
  b2PolygonShape* polygonShape{};
public:
  Rigidbody();
  Rigidbody(b2World*& world, b2BodyType bodyType, b2Vec2* position, float width, float height,
  float density, float friction, float restitution, b2Vec2 origin, float angle);
  ~Rigidbody();

  b2Body* GetBody() const;
};