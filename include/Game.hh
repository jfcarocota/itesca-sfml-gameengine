#pragma once
#include<SFML/Graphics.hpp>

class Game
{
private:
  sf::RenderWindow* window{};
  sf::Event* event{};
public:
  Game();
  ~Game();

  void Render();
  void Init();
  void Update();
  void Draw();
  void Inputs();
};
