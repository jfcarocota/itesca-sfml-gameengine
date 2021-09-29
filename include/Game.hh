#pragma once
#include<SFML/Graphics.hpp>
#include<box2d/box2d.h>

class Game
{
private:
  sf::RenderWindow* window{};
  sf::Event* event{};
  b2Vec2* gravity{};
  b2World* world{};
public:
  Game();
  ~Game();

  void UpdatePhysics();
  void Render();
  void Init();
  void Update();
  void Draw();
  void Inputs();
};
